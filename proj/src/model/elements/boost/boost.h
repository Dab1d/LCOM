#ifndef BOOST_H
#define BOOST_H

#include "../element/element.h"
#include "../track/track.h"
#include "../car/car.h"

/**
 * @brief Representa um boost na pista.
 * Ocupa exatamente 1 faixa × 1 tile. Quando um carro passa por cima,
 * avança o seu track_progress e o boost é desativado.
 */
typedef struct {
    Element base;  // Posição em píxeis, hitbox, is_active, sprite
    int lane;      // Faixa lógica (0–9)
    int row;       // Linha lógica na grelha
} Boost;

Boost* create_boost(int row, int lane);
void   destroy_boost(Boost* boost);

/**
 * @brief Atualiza a posição em píxeis do boost com base no scroll atual da pista.
 * Desativa automaticamente quando sai pelo topo do ecrã.
 */
void boost_update(Boost* boost, int scroll_row, float scroll_offset);

/**
 * @brief Verifica se o boost está dentro da zona visível do ecrã.
 */
bool boost_is_visible(const Boost* boost);

/**
 * @brief Verifica se um carro colide com este boost (AABB + faixa).
 */
bool boost_collides_with_car(const Boost* boost, const Car* car);

#endif // BOOST_H
