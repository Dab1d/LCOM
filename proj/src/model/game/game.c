#include <lcom/lcf.h>
#include "game.h"

static GameState current_state = MAIN_MENU;

void game_init(void) {
    current_state = MAIN_MENU;
    track = create_track(TRACK_THEME_CITY);

    // Jogador 1: faixas 0-4, começa na faixa 2 (centro da sua metade)
    car1 = create_car(2, PLAYER1_LANE_START, PLAYER1_LANE_END, CAR_WIDTH, CAR_HEIGHT);

    // Jogador 2: faixas 5-9, começa na faixa 7 (centro da sua metade)
    car2 = create_car(7, PLAYER2_LANE_START, PLAYER2_LANE_END, CAR_WIDTH, CAR_HEIGHT);

    winner = 0;
}

GameState game_get_state(void) {
    return current_state;
}

void game_set_state(GameState new_state) {
    current_state = new_state;
}

void game_process_collisions(void) {
    // TODO: quando Car e Obstacle existirem:
    // for cada obstáculo ativo:
    //     if (check_collision(&car1->base, &obs->base)) car_take_damage(car1);
    //     if (check_collision(&car2->base, &obs->base)) car_take_damage(car2);
}