/**
 * @file shield.h
 * @brief Shield pickup: grants the collecting car 5 seconds of invulnerability.
 */

#ifndef SHIELD_H
#define SHIELD_H

#include "../element/element.h"
#include "../track/track.h"
#include "../car/car.h"

#define SHIELD_DURATION_TICKS 300 /**< 5 seconds at 60 Hz. */

/**
 * @brief Represents a shield pickup on the track.
 */
typedef struct {
    Element base; /**< Pixel position, hitbox, active flag, and sprite. */
    int     lane; /**< Logical lane index (0–9). */
    int     row;  /**< Logical row index in the track grid. */
} Shield;

Shield* create_shield(int row, int lane);
void    destroy_shield(Shield *shield);
void    shield_update(Shield *shield, int scroll_row, float scroll_offset);
bool    shield_is_visible(const Shield *shield);
bool    shield_collides_with_car(const Shield *shield, const Car *car);

#endif /* SHIELD_H */
