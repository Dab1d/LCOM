/**
 * @file win_view.h
 * @brief Win/result screen rendering.
 */

#ifndef __PROJ_WIN_VIEW_H
#define __PROJ_WIN_VIEW_H

/** @defgroup win_layout Win screen car position (screen 1024×768, car 64×64)
 * @{ */
#define WIN_CAR_X 480 /**< Car sprite left edge: (1024 - 64) / 2. */
#define WIN_CAR_Y 352 /**< Car sprite top edge: (768 - 64) / 2. */
/** @} */

/**
 * @brief Draws the race result screen showing the winning player.
 * @param winner 1 = player 1 won (blue car), 2 = player 2 won (red car).
 */
void win_view_draw(int winner);

#endif /* __PROJ_WIN_VIEW_H */
