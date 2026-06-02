#include <lcom/lcf.h>
#include "game.h"
#include "../../controller/input/input.h"
#include "../resources/resources.h"
#include "../../view/car/car_view.h"
#include "../../view/obstacle/obstacle_view.h"
#include "../../view/track/track_view.h"
#include "../../view/scenery/scenery_view.h"
#include "../../view/view.h"
#define MAX_OBSTACLES    200
#define CLUSTER_CHANCE    70
#define BOOST_TILES       2


static GameState current_state = MAIN_MENU;
static Track*    track         = NULL;
static Car*      car1          = NULL;
static Car*      car2          = NULL;
static SceneryView* scenery_view = NULL;
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

void game_init(void) {
    current_state = GAMEPLAY;

    resources_load();

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
}

GameState game_get_state(void) {
    return current_state;
}

void game_set_state(GameState new_state) {
    current_state = new_state;
}

void game_process_collisions(void) {
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

void game_update(void) {
    track_update(track);
    for (int i = 0; i < obstacle_count; i++) {
        if (obstacles[i] != NULL)
            obstacle_update(obstacles[i], track->scroll_row, track->scroll_offset);
    }
}

void game_process_input(void) {
    if (input_esc_pressed())
        game_set_state(EXIT);
}

void game_render(void) {
    draw_clear(0x000000);

    track_view_draw(track);

    scenery_view_update(scenery_view, track);
    scenery_view_draw(scenery_view);

    car_view_update(car1);
    draw_car(car1);

    car_view_update(car2);
    draw_car(car2);

    for (int i = 0; i < obstacle_count; i++) {
        if (obstacle_is_visible(obstacles[i])) {
            obstacle_view_update(obstacles[i]);
            draw_obstacle(obstacles[i]);
        }
    }

    copy_buffer_to_video();
}
bool game_is_over(void) {
    if (!car1->base.is_active) { winner = 2; return true; }
    if (!car2->base.is_active) { winner = 1; return true; }
    if (track_is_finished(track)) {
        winner = (car1->track_progress >= car2->track_progress) ? 1 : 2;
        return true;
    }
    return false;
}
