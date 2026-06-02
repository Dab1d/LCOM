#ifndef __PROJ_SCENERY_VIEW_H
#define __PROJ_SCENERY_VIEW_H

#include "../../model/track/track.h"
#include "../../model/sprite/sprite.h"

#define MAX_TREES  120
#define TREE_SIZE   32  // square sprite, centered in the grass strip

typedef struct {
    int    screen_x;    // fixed screen x (within grass strip)
    int    logical_row; // track row — used to compute scroll y
    double screen_y;    // updated each tick
} TreeInstance;

typedef struct {
    TreeInstance trees[MAX_TREES];
    int          count;
    Sprite      *grass_sprite;
    Sprite      *tree_sprite;
    float        scroll_offset;  // cached from last update, used in draw
} SceneryView;

SceneryView* scenery_view_create(void);
void         scenery_view_update(SceneryView *sv, const Track *track);
void         scenery_view_draw(SceneryView *sv);
void         scenery_view_destroy(SceneryView *sv);

#endif /* __PROJ_SCENERY_VIEW_H */
