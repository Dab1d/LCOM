#include "shield.h"
#include <stdlib.h>

static double row_to_y(int logical_row, int scroll_row, float scroll_offset) {
    int screen_row = logical_row - scroll_row;
    return (double)((2 * CAR_SCREEN_ROW - screen_row) * TRACK_TILE_HEIGHT) + (double)scroll_offset;
}

Shield* create_shield(int row, int lane) {
    Shield *shield = (Shield*) malloc(sizeof(Shield));
    if (shield == NULL) return NULL;

    shield->lane = lane;
    shield->row  = row;

    double x = (double)(lane * CAR_LANE_WIDTH);
    double y = (double)(row  * TRACK_TILE_HEIGHT);
    init_element(&shield->base, x, y, CAR_LANE_WIDTH, TRACK_TILE_HEIGHT);

    return shield;
}

void destroy_shield(Shield *shield) {
    if (shield != NULL)
        free(shield);
}

void shield_update(Shield *shield, int scroll_row, float scroll_offset) {
    if (shield == NULL || !shield->base.is_active) return;

    shield->base.y = row_to_y(shield->row, scroll_row, scroll_offset);

    if (shield->base.y > (double)(TRACK_VISIBLE_ROWS * TRACK_TILE_HEIGHT))
        shield->base.is_active = false;
}

bool shield_is_visible(const Shield *shield) {
    if (shield == NULL || !shield->base.is_active) return false;

    int screen_height = TRACK_VISIBLE_ROWS * TRACK_TILE_HEIGHT;
    return shield->base.y < screen_height && shield->base.y + shield->base.height > 0;
}

bool shield_collides_with_car(const Shield *shield, const Car *car) {
    if (shield == NULL || !shield->base.is_active) return false;
    if (car   == NULL || !car->base.is_active)     return false;

    if (car->lane != shield->lane) return false;

    int car_y_top    = (int)car->base.y;
    int car_y_bot    = car_y_top + CAR_HEIGHT;
    int shield_y_top = (int)shield->base.y;
    int shield_y_bot = shield_y_top + (int)shield->base.height;

    return car_y_top < shield_y_bot && car_y_bot > shield_y_top;
}
