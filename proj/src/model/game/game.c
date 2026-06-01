#include <lcom/lcf.h>
#include "game.h"
#include "../../controller/input/input.h"
#include "../../view/car/car_view.h"
#include "../../view/obstacle/obstacle_view.h"
#include "../../view/track/track_view.h"
#include "../../view/view.h"
#define MAX_OBSTACLES ((TRACK_TOTAL_ROWS / 8) * 2) // conta para uma distribuição equilibrada de obstacles


static GameState current_state = MAIN_MENU;
static Track*    track          = NULL;
static Car*      car1           = NULL;
static Car*      car2           = NULL;
static CarView*   car1_view      = NULL;
static CarView*   car2_view      = NULL;
static TrackView* track_view     = NULL;
static Obstacle*     obstacles[MAX_OBSTACLES];
static ObstacleView* obstacle_views[MAX_OBSTACLES];
static int           obstacle_count = 0;
static int       winner         = 0;


void game_init(void) {
    current_state = MAIN_MENU;
    track = create_track(TRACK_THEME_CITY);

    // Jogador 1: faixas 0-4, começa na faixa 2 (centro da sua metade)
    car1 = create_car(2, PLAYER1_LANE_START, PLAYER1_LANE_END, CAR_WIDTH, CAR_HEIGHT);

    // Jogador 2: faixas 5-9, começa na faixa 7 (centro da sua metade)
    car2 = create_car(7, PLAYER2_LANE_START, PLAYER2_LANE_END, CAR_WIDTH, CAR_HEIGHT);

    car1_view  = car_view_create(CAR_WIDTH, CAR_HEIGHT);
    car2_view  = car_view_create(CAR_WIDTH, CAR_HEIGHT);
    track_view = track_view_create();

    winner = 0;
    obstacle_count = 0;
    for (int row = 10; row < TRACK_TOTAL_ROWS - 10 && obstacle_count < MAX_OBSTACLES - 1; row += 8) {
        obstacles[obstacle_count] = create_obstacle(row, PLAYER1_LANE_START, PLAYER1_LANE_END);
        obstacle_views[obstacle_count] = obstacle_view_create(obstacles[obstacle_count]->base.width,
                                                              obstacles[obstacle_count]->base.height);
        obstacle_count++;

        obstacles[obstacle_count] = create_obstacle(row + 4, PLAYER2_LANE_START, PLAYER2_LANE_END);
        obstacle_views[obstacle_count] = obstacle_view_create(obstacles[obstacle_count]->base.width,
                                                              obstacles[obstacle_count]->base.height);
        obstacle_count++;
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

        if (obstacle_collides_with_car(obs, car1->lane, CAR_SCREEN_ROW)) {
            car_take_damage(car1);
            obs->base.is_active = false;
        }
        if (obstacle_collides_with_car(obs, car2->lane, CAR_SCREEN_ROW)) {
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
