#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../element/element.h"
#include "../track/track.h"

// Tamanhos mínimos e máximos de um obstáculo em tiles
#define OBSTACLE_MIN_LANES 1
#define OBSTACLE_MAX_LANES 3  // Nunca pode bloquear todas as faixas de um jogador (max 5)
#define OBSTACLE_MIN_ROWS  1
#define OBSTACLE_MAX_ROWS  2

/**
 * @brief Representa um obstáculo na pista.
 * Ocupa uma região retangular da grelha (lane_start..lane_end, row_start..row_end).
 * O Element base guarda a posição em píxeis para colisão e desenho.
 */
typedef struct {
    Element base;       // Posição em píxeis, hitbox, is_active, sprite
    int lane_start;     // Faixa onde o obstáculo começa (inclusive)
    int lane_end;       // Faixa onde o obstáculo termina (inclusive)
    int row_start;      // Linha lógica onde começa na grelha
    int row_end;        // Linha lógica onde termina na grelha
} Obstacle;

/**
 * @brief Cria um obstáculo com dimensões aleatórias dentro dos limites dados.
 * lane_min e lane_max definem a metade da pista onde pode aparecer
 * (garante que não atravessa para a metade do outro jogador).
 */
Obstacle* create_obstacle(int row_start, int lane_min, int lane_max);
void      destroy_obstacle(Obstacle* obs);

/**
 * @brief Atualiza a posição em píxeis do obstáculo com base no scroll atual da pista.
 * Deve ser chamado a cada tick antes de desenhar.
 */
void obstacle_update(Obstacle* obs, int scroll_row, int scroll_offset);

/**
 * @brief Verifica se o obstáculo está dentro da zona visível do ecrã.
 * Evita desenhar ou processar colisões com obstáculos fora de vista.
 */
bool obstacle_is_visible(const Obstacle* obs);

/**
 * @brief Verifica se um carro numa dada faixa e linha de ecrã colide com este obstáculo.
 */
bool obstacle_collides_with_car(const Obstacle* obs, int car_lane, int car_screen_row);

#endif // OBSTACLE_H
