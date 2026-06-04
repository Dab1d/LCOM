#ifndef CAR_H
#define CAR_H

#include "../element/element.h"
#include "../track/track.h"
#include <stdbool.h>

#define CAR_LANE_WIDTH  64   // Largura de cada faixa em píxeis
#define CAR_WIDTH  CAR_LANE_WIDTH       // largura = largura de uma faixa
#define CAR_HEIGHT TRACK_TILE_HEIGHT    // altura = altura de um tile
#define CAR_INITIAL_LIVES 3
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
    Element base;
    int player;       // 1 ou 2
    int lane;
    int lane_min;
    int lane_max;
    int track_progress;
    float boost_remaining;
    CarState state;
    int score;
    int lives;
} Car;

// Construtor / Destrutor
Car* create_car(int initial_lane, int lane_min, int lane_max, int car_width, int car_height);
void destroy_car(Car* car);

// Move o carro uma faixa: direction = -1 (esquerda) ou +1 (direita)
void car_move_lane(Car* car, int direction);

// Aplica um impacto — avança o estado de dano do carro
void car_take_damage(Car* car);

// Aplica o boost instantaneamente: incrementa track_progress em 'tiles'
void car_apply_boost(Car* car, int tiles);

// Faz deslizar o carro para uma faixa adjacente (efeito casca de banana)
void car_banana_slip(Car* car);

// Repõe o carro para o estado inicial
void reset_car(Car* car, int initial_lane);

// Inicializa score e lives com o número de vidas escolhido pelo jogador
void car_init_session(Car* car, int initial_lives);

#endif // CAR_H
