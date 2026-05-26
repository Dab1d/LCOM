#include <lcom/lcf.h>
#include "game.h"

static GameState current_state = MAIN_MENU;

void game_init(void) {
    current_state = MAIN_MENU;
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