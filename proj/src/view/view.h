#ifndef __PROJ_VIEW_H
#define __PROJ_VIEW_H

#include "../../model/game/game.h"

/**
 * @brief Renders one frame for the current game state.
 *        Call once per timer tick inside the main loop.
 */
void view_render(GameState state);

#endif /* __PROJ_VIEW_H */
