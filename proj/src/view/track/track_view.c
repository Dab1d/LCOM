#include "track_view.h"
#include "../view.h"
#include "../../model/car/car.h"
#include <stdlib.h>

// Placeholder colors per tile type
static const uint32_t TILE_COLORS[4] = {
    0x444444,  // TILE_EMPTY    - asphalt
    0x00CC44,  // TILE_BOOST    - green
    0x888888,  // TILE_OBSTACLE - unused by track view, obstacle view handles it
    0xFFFFFF,  // TILE_FINISH   - white
};

static Sprite* make_tile_sprite(uint32_t color) {
    int w = CAR_LANE_WIDTH;
    int h = TRACK_TILE_HEIGHT;

    Sprite *sp = malloc(sizeof(Sprite));
    if (!sp) return NULL;

    sp->pixmap = malloc(w * h * sizeof(uint32_t));
    if (!sp->pixmap) { free(sp); return NULL; }

    for (int i = 0; i < w * h; i++) sp->pixmap[i] = color;

    sp->x      = 0;
    sp->y      = 0;
    sp->width  = w;
    sp->height = h;
    return sp;
}

TrackView* track_view_create(void) {
    TrackView *tv = malloc(sizeof(TrackView));
    if (!tv) return NULL;

    for (int t = 0; t < 4; t++) {
        tv->tile_sprites[t] = make_tile_sprite(TILE_COLORS[t]);
        if (!tv->tile_sprites[t]) {
            for (int j = 0; j < t; j++) {
                free(tv->tile_sprites[j]->pixmap);
                free(tv->tile_sprites[j]);
            }
            free(tv);
            return NULL;
        }
    }
    return tv;
}

void track_view_draw(TrackView *tv, const Track *track) {
    if (!tv || !track) return;

    // Draw TRACK_VISIBLE_ROWS + 1 rows to fill the gap introduced by scroll_offset
    for (int screen_row = 0; screen_row <= TRACK_VISIBLE_ROWS; screen_row++) {
        int y = screen_row * TRACK_TILE_HEIGHT - (int)track->scroll_offset;

        for (int lane = 0; lane < TRACK_LANES; lane++) {
            int logical_row = track->scroll_row + screen_row;
            TileType type   = track_get_tile(track, logical_row, lane);

            Sprite *sp = tv->tile_sprites[type];
            sp->x = lane * CAR_LANE_WIDTH;
            sp->y = y;

            draw_sprite(sp);
        }
    }
}

void track_view_destroy(TrackView *tv) {
    if (!tv) return;

    for (int t = 0; t < 4; t++) {
        if (tv->tile_sprites[t]) {
            free(tv->tile_sprites[t]->pixmap);
            free(tv->tile_sprites[t]);
        }
    }
    free(tv);
}
