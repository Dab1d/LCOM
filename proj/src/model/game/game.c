#include <lcom/lcf.h>
#include "game.h"
#define MAX_OBSTACLES ((TRACK_TOTAL_ROWS / 8) * 2) // conta para uma distribuição equilibrada de obstacles


static GameState current_state = MAIN_MENU;
static Track*    track          = NULL;
static Car*      car1           = NULL;
static Car*      car2           = NULL;
static Obstacle* obstacles[MAX_OBSTACLES];
static int       obstacle_count = 0;
static int       winner         = 0;


void game_init(void) {
    current_state = MAIN_MENU;
    track = create_track(TRACK_THEME_CITY);

    // Jogador 1: faixas 0-4, começa na faixa 2 (centro da sua metade)
    car1 = create_car(2, PLAYER1_LANE_START, PLAYER1_LANE_END, CAR_WIDTH, CAR_HEIGHT);

    // Jogador 2: faixas 5-9, começa na faixa 7 (centro da sua metade)
    car2 = create_car(7, PLAYER2_LANE_START, PLAYER2_LANE_END, CAR_WIDTH, CAR_HEIGHT);

    winner = 0;
    obstacle_count = 0;
    for (int row = 10; row < TRACK_TOTAL_ROWS - 10 && obstacle_count < MAX_OBSTACLES - 1; row += 8) {
        obstacles[obstacle_count++] = create_obstacle(row,     PLAYER1_LANE_START, PLAYER1_LANE_END);
        obstacles[obstacle_count++] = create_obstacle(row + 4, PLAYER2_LANE_START, PLAYER2_LANE_END);
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
    // TODO: ler teclado/rato e mover carros
}

void game_render(void) {
    // TODO: desenhar pista, carros e obstáculos
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
