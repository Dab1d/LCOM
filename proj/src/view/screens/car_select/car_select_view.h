/**
 * @file car_select_view.h
 * @brief Car-skin selection screen rendering.
 */

#ifndef __PROJ_CAR_SELECT_VIEW_H
#define __PROJ_CAR_SELECT_VIEW_H

/**
 * @brief Draws the car-selection screen showing each player's currently chosen skin.
 * @param p1_fmt    Format index currently selected by player 1 (0..fmt_count-1).
 * @param p2_fmt    Format index currently selected by player 2 (0..fmt_count-1).
 * @param fmt_count Total number of available car formats.
 */
void car_select_view_draw(int p1_fmt, int p2_fmt, int fmt_count);

#endif /* __PROJ_CAR_SELECT_VIEW_H */
