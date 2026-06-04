/**
 * @file menu_view.h
 * @brief Main menu screen rendering.
 */

#ifndef __PROJ_MENU_VIEW_H
#define __PROJ_MENU_VIEW_H

#include "../../../model/track/track.h"

/**
 * @brief Draws the main menu screen.
 *
 * Renders the title, START and EXIT buttons (with the selected one highlighted),
 * and a preview of the currently chosen track theme in the background.
 * @param selection 0 = START highlighted, 1 = EXIT highlighted.
 * @param theme     TrackTheme currently highlighted for the race.
 */
void menu_view_draw(int selection, TrackTheme theme);

#endif /* __PROJ_MENU_VIEW_H */
