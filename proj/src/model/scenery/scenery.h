#ifndef __PROJ_SCENERY_H
#define __PROJ_SCENERY_H

#include "../elements/track/track.h"

#define MAX_TREES 120
#define TREE_SIZE  32

typedef struct {
    int    screen_x;
    int    logical_row;
    double screen_y;
} TreeInstance;

typedef struct {
    TreeInstance trees[MAX_TREES];
    int          count;
    float        scroll_offset;
} Scenery;

Scenery* scenery_create(TrackTheme theme);
void     scenery_update(Scenery *s, const Track *track);
void     scenery_destroy(Scenery *s);

#endif /* __PROJ_SCENERY_H */
