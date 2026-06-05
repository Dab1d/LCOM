#ifndef __PROJ_BIOME_SELECT_VIEW_H
#define __PROJ_BIOME_SELECT_VIEW_H

#include "../../../model/terrain/track/track.h"

#define BIOME_LARROW_X      100
#define BIOME_RARROW_X      884
#define BIOME_ARROW_Y       390
#define BIOME_ARROW_HIT      60
#define BIOME_SELECT_BTN_X  384
#define BIOME_SELECT_BTN_Y  650
#define BIOME_SELECT_BTN_W  256
#define BIOME_SELECT_BTN_H   64

void biome_select_view_draw(TrackTheme selected);

#endif /* __PROJ_BIOME_SELECT_VIEW_H */
