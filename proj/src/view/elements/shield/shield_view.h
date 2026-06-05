/**
 * @file shield_view.h
 * @brief Shield pickup rendering.
 */

#ifndef __PROJ_SHIELD_VIEW_H
#define __PROJ_SHIELD_VIEW_H

#include "../../../model/elements/shield/shield.h"
#include "../../../model/elements/car/car.h"

void shield_view_draw(Shield *shield);
void shield_aura_draw(Car *car);

#endif /* __PROJ_SHIELD_VIEW_H */
