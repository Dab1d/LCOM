#include "scenery_view.h"
#include "../../model/resources/resources.h"
#include "../view.h"
#include "../../model/car/car.h"
#include <stdlib.h>

#define GRASS_MARGIN 20

#define LEFT_X_MIN  (GRASS_MARGIN)
#define LEFT_X_MAX  (ROAD_OFFSET_X - GRASS_MARGIN - TREE_SIZE)
#define RIGHT_BASE  (ROAD_OFFSET_X + 10 * CAR_LANE_WIDTH)
#define RIGHT_X_MIN (RIGHT_BASE + GRASS_MARGIN)
#define RIGHT_X_MAX (RIGHT_BASE + 192 - GRASS_MARGIN - TREE_SIZE)

#define STRIP_TILES  3

SceneryView* scenery_view_create(void) {
    SceneryView *sv = malloc(sizeof(SceneryView));
    if (!sv) return NULL;

    sv->scroll_offset = 0.0f;
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
        sv->trees[i].screen_y = (double)((2 * CAR_SCREEN_ROW - screen_row) * TRACK_TILE_HEIGHT) + (double)track->scroll_offset;
    }
}

void scenery_view_draw(SceneryView *sv) {
    if (!sv) return;
    const Resources *res = get_resources();

    int tile     = TRACK_TILE_HEIGHT;
    int off      = (int)sv->scroll_offset;
    int road_end = ROAD_OFFSET_X + 10 * CAR_LANE_WIDTH;

    for (int screen_row = 0; screen_row <= TRACK_VISIBLE_ROWS; screen_row++) {
        int y = screen_row * tile - off;
        for (int col = 0; col < STRIP_TILES; col++) {
            res->grass_sprite->x = col * tile;
            res->grass_sprite->y = y;
            draw_sprite(res->grass_sprite);

            res->grass_sprite->x = road_end + col * tile;
            res->grass_sprite->y = y;
            draw_sprite(res->grass_sprite);
        }
    }

    int screen_height = TRACK_VISIBLE_ROWS * tile;
    for (int i = 0; i < sv->count; i++) {
        int y = (int)sv->trees[i].screen_y;
        if (y + TREE_SIZE < 0 || y >= screen_height) continue;

        res->tree_sprite->x = sv->trees[i].screen_x;
        res->tree_sprite->y = y;
        draw_sprite(res->tree_sprite);
    }
}

void scenery_view_destroy(SceneryView *sv) {
    free(sv);
}
