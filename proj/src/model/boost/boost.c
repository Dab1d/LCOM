#include "boost.h"
#include "../car/car.h"
#include <stdlib.h>

#define CAR_SCREEN_ROW (TRACK_VISIBLE_ROWS - 2)

static double row_to_y(int logical_row, int scroll_row, float scroll_offset) {
    int screen_row = logical_row - scroll_row;
    return (double)(screen_row * TRACK_TILE_HEIGHT) - (double)scroll_offset;
}

Boost* create_boost(int row, int lane) {
    Boost* boost = (Boost*) malloc(sizeof(Boost));
    if (boost == NULL) return NULL;

    boost->lane = lane;
    boost->row  = row;

    double x = (double)(lane * CAR_LANE_WIDTH);
    double y = (double)(row * TRACK_TILE_HEIGHT);

    init_element(&boost->base, x, y, CAR_LANE_WIDTH, TRACK_TILE_HEIGHT);

    return boost;
}

void destroy_boost(Boost* boost) {
    if (boost != NULL)
        free(boost);
}

void boost_update(Boost* boost, int scroll_row, float scroll_offset) {
    if (boost == NULL || !boost->base.is_active) return;

    boost->base.y = row_to_y(boost->row, scroll_row, scroll_offset);

    if (boost->base.y + boost->base.height < 0)
        boost->base.is_active = false;
}

bool boost_is_visible(const Boost* boost) {
    if (boost == NULL || !boost->base.is_active) return false;

    int screen_height = TRACK_VISIBLE_ROWS * TRACK_TILE_HEIGHT;
    return boost->base.y < screen_height && boost->base.y + boost->base.height > 0;
}

bool boost_collides_with_car(const Boost* boost, int car_lane, int car_screen_row) {
    if (boost == NULL || !boost->base.is_active) return false;

    bool lane_hit = (car_lane == boost->lane);

    int car_y     = CAR_SCREEN_ROW * TRACK_TILE_HEIGHT;
    int boost_y_top = (int)boost->base.y;
    int boost_y_bot = boost_y_top + boost->base.height;
    bool row_hit  = (car_y >= boost_y_top && car_y < boost_y_bot);

    return lane_hit && row_hit;
}
