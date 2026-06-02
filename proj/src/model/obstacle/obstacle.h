#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../element/element.h"
#include "../track/track.h"

/**
 * @brief Representa um obstáculo de um tile (CAR_LANE_WIDTH x TRACK_TILE_HEIGHT).
 * Obstáculos são sempre 1 faixa × 1 linha; clusters são criados em game.c.
 */
typedef struct {
    Element base;  // posição em píxeis, hitbox, is_active, sprite
    int lane;      // faixa lógica do obstáculo
    int row;       // linha lógica do obstáculo
} Obstacle;

Obstacle* create_obstacle(int row, int lane);
void      destroy_obstacle(Obstacle* obs);

/**
 * @brief Atualiza a posição em píxeis do obstáculo com base no scroll atual da pista.
 * Deve ser chamado a cada tick antes de desenhar.
 */
void obstacle_update(Obstacle* obs, int scroll_row, float scroll_offset);
bool obstacle_is_visible(const Obstacle* obs);
bool obstacle_collides_with_car(const Obstacle* obs, int car_lane);

#endif // OBSTACLE_H
