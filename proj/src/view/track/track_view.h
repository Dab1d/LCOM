#ifndef __PROJ_TRACK_VIEW_H
#define __PROJ_TRACK_VIEW_H

#include "../../model/track/track.h"
#include "../../model/sprite/sprite.h"

typedef struct {
    Sprite *tile_sprites[4];  // indexed by TileType
} TrackView;

TrackView* track_view_create(void);
void       track_view_draw(TrackView *tv, const Track *track);
void       track_view_destroy(TrackView *tv);

#endif /* __PROJ_TRACK_VIEW_H */
