#include <lcom/lcf.h>
#include "game.h"
#include "../../controller/input/input.h"
#include "../../view/car/car_view.h"
#include "../../view/obstacle/obstacle_view.h"
#include "../../view/track/track_view.h"
#include "../../view/scenery/scenery_view.h"
#include "../../view/view.h"
#define MAX_OBSTACLES    200
#define CLUSTER_CHANCE    70  // % chance of cluster vs single obstacle


static GameState current_state = MAIN_MENU;
static Track*    track          = NULL;
static Car*      car1           = NULL;
static Car*      car2           = NULL;
static CarView*   car1_view      = NULL;
static CarView*   car2_view      = NULL;
static TrackView*   track_view    = NULL;
static SceneryView* scenery_view  = NULL;
static Obstacle*     obstacles[MAX_OBSTACLES];
static ObstacleView* obstacle_views[MAX_OBSTACLES];
static int           obstacle_count = 0;
static int       winner         = 0;


static void spawn_single(int row, int lane_min, int lane_max) {
    if (obstacle_count >= MAX_OBSTACLES) return;
    int lane = lane_min + rand() % (lane_max - lane_min + 1);
    obstacles[obstacle_count]      = create_obstacle(row, lane);
    obstacle_views[obstacle_count] = obstacle_view_create();
    obstacle_count++;
}

static void spawn_cluster(int base_row, int lane_min, int lane_max) {
    int available = lane_max - lane_min + 1;
    int size      = 2 + rand() % 2;  // 2 or 3 tiles

    if (rand() % 2) {
        // Horizontal: same row, adjacent lanes (leaves at least 2 free lanes)
        int start = lane_min + rand() % (available - size + 1);
        for (int i = 0; i < size && obstacle_count < MAX_OBSTACLES; i++) {
            obstacles[obstacle_count]      = create_obstacle(base_row, start + i);
            obstacle_views[obstacle_count] = obstacle_view_create();
            obstacle_count++;
        }
    } else {
        // Vertical: same lane, consecutive rows
        int lane = lane_min + rand() % available;
        for (int i = 0; i < size && obstacle_count < MAX_OBSTACLES; i++) {
            obstacles[obstacle_count]      = create_obstacle(base_row + i, lane);
            obstacle_views[obstacle_count] = obstacle_view_create();
            obstacle_count++;
        }
    }
}

void game_init(void) {
    current_state = MAIN_MENU;
    track = create_track(TRACK_THEME_CITY);

    // Jogador 1: faixas 0-4, começa na faixa 2 (centro da sua metade)
    car1 = create_car(2, PLAYER1_LANE_START, PLAYER1_LANE_END, CAR_WIDTH, CAR_HEIGHT);

    // Jogador 2: faixas 5-9, começa na faixa 7 (centro da sua metade)
    car2 = create_car(7, PLAYER2_LANE_START, PLAYER2_LANE_END, CAR_WIDTH, CAR_HEIGHT);

    car1_view  = car_view_create(CAR_WIDTH, CAR_HEIGHT);
    car2_view  = car_view_create(CAR_WIDTH, CAR_HEIGHT);
    track_view   = track_view_create();
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

        if (obstacle_collides_with_car(obs, car1->lane)) {
            car_take_damage(car1);
            obs->base.is_active = false;
        }
        if (obstacle_collides_with_car(obs, car2->lane)) {
            car_take_damage(car2);
            obs->base.is_active = false;
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

    track_view_draw(track_view, track);

    scenery_view_update(scenery_view, track);
    scenery_view_draw(scenery_view);

    car_view_update(car1_view, car1);
    draw_car(car1);

    car_view_update(car2_view, car2);
    draw_car(car2);

    for (int i = 0; i < obstacle_count; i++) {
        if (obstacle_is_visible(obstacles[i])) {
            obstacle_view_update(obstacle_views[i], obstacles[i]);
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
