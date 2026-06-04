#include <lcom/lcf.h>
#include <stdlib.h>
#include "game.h"
#include "../../controller/input/input.h"
#include "../resources/resources.h"
#include "../../view/car/car_view.h"
#include "../../view/obstacle/obstacle_view.h"
#include "../../view/boost/boost_view.h"
#include "../../view/track/track_view.h"
#include "../scenery/scenery.h"
#include "../../view/scenery/scenery_view.h"
#include "../../view/view.h"
#include "../../view/pause/pause_view.h"
#include "../../view/win/win_view.h"
#include "../../controller/palette/palette.h"

/* forward declarations — defined in input.c, only used in this file */
int input_mouse_over_pause_resume(void);
int input_mouse_over_pause_quit(void);
int input_mouse_pause_resume_pressed(void);
int input_mouse_pause_quit_pressed(void);
int input_cursor_x(void);
int input_cursor_y(void);

#define CLUSTER_CHANCE    70
#define BOOST_TILES       2
#define BOOST_SPAWN_CHANCE 65
#define MENU_START        0
#define MENU_EXIT         1

static Game game;

static void spawn_boost(int row, int lane_min, int lane_max) {
    if (game.boost_count >= MAX_BOOSTS) return;
    int lane = lane_min + rand() % (lane_max - lane_min + 1);
    game.boosts[game.boost_count] = create_boost(row, lane);
    game.boost_count++;
}

static void spawn_single(int row, int lane_min, int lane_max) {
    if (game.obstacle_count >= MAX_OBSTACLES) return;
    int lane = lane_min + rand() % (lane_max - lane_min + 1);
    game.obstacles[game.obstacle_count] = create_obstacle(row, lane, OBSTACLE_ROCK);
    game.obstacle_count++;
}

static void spawn_cluster(int base_row, int lane_min, int lane_max) {
    int available = lane_max - lane_min + 1;
    int size = 2 + rand() % 2;

    if (rand() % 2) {
        int start = lane_min + rand() % (available - size + 1);
        for (int i = 0; i < size && game.obstacle_count < MAX_OBSTACLES; i++) {
            game.obstacles[game.obstacle_count] = create_obstacle(base_row, start + i, OBSTACLE_ROCK);
            game.obstacle_count++;
        }
    } else {
        int lane = lane_min + rand() % available;
        for (int i = 0; i < size && game.obstacle_count < MAX_OBSTACLES; i++) {
            game.obstacles[game.obstacle_count] = create_obstacle(base_row + i, lane, OBSTACLE_ROCK);
            game.obstacle_count++;
        }
    }
}

static void spawn_banana(int row, int lane_min, int lane_max) {
    if (game.obstacle_count >= MAX_OBSTACLES) return;
    int lane = lane_min + rand() % (lane_max - lane_min + 1);
    game.obstacles[game.obstacle_count] = create_obstacle(row, lane, OBSTACLE_BANANA);
    game.obstacle_count++;
}

/* ── ciclo de vida da sessão ──────────────────────────────────────── */

void game_create(Game *game) {
    game->track = create_track(TRACK_THEME_CITY);
    game->car1 = create_car(2, PLAYER1_LANE_START, PLAYER1_LANE_END, CAR_WIDTH, CAR_HEIGHT);
    game->car1->player = 1;
    game->car2 = create_car(7, PLAYER2_LANE_START, PLAYER2_LANE_END, CAR_WIDTH, CAR_HEIGHT);
    game->car2->player = 2;
    game->scenery = scenery_create();
    game->winner = 0;
    game->pause_selected = 0;
    game->obstacle_count = 0;
    game->boost_count = 0;

    for (int row = 10; row < TRACK_TOTAL_ROWS - 10 && game->boost_count < MAX_BOOSTS; row += 10) {
        if (rand() % 100 < BOOST_SPAWN_CHANCE)
            spawn_boost(row, PLAYER1_LANE_START, PLAYER1_LANE_END);
        if (rand() % 100 < BOOST_SPAWN_CHANCE)
            spawn_boost(row, PLAYER2_LANE_START, PLAYER2_LANE_END);
    }

    for (int row = 10; row < TRACK_TOTAL_ROWS - 10 && game->obstacle_count < MAX_OBSTACLES - 6; row += 8) {
        if (rand() % 100 < CLUSTER_CHANCE)
            spawn_cluster(row, PLAYER1_LANE_START, PLAYER1_LANE_END);
        else
            spawn_single(row, PLAYER1_LANE_START, PLAYER1_LANE_END);

        if (rand() % 100 < CLUSTER_CHANCE)
            spawn_cluster(row + 4, PLAYER2_LANE_START, PLAYER2_LANE_END);
        else
            spawn_single(row + 4, PLAYER2_LANE_START, PLAYER2_LANE_END);
    }

    /* Cascas de banana — intercaladas com os obstáculos normais */
    for (int row = 14; row < TRACK_TOTAL_ROWS - 10 && game->obstacle_count < MAX_OBSTACLES; row += 12) {
        if (rand() % 100 < 35)
            spawn_banana(row, PLAYER1_LANE_START, PLAYER1_LANE_END);
        if (rand() % 100 < 35)
            spawn_banana(row + 6, PLAYER2_LANE_START, PLAYER2_LANE_END);
    }

    game->state = GAMEPLAY;
}

void game_reset(Game *game) {
    if (game->track) {
        destroy_track(game->track);
        game->track = NULL;
    }
    if (game->car1) {
        destroy_car(game->car1);
        game->car1 = NULL;
    }
    if (game->car2) {
        destroy_car(game->car2);
        game->car2 = NULL;
    }
    if (game->scenery) {
        scenery_destroy(game->scenery);
        game->scenery = NULL;
    }
    for (int i = 0; i < game->obstacle_count; i++) {
        if (game->obstacles[i]) {
            destroy_obstacle(game->obstacles[i]);
            game->obstacles[i] = NULL;
        }
    }
    game->obstacle_count = 0;
    for (int i = 0; i < game->boost_count; i++) {
        if (game->boosts[i]) {
            destroy_boost(game->boosts[i]);
            game->boosts[i] = NULL;
        }
    }
    game->boost_count = 0;
    game_create(game);
}

/* ── input / update / render ──────────────────────────────────────── */

static void game_process_input(void) {
    switch (game.state) {
        case MAIN_MENU:
            if (input_esc_pressed()) { game.state = EXIT; break; }
            if (input_menu_nav_up())      game.menu_selection = MENU_START;
            if (input_menu_nav_down())    game.menu_selection = MENU_EXIT;
            if (input_mouse_over_start()) game.menu_selection = MENU_START;
            if (input_mouse_over_exit())  game.menu_selection = MENU_EXIT;
            if (input_keyboard_start_pressed()) {
                if (game.menu_selection == MENU_START) game_reset(&game);
                else game.state = EXIT;
            }
            if (input_mouse_start_pressed()) game_reset(&game);
            if (input_mouse_exit_pressed())  game.state = EXIT;
            break;
        case GAMEPLAY:
            if (input_keyboard_pause_pressed()) {
                game.pause_selected = 0;
                game.state = PAUSE;
            }
            if (input_keyboard_car_left_pressed()  || input_keyboard_car1_left_pressed())  car_move_lane(game.car1, -1);
            if (input_keyboard_car_right_pressed() || input_keyboard_car1_right_pressed()) car_move_lane(game.car1, +1);
            if (input_mouse_car2_left())  car_move_lane(game.car2, -1);
            if (input_mouse_car2_right()) car_move_lane(game.car2, +1);
            break;
        case PAUSE:
            if (input_mouse_over_pause_resume()) game.pause_selected = 0;
            if (input_mouse_over_pause_quit())   game.pause_selected = 1;
            if (input_keyboard_pause_pressed() || input_mouse_pause_resume_pressed()) {
                game.state = GAMEPLAY;
            } else if (input_mouse_pause_quit_pressed()) {
                game.menu_selection = 0;
                game.state = MAIN_MENU;
            } else if (input_keyboard_up_pressed() || input_keyboard_down_pressed()) {
                game.pause_selected = 1 - game.pause_selected;
            } else if (input_keyboard_confirm_pressed()) {
                if (game.pause_selected == 0)
                    game.state = GAMEPLAY;
                else {
                    game.menu_selection = 0;
                    game.state = MAIN_MENU;
                }
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

static void apply_boost_movement(Car* car, float boost_speed) {
    if (car->boost_remaining <= 0.0f) return;
    float step = car->boost_remaining < boost_speed ? car->boost_remaining : boost_speed;
    car->base.y -= (double)step;
    if (car->base.y < 0.0) car->base.y = 0.0;
    car->boost_remaining -= step;
}

static void game_update(void) {
    input_tick_inverted();
    track_update(game.track);
    scenery_update(game.scenery, game.track);

    float boost_speed = game.track->scroll_speed * 3.0f;
    apply_boost_movement(game.car1, boost_speed);
    apply_boost_movement(game.car2, boost_speed);

    for (int i = 0; i < game.obstacle_count; i++) {
        if (game.obstacles[i] != NULL)
            obstacle_update(game.obstacles[i], game.track->scroll_row, game.track->scroll_offset);
    }
    for (int i = 0; i < game.boost_count; i++) {
        if (game.boosts[i] != NULL)
            boost_update(game.boosts[i], game.track->scroll_row, game.track->scroll_offset);
    }
}

static void game_process_collisions(void) {
    for (int i = 0; i < game.obstacle_count; i++) {
        Obstacle *obs = game.obstacles[i];
        if (obs == NULL || !obs->base.is_active) continue;

        if (game.car1->base.is_active && obstacle_collides_with_car(obs, game.car1)) {
            if (obs->type == OBSTACLE_BANANA) {
                car_banana_slip(game.car1);
                input_set_car1_inverted(180);
            } else {
                car_take_damage(game.car1);
            }
            obs->base.is_active = false;
        }
        if (game.car2->base.is_active && obstacle_collides_with_car(obs, game.car2)) {
            if (obs->type == OBSTACLE_BANANA) {
                car_banana_slip(game.car2);
                input_set_car2_inverted(180);
            } else {
                car_take_damage(game.car2);
            }
            obs->base.is_active = false;
        }
    }

    for (int i = 0; i < game.boost_count; i++) {
        Boost *boost = game.boosts[i];
        if (boost == NULL || !boost->base.is_active) continue;

        if (boost_collides_with_car(boost, game.car1)) {
            car_apply_boost(game.car1, BOOST_TILES);
            boost->base.is_active = false;
        } else if (boost_collides_with_car(boost, game.car2)) {
            car_apply_boost(game.car2, BOOST_TILES);
            boost->base.is_active = false;
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
    switch (game.state) {
        case GAME_OVER:
            draw_clear(PAL_HUD_BG);
            win_view_draw(game.winner);
            copy_buffer_to_video();
            return;
        default:
            break;
    }

    draw_clear(PAL_BLACK);

    switch (game.state) {
        case MAIN_MENU: {
            Sprite *title     = resources_get_menu_title();
            Sprite *start_btn = resources_get_menu_start_btn();
            Sprite *exit_btn  = resources_get_menu_exit_btn();
            if (title) draw_sprite(title, (SCREEN_W - title->width) / 2, 200);
            if (start_btn) {
                if (game.menu_selection == MENU_START) {
                    int w = start_btn->width  * 9 / 8;
                    int h = start_btn->height * 9 / 8;
                    draw_sprite_scaled(start_btn, (SCREEN_W - w) / 2,
                                       420 - (h - start_btn->height) / 2, w, h);
                } else {
                    draw_sprite(start_btn, (SCREEN_W - start_btn->width) / 2, 420);
                }
            }
            if (exit_btn) {
                if (game.menu_selection == MENU_EXIT) {
                    int w = exit_btn->width  * 9 / 8;
                    int h = exit_btn->height * 9 / 8;
                    draw_sprite_scaled(exit_btn, (SCREEN_W - w) / 2,
                                       510 - (h - exit_btn->height) / 2, w, h);
                } else {
                    draw_sprite(exit_btn, (SCREEN_W - exit_btn->width) / 2, 510);
                }
            }
            draw_sprite(resources_get_cursor_sprite(), input_cursor_x(), input_cursor_y());
            break;
        }
        case GAMEPLAY:
            track_view_draw(game.track);
            scenery_view_draw(game.scenery);
            car_view_draw(game.car1);
            car_view_draw(game.car2);
            for (int i = 0; i < game.obstacle_count; i++) {
                if (obstacle_is_visible(game.obstacles[i]))
                    obstacle_view_draw(game.obstacles[i]);
            }
            for (int i = 0; i < game.boost_count; i++) {
                if (boost_is_visible(game.boosts[i]))
                    boost_view_draw(game.boosts[i]);
            }
            break;
        case GAME_OVER:
            break;
        case PAUSE:
            track_view_draw(game.track);
            scenery_view_draw(game.scenery);
            car_view_draw(game.car1);
            car_view_draw(game.car2);
            for (int i = 0; i < game.obstacle_count; i++) {
                if (obstacle_is_visible(game.obstacles[i]))
                    obstacle_view_draw(game.obstacles[i]);
            }
            for (int i = 0; i < game.boost_count; i++) {
                if (boost_is_visible(game.boosts[i]))
                    boost_view_draw(game.boosts[i]);
            }
            pause_view_draw(game.pause_selected);
            draw_sprite(resources_get_cursor_sprite(), input_cursor_x(), input_cursor_y());
            break;
        case EXIT:
            break;
    }

    copy_buffer_to_video();
}

void game_init(void) {
    resources_destroy();
    resources_load();
    input_init_cursor(SCREEN_W, SCREEN_H);
    game.state = MAIN_MENU;
    game.winner = 0;
    game.pause_selected = 0;
    game.menu_selection = 0;
    game.track = NULL;
    game.car1 = NULL;
    game.car2 = NULL;
    game.scenery = NULL;
    game.obstacle_count = 0;
    game.boost_count = 0;
}

void game_cleanup(void) {
    game_reset(&game);
    resources_destroy();
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
