/**
 * @file biome_select_view.h
 * @brief Biome-selection screen rendering.
 */

#ifndef __PROJ_BIOME_SELECT_VIEW_H
#define __PROJ_BIOME_SELECT_VIEW_H

#include "../../../model/terrain/track/track.h"

/**
 * @brief Draws the biome-selection screen with the currently highlighted biome.
 * @param selected TrackTheme value of the biome currently highlighted by the player.
 */
void biome_select_view_draw(TrackTheme selected);

#endif /* __PROJ_BIOME_SELECT_VIEW_H */
