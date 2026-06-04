/**
 * @file car_view.h
 * @brief Car rendering: draws a car sprite at its current screen position.
 */

#ifndef __PROJ_CAR_VIEW_H
#define __PROJ_CAR_VIEW_H

#include "../../../model/car/car.h"

/**
 * @brief Draws the car sprite corresponding to its current CarState.
 * @param car Car to render.
 */
void car_view_draw(Car *car);

#endif /* __PROJ_CAR_VIEW_H */
