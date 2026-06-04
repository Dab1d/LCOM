/**
 * @file hud_view.h
 * @brief HUD rendering: score, speed, and progress bars for both players.
 */

#ifndef __PROJ_HUD_VIEW_H
#define __PROJ_HUD_VIEW_H

#include "../../../model/elements/car/car.h"

/**
 * @brief Draws the full HUD overlay for both players.
 *
 * Renders score, track progress, and damage state indicators
 * at the top and bottom of the screen.
 * @param car1 Player 1 car (read-only).
 * @param car2 Player 2 car (read-only).
 */
void hud_view_draw(const Car *car1, const Car *car2);

#endif /* __PROJ_HUD_VIEW_H */
