#include <lcom/lcf.h>
#include "game.h"
#include "../../controller/input/input.h"
#include "../resources/resources.h"
#include "../../view/car/car_view.h"
#include "../../view/obstacle/obstacle_view.h"
#include "../../view/track/track_view.h"
#include "../../view/scenery/scenery_view.h"
#include "../../view/view.h"
#include "../../controller/palette/palette.h"

#define MAX_OBSTACLES    200
#define CLUSTER_CHANCE    70
#define BOOST_TILES       2

typedef enum { MENU_START, MENU_EXIT } MenuOption;

static GameState    current_state  = MAIN_MENU;
static MenuOption   menu_selection = MENU_START;
static Track*       track          = NULL;
static Car*         car1           = NULL;
static Car*         car2           = NULL;
static SceneryView* scenery_view   = NULL;
static Obstacle*    obstacles[MAX_OBSTACLES];
static int          obstacle_count = 0;
static int          winner         = 0;

static void spawn_single(int row, int lane_min, int lane_max) {
    if (obstacle_count >= MAX_OBSTACLES) return;
    int lane = lane_min + rand() % (lane_max - lane_min + 1);
    obstacles[obstacle_count] = create_obstacle(row, lane);
    obstacle_count++;
}

static void spawn_cluster(int base_row, int lane_min, int lane_max) {
    int available = lane_max - lane_min + 1;
    int size      = 2 + rand() % 2;

    if (rand() % 2) {
        int start = lane_min + rand() % (available - size + 1);
        for (int i = 0; i < size && obstacle_count < MAX_OBSTACLES; i++) {
            obstacles[obstacle_count] = create_obstacle(base_row, start + i);
            obstacle_count++;
        }
    } else {
        int lane = lane_min + rand() % available;
        for (int i = 0; i < size && obstacle_count < MAX_OBSTACLES; i++) {
            obstacles[obstacle_count] = create_obstacle(base_row + i, lane);
            obstacle_count++;
        }
    }
}

static void game_start(void);

static void game_process_input(void) {
    switch (current_state) {
        case MAIN_MENU:
            if (input_esc_pressed()) { current_state = EXIT; break; }
            /* keyboard navigation */
            if (input_menu_nav_up())   menu_selection = MENU_START;
            if (input_menu_nav_down()) menu_selection = MENU_EXIT;
            /* mouse hover */
            if (input_mouse_over_start()) menu_selection = MENU_START;
            if (input_mouse_over_exit())  menu_selection = MENU_EXIT;
            /* confirm selection */
            if (input_keyboard_start_pressed()) {
                if (menu_selection == MENU_START) game_start();
                else current_state = EXIT;
            }
            if (input_mouse_start_pressed()) game_start();
            if (input_mouse_exit_pressed())  current_state = EXIT;
            break;
        case GAMEPLAY:
            if (input_esc_pressed())
                current_state = MAIN_MENU;
            /* car1: arrows */
            if (input_keyboard_car_left_pressed())  car_move_lane(car1, -1);
            if (input_keyboard_car_right_pressed()) car_move_lane(car1, +1);
            /* car2: mouse */
            if (input_mouse_car2_left())  car_move_lane(car2, -1);
            if (input_mouse_car2_right()) car_move_lane(car2, +1);
            break;
        case PAUSE:
            break;
        case GAME_OVER:
            if (input_gameover_restart_pressed())
                game_start();
            if (input_gameover_menu_pressed())
                current_state = MAIN_MENU;
            break;
        case EXIT:
            break;
    }
}

static void game_update(void) {
    track_update(track);
    for (int i = 0; i < obstacle_count; i++) {
        if (obstacles[i] != NULL)
            obstacle_update(obstacles[i], track->scroll_row, track->scroll_offset);
    }
}

static void game_process_collisions(void) {
    for (int i = 0; i < obstacle_count; i++) {
        Obstacle* obs = obstacles[i];
        if (obs == NULL || !obs->base.is_active) continue;

        if (car1->base.is_active && obstacle_collides_with_car(obs, car1)) {
            car_take_damage(car1);
            obs->base.is_active = false;
        }
        if (car2->base.is_active && obstacle_collides_with_car(obs, car2)) {
            car_take_damage(car2);
            obs->base.is_active = false;
        }
    }

    if (car1->base.is_active) {
        int c1_screen_row  = (int)(car1->base.y / TRACK_TILE_HEIGHT);
        int c1_logical_row = track->scroll_row + c1_screen_row;
        TileType t1 = track_get_tile(track, c1_logical_row, car1->lane);
        if (t1 == TILE_OBSTACLE) {
            car_take_damage(car1);
            track_clear_tile(track, c1_logical_row, car1->lane);
        } else if (t1 == TILE_BOOST) {
            car_apply_boost(car1, BOOST_TILES);
            track_clear_tile(track, c1_logical_row, car1->lane);
        }
    }

    if (car2->base.is_active) {
        int c2_screen_row  = (int)(car2->base.y / TRACK_TILE_HEIGHT);
        int c2_logical_row = track->scroll_row + c2_screen_row;
        TileType t2 = track_get_tile(track, c2_logical_row, car2->lane);
        if (t2 == TILE_OBSTACLE) {
            car_take_damage(car2);
            track_clear_tile(track, c2_logical_row, car2->lane);
        } else if (t2 == TILE_BOOST) {
            car_apply_boost(car2, BOOST_TILES);
            track_clear_tile(track, c2_logical_row, car2->lane);
        }
    }
}

static bool game_is_over(void) {
    if (!car1->base.is_active) { winner = 2; return true; }
    if (!car2->base.is_active) { winner = 1; return true; }
    if (track_is_finished(track)) {
        winner = (car1->track_progress >= car2->track_progress) ? 1 : 2;
        return true;
    }
    return false;
}

#define SCREEN_W 1024
#define SCREEN_H  768

static void game_render(void) {
    draw_clear(PAL_BLACK);

    switch (current_state) {
        case MAIN_MENU: {
            Sprite *title     = resources_get_menu_title();
            Sprite *start_btn = resources_get_menu_start_btn();
            Sprite *exit_btn  = resources_get_menu_exit_btn();
            if (title) draw_sprite(title, (SCREEN_W - title->width) / 2, 200);
            /* hovered button drawn at 9/8 scale, kept vertically centred */
            if (start_btn) {
                if (menu_selection == MENU_START) {
                    int w = start_btn->width  * 9 / 8;
                    int h = start_btn->height * 9 / 8;
                    draw_sprite_scaled(start_btn, (SCREEN_W - w) / 2,
                                       420 - (h - start_btn->height) / 2, w, h);
                } else {
                    draw_sprite(start_btn, (SCREEN_W - start_btn->width) / 2, 420);
                }
            }
            if (exit_btn) {
                if (menu_selection == MENU_EXIT) {
                    int w = exit_btn->width  * 9 / 8;
                    int h = exit_btn->height * 9 / 8;
                    draw_sprite_scaled(exit_btn, (SCREEN_W - w) / 2,
                                       510 - (h - exit_btn->height) / 2, w, h);
                } else {
                    draw_sprite(exit_btn, (SCREEN_W - exit_btn->width) / 2, 510);
                }
            }
            break;
        }
        case GAMEPLAY:
            track_view_draw(track);
            scenery_view_update(scenery_view, track);
            scenery_view_draw(scenery_view);
            car_view_draw(car1);
            car_view_draw(car2);
            for (int i = 0; i < obstacle_count; i++) {
                if (obstacle_is_visible(obstacles[i]))
                    obstacle_view_draw(obstacles[i]);
            }
            break;
        case GAME_OVER:
            break;
        case PAUSE:
        case EXIT:
            break;
    }

    copy_buffer_to_video();
}

static void game_start(void) {
    track = create_track(TRACK_THEME_CITY);
    car1  = create_car(2, PLAYER1_LANE_START, PLAYER1_LANE_END, CAR_WIDTH, CAR_HEIGHT);
    car1->player = 1;
    car2  = create_car(7, PLAYER2_LANE_START, PLAYER2_LANE_END, CAR_WIDTH, CAR_HEIGHT);
    car2->player = 2;
    scenery_view = scenery_view_create();

    winner = 0;
    obstacle_count = 0;
    for (int row = 10; row < TRACK_TOTAL_ROWS - 10 && obstacle_count < MAX_OBSTACLES - 6; row += 8) {
        if (rand() % 100 < CLUSTER_CHANCE)
            spawn_cluster(row, PLAYER1_LANE_START, PLAYER1_LANE_END);
        else
            spawn_single(row, PLAYER1_LANE_START, PLAYER1_LANE_END);

        if (rand() % 100 < CLUSTER_CHANCE)
            spawn_cluster(row + 4, PLAYER2_LANE_START, PLAYER2_LANE_END);
        else
            spawn_single(row + 4, PLAYER2_LANE_START, PLAYER2_LANE_END);
    }

    current_state = GAMEPLAY;
}

void game_init(void) {
    resources_destroy();
    resources_load();
    input_init_cursor(SCREEN_W, SCREEN_H);
    menu_selection = MENU_START;
    current_state  = MAIN_MENU;
}

GameState game_get_state(void) {
    return current_state;
}

void game_set_state(GameState new_state) {
    current_state = new_state;
}

void game_tick(void) {
    game_process_input();

    switch (current_state) {
        case GAMEPLAY:
            game_update();
            game_process_collisions();
            if (game_is_over())
                current_state = GAME_OVER;
            break;
        case MAIN_MENU:
        case PAUSE:
        case GAME_OVER:
        case EXIT:
            break;
    }

    game_render();
}
