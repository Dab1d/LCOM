#include "scenery_view.h"
#include "scenery_xpm.h"
#include "../view.h"
#include "../../model/car/car.h"
#include <stdlib.h>

#define GRASS_BASE   0x3A7D44  // base green
#define GRASS_DARK   0x2A6030  // darker blade — ~25% of pixels
#define TREE_COLOR   0x1A5C1A  // dark canopy placeholder
#define GRASS_MARGIN 20

#define LEFT_X_MIN  (GRASS_MARGIN)
#define LEFT_X_MAX  (ROAD_OFFSET_X - GRASS_MARGIN - TREE_SIZE)
#define RIGHT_BASE  (ROAD_OFFSET_X + 10 * CAR_LANE_WIDTH)
#define RIGHT_X_MIN (RIGHT_BASE + GRASS_MARGIN)
#define RIGHT_X_MAX (RIGHT_BASE + 192 - GRASS_MARGIN - TREE_SIZE)

// Strips are 192px wide = 3 × 64px tiles
#define STRIP_TILES  3

static Sprite* make_grass_sprite(void) {
    int sz = TRACK_TILE_HEIGHT;  // 64×64

#if HAS_SCENERY_XPM
    return sprite_from_xpm((xpm_map_t)grass_xpm);
#else
    Sprite *sp = malloc(sizeof(Sprite));
    if (!sp) return NULL;

    sp->pixmap = malloc(sz * sz * sizeof(uint32_t));
    if (!sp->pixmap) { free(sp); return NULL; }

    for (int i = 0; i < sz * sz; i++)
        sp->pixmap[i] = (rand() % 4 == 0) ? GRASS_DARK : GRASS_BASE;

    sp->x = sp->y = 0;
    sp->width = sp->height = sz;
    return sp;
#endif
}

static Sprite* make_tree_sprite(void) {
#if HAS_SCENERY_XPM
    return sprite_from_xpm((xpm_map_t)tree_xpm);
#else
    Sprite *sp = malloc(sizeof(Sprite));
    if (!sp) return NULL;

    sp->pixmap = malloc(TREE_SIZE * TREE_SIZE * sizeof(uint32_t));
    if (!sp->pixmap) { free(sp); return NULL; }

    for (int i = 0; i < TREE_SIZE * TREE_SIZE; i++) sp->pixmap[i] = TREE_COLOR;

    sp->x = sp->y = 0;
    sp->width = sp->height = TREE_SIZE;
    return sp;
#endif
}

SceneryView* scenery_view_create(void) {
    SceneryView *sv = malloc(sizeof(SceneryView));
    if (!sv) return NULL;

    sv->grass_sprite = make_grass_sprite();
    sv->tree_sprite  = make_tree_sprite();
    sv->scroll_offset = 0.0f;

    if (!sv->grass_sprite || !sv->tree_sprite) {
        sprite_destroy(sv->grass_sprite);
        sprite_destroy(sv->tree_sprite);
        free(sv);
        return NULL;
    }

    sv->count = 0;
    int left_range  = LEFT_X_MAX  - LEFT_X_MIN  + 1;
    int right_range = RIGHT_X_MAX - RIGHT_X_MIN + 1;

    for (int row = 0; row < TRACK_TOTAL_ROWS && sv->count < MAX_TREES - 2; row += 4) {
        int actual_row = row + rand() % 3;

        if (rand() % 10 < 7) {
            sv->trees[sv->count].logical_row = actual_row;
            sv->trees[sv->count].screen_x    = LEFT_X_MIN + rand() % left_range;
            sv->trees[sv->count].screen_y    = 0;
            sv->count++;
        }

        if (rand() % 10 < 7 && sv->count < MAX_TREES) {
            sv->trees[sv->count].logical_row = actual_row;
            sv->trees[sv->count].screen_x    = RIGHT_X_MIN + rand() % right_range;
            sv->trees[sv->count].screen_y    = 0;
            sv->count++;
        }
    }

    return sv;
}

void scenery_view_update(SceneryView *sv, const Track *track) {
    if (!sv || !track) return;

    sv->scroll_offset = track->scroll_offset;

    for (int i = 0; i < sv->count; i++) {
        int screen_row = sv->trees[i].logical_row - track->scroll_row;
        sv->trees[i].screen_y = (double)(screen_row * TRACK_TILE_HEIGHT) - (double)track->scroll_offset;
    }
}

void scenery_view_draw(SceneryView *sv) {
    if (!sv) return;

    int tile  = TRACK_TILE_HEIGHT;  // 64 — grass tiles are square
    int off   = (int)sv->scroll_offset;
    int road_end = ROAD_OFFSET_X + 10 * CAR_LANE_WIDTH;

    // Tile grass across both strips, scrolling with the track
    for (int screen_row = 0; screen_row <= TRACK_VISIBLE_ROWS; screen_row++) {
        int y = screen_row * tile - off;

        for (int col = 0; col < STRIP_TILES; col++) {
            sv->grass_sprite->x = col * tile;
            sv->grass_sprite->y = y;
            draw_sprite(sv->grass_sprite);

            sv->grass_sprite->x = road_end + col * tile;
            sv->grass_sprite->y = y;
            draw_sprite(sv->grass_sprite);
        }
    }

    // Trees on top of grass
    int screen_height = TRACK_VISIBLE_ROWS * tile;
    for (int i = 0; i < sv->count; i++) {
        int y = (int)sv->trees[i].screen_y;
        if (y + TREE_SIZE < 0 || y >= screen_height) continue;

        sv->tree_sprite->x = sv->trees[i].screen_x;
        sv->tree_sprite->y = y;
        draw_sprite(sv->tree_sprite);
    }
}

void scenery_view_destroy(SceneryView *sv) {
    if (!sv) return;
    sprite_destroy(sv->grass_sprite);
    sprite_destroy(sv->tree_sprite);
    free(sv);
}
