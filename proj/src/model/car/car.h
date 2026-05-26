#ifndef CAR_H
#define CAR_H

#include "../element/element.h"
#include <stdbool.h>

#define TRACK_LANES     4
#define CAR_LANE_WIDTH  100  // Largura de cada faixa em píxeis

/**
 * @brief Os 4 estados visuais/de saúde do carro.
 * O índice corresponde diretamente ao sprite a carregar na View.
 */
typedef enum {
    CAR_STATE_NORMAL   = 0,  // Carro em perfeito estado
    CAR_STATE_DAMAGED  = 1,  // Primeiro impacto
    CAR_STATE_BURNING  = 2,  // Segundo impacto — em chamas
    CAR_STATE_EXPLODED = 3   // Terceiro impacto — fora da corrida
} CarState;

/**
 * @brief Estrutura que representa um carro jogador.
 */
typedef struct {
    Element base;        // Posição, hitbox, is_active, sprite (View injeta)
    int lane;            // Faixa atual: 0 (esquerda) a TRACK_LANES-1 (direita)
    int track_progress;  // Progresso na pista em tiles — aumenta com o tempo e com boosts
    CarState state;      // Estado atual de dano — determina o sprite ativo
} Car;

// Construtor / Destrutor
Car* create_car(int initial_lane, int car_width, int car_height);
void destroy_car(Car* car);

// Move o carro uma faixa: direction = -1 (esquerda) ou +1 (direita)
void car_move_lane(Car* car, int direction);

// Aplica um impacto — avança o estado de dano do carro
void car_take_damage(Car* car);

// Aplica o boost instantaneamente: incrementa track_progress em 'tiles'
void car_apply_boost(Car* car, int tiles);

// Repõe o carro para o estado inicial
void reset_car(Car* car, int initial_lane);

#endif // CAR_H