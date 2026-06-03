#ifndef __PROJ_SCENERY_VIEW_H
#define __PROJ_SCENERY_VIEW_H

#include "../../model/track/track.h"

#define MAX_TREES  120
#define TREE_SIZE   32

typedef struct {
    int    screen_x;
    int    logical_row;
    double screen_y;
} TreeInstance;

typedef struct {
    TreeInstance trees[MAX_TREES];
    int          count;
    float        scroll_offset;
} SceneryView;

SceneryView* scenery_view_create(void);
void         scenery_view_update(SceneryView *sv, const Track *track);
void         scenery_view_draw(SceneryView *sv);
void         scenery_view_destroy(SceneryView *sv);

#endif /* __PROJ_SCENERY_VIEW_H */
