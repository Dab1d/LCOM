#include "scenery.h"
#include "../car/car.h"
#include <stdlib.h>

#define GRASS_MARGIN 20

#define LEFT_X_MIN  (GRASS_MARGIN)
#define LEFT_X_MAX  (192 - GRASS_MARGIN - TREE_SIZE)
#define RIGHT_BASE  (192 + 10 * CAR_LANE_WIDTH)
#define RIGHT_X_MIN (RIGHT_BASE + GRASS_MARGIN)
#define RIGHT_X_MAX (RIGHT_BASE + 192 - GRASS_MARGIN - TREE_SIZE)

Scenery* scenery_create(void) {
    Scenery *s = malloc(sizeof(Scenery));
    if (!s) return NULL;

    s->scroll_offset = 0.0f;
    s->count = 0;

    int left_range  = LEFT_X_MAX  - LEFT_X_MIN  + 1;
    int right_range = RIGHT_X_MAX - RIGHT_X_MIN + 1;

    for (int row = 0; row < TRACK_TOTAL_ROWS && s->count < MAX_TREES - 2; row += 4) {
        int actual_row = row + rand() % 3;

        if (rand() % 10 < 7) {
            s->trees[s->count].logical_row = actual_row;
            s->trees[s->count].screen_x    = LEFT_X_MIN + rand() % left_range;
            s->trees[s->count].screen_y    = 0;
            s->count++;
        }

        if (rand() % 10 < 7 && s->count < MAX_TREES) {
            s->trees[s->count].logical_row = actual_row;
            s->trees[s->count].screen_x    = RIGHT_X_MIN + rand() % right_range;
            s->trees[s->count].screen_y    = 0;
            s->count++;
        }
    }

    return s;
}

void scenery_update(Scenery *s, const Track *track) {
    if (!s || !track) return;

    s->scroll_offset = track->scroll_offset;

    for (int i = 0; i < s->count; i++) {
        int screen_row = s->trees[i].logical_row - track->scroll_row;
        s->trees[i].screen_y = (double)((2 * CAR_SCREEN_ROW - screen_row) * TRACK_TILE_HEIGHT)
                             + (double)track->scroll_offset;
    }
}

void scenery_destroy(Scenery *s) {
    free(s);
}
