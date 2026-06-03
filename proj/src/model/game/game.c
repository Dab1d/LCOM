#include <lcom/lcf.h>
#include <stdlib.h>
#include "game.h"
#include "../../controller/input/input.h"
#include "../resources/resources.h"
#include "../../view/car/car_view.h"
#include "../../view/obstacle/obstacle_view.h"
#include "../../view/track/track_view.h"
#include "../../view/scenery/scenery_view.h"
#include "../../view/view.h"
#include "../../view/pause/pause_view.h"
#include "../../controller/palette/palette.h"

#define CLUSTER_CHANCE    70
#define BOOST_TILES       2

static Game game;

static void spawn_single(int row, int lane_min, int lane_max) {
    if (game.obstacle_count >= MAX_OBSTACLES) return;
    int lane = lane_min + rand() % (lane_max - lane_min + 1);
    game.obstacles[game.obstacle_count] = create_obstacle(row, lane);
    game.obstacle_count++;
}

static void spawn_cluster(int base_row, int lane_min, int lane_max) {
    int available = lane_max - lane_min + 1;
    int size = 2 + rand() % 2;

    if (rand() % 2) {
        int start = lane_min + rand() % (available - size + 1);
        for (int i = 0; i < size && game.obstacle_count < MAX_OBSTACLES; i++) {
            game.obstacles[game.obstacle_count] = create_obstacle(base_row, start + i);
            game.obstacle_count++;
        }
    } else {
        int lane = lane_min + rand() % available;
        for (int i = 0; i < size && game.obstacle_count < MAX_OBSTACLES; i++) {
            game.obstacles[game.obstacle_count] = create_obstacle(base_row + i, lane);
            game.obstacle_count++;
        }
    }
}

/* ── ciclo de vida da sessão ──────────────────────────────────────── */

void game_create(Game *g) {
    g->track = create_track(TRACK_THEME_CITY);
    g->car1 = create_car(2, PLAYER1_LANE_START, PLAYER1_LANE_END, CAR_WIDTH, CAR_HEIGHT);
    g->car1->player = 1;
    g->car2 = create_car(7, PLAYER2_LANE_START, PLAYER2_LANE_END, CAR_WIDTH, CAR_HEIGHT);
    g->car2->player = 2;
    g->scenery = scenery_view_create();
    g->winner = 0;
    g->pause_selected = 0;
    g->obstacle_count = 0;

    for (int row = 10; row < TRACK_TOTAL_ROWS - 10 && g->obstacle_count < MAX_OBSTACLES - 6; row += 8) {
        if (rand() % 100 < CLUSTER_CHANCE)
            spawn_cluster(row, PLAYER1_LANE_START, PLAYER1_LANE_END);
        else
            spawn_single(row, PLAYER1_LANE_START, PLAYER1_LANE_END);

        if (rand() % 100 < CLUSTER_CHANCE)
            spawn_cluster(row + 4, PLAYER2_LANE_START, PLAYER2_LANE_END);
        else
            spawn_single(row + 4, PLAYER2_LANE_START, PLAYER2_LANE_END);
    }

    g->state = GAMEPLAY;
}

void game_reset(Game *g) {
    if (g->track) {
        destroy_track(g->track);
        g->track = NULL;
    }
    if (g->car1) {
        destroy_car(g->car1);
        g->car1 = NULL;
    }
    if (g->car2) {
        destroy_car(g->car2);
        g->car2 = NULL;
    }
    if (g->scenery) {
        scenery_view_destroy(g->scenery);
        g->scenery = NULL;
    }
    for (int i = 0; i < g->obstacle_count; i++) {
        if (g->obstacles[i]) {
            destroy_obstacle(g->obstacles[i]);
            g->obstacles[i] = NULL;
        }
    }
    g->obstacle_count = 0;
    game_create(g);
}

/* ── input / update / render ──────────────────────────────────────── */

static void game_process_input(void) {
    switch (game.state) {
        case MAIN_MENU:
            if (input_esc_pressed()) game.state = EXIT;
            if (input_menu_start_pressed()) game_reset(&game);
            break;
        case GAMEPLAY:
            if (input_keyboard_pause_pressed()) {
                game.pause_selected = 0;
                game.state = PAUSE;
            }
            if (input_keyboard_car_left_pressed()) car_move_lane(game.car1, -1);
            if (input_keyboard_car_right_pressed()) car_move_lane(game.car1, +1);
            break;
        case PAUSE:
            if (input_keyboard_pause_pressed()) {
                game.state = GAMEPLAY;
            } else if (input_keyboard_up_pressed() || input_keyboard_down_pressed()) {
                game.pause_selected = 1 - game.pause_selected;
            } else if (input_keyboard_confirm_pressed()) {
                if (game.pause_selected == 0)
                    game.state = GAMEPLAY;
                else
                    game.state = MAIN_MENU;
            }
            break;
        case GAME_OVER:
            if (input_gameover_restart_pressed())
                game_reset(&game);
            if (input_gameover_menu_pressed())
                game.state = MAIN_MENU;
            break;
        case EXIT:
            break;
    }
    input_flush();
}

static void game_update(void) {
    track_update(game.track);
    for (int i = 0; i < game.obstacle_count; i++) {
        if (game.obstacles[i] != NULL)
            obstacle_update(game.obstacles[i], game.track->scroll_row, game.track->scroll_offset);
    }
}

static void game_process_collisions(void) {
    for (int i = 0; i < game.obstacle_count; i++) {
        Obstacle *obs = game.obstacles[i];
        if (obs == NULL || !obs->base.is_active) continue;

        if (game.car1->base.is_active && obstacle_collides_with_car(obs, game.car1)) {
            car_take_damage(game.car1);
            obs->base.is_active = false;
        }
        if (game.car2->base.is_active && obstacle_collides_with_car(obs, game.car2)) {
            car_take_damage(game.car2);
            obs->base.is_active = false;
        }
    }

    if (game.car1->base.is_active) {
        int c1_row = game.track->scroll_row + (int) (game.car1->base.y / TRACK_TILE_HEIGHT);
        TileType t1 = track_get_tile(game.track, c1_row, game.car1->lane);
        if (t1 == TILE_OBSTACLE) {
            car_take_damage(game.car1);
            track_clear_tile(game.track, c1_row, game.car1->lane);
        } else if (t1 == TILE_BOOST) {
            car_apply_boost(game.car1, BOOST_TILES);
            track_clear_tile(game.track, c1_row, game.car1->lane);
        }
    }

    if (game.car2->base.is_active) {
        int c2_row = game.track->scroll_row + (int) (game.car2->base.y / TRACK_TILE_HEIGHT);
        TileType t2 = track_get_tile(game.track, c2_row, game.car2->lane);
        if (t2 == TILE_OBSTACLE) {
            car_take_damage(game.car2);
            track_clear_tile(game.track, c2_row, game.car2->lane);
        } else if (t2 == TILE_BOOST) {
            car_apply_boost(game.car2, BOOST_TILES);
            track_clear_tile(game.track, c2_row, game.car2->lane);
        }
    }
}

static bool game_is_over(void) {
    if (!game.car1->base.is_active) {
        game.winner = 2;
        return true;
    }
    if (!game.car2->base.is_active) {
        game.winner = 1;
        return true;
    }
    if (track_is_finished(game.track)) {
        game.winner = (game.car1->track_progress >= game.car2->track_progress) ? 1 : 2;
        return true;
    }
    return false;
}

#define SCREEN_W 1024
#define SCREEN_H  768

static void game_render(void) {
    draw_clear(PAL_BLACK);

    switch (game.state) {
        case MAIN_MENU:
            break;
        case GAMEPLAY:
            track_view_draw(game.track);
            scenery_view_update(game.scenery, game.track);
            scenery_view_draw(game.scenery);
            car_view_draw(game.car1);
            car_view_draw(game.car2);
            for (int i = 0; i < game.obstacle_count; i++) {
                if (obstacle_is_visible(game.obstacles[i]))
                    obstacle_view_draw(game.obstacles[i]);
            }
            break;
        case GAME_OVER:
            break;
        case PAUSE:
            track_view_draw(game.track);
            scenery_view_update(game.scenery, game.track);
            scenery_view_draw(game.scenery);
            car_view_draw(game.car1);
            car_view_draw(game.car2);
            for (int i = 0; i < game.obstacle_count; i++) {
                if (obstacle_is_visible(game.obstacles[i]))
                    obstacle_view_draw(game.obstacles[i]);
            }
            pause_view_draw(game.pause_selected);
            break;
        case EXIT:
            break;
    }

    copy_buffer_to_video();
}

void game_init(void) {
    resources_destroy();
    resources_load();
    game.state = MAIN_MENU;
    game.winner = 0;
    game.pause_selected = 0;
    game.track = NULL;
    game.car1 = NULL;
    game.car2 = NULL;
    game.scenery = NULL;
    game.obstacle_count = 0;
}

GameState game_get_state(void) {
    return game.state;
}

void game_set_state(GameState new_state) {
    game.state = new_state;
}

const Game *game_get(void) {
    return &game;
}

void game_tick(void) {
    game_process_input();

    switch (game.state) {
        case GAMEPLAY:
            game_update();
            game_process_collisions();
            if (game_is_over()) game.state = GAME_OVER;
            break;
        case MAIN_MENU:
        case PAUSE:
        case GAME_OVER:
        case EXIT:
            break;
    }

    game_render();
}
