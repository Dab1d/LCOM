#include "obstacle.h"
#include "../car/car.h"
#include <stdlib.h>

static double lane_to_x(int lane) {
    return (double)(lane * CAR_LANE_WIDTH);
}

static double row_to_y(int logical_row, int scroll_row, float scroll_offset) {
    int screen_row = logical_row - scroll_row;
    return (double)(screen_row * TRACK_TILE_HEIGHT) - (double)scroll_offset;
}

Obstacle* create_obstacle(int row, int lane) {
    Obstacle* obs = (Obstacle*) malloc(sizeof(Obstacle));
    if (obs == NULL) return NULL;

    obs->lane = lane;
    obs->row  = row;

    init_element(&obs->base, lane_to_x(lane), (double)(row * TRACK_TILE_HEIGHT),
                 CAR_LANE_WIDTH, TRACK_TILE_HEIGHT);
    return obs;
}

void destroy_obstacle(Obstacle* obs) {
    free(obs);
}

void obstacle_update(Obstacle* obs, int scroll_row, float scroll_offset) {
    if (obs == NULL || !obs->base.is_active) return;

    obs->base.y = row_to_y(obs->row, scroll_row, scroll_offset);

    if (obs->base.y + obs->base.height < 0)
        obs->base.is_active = false;
}

bool obstacle_is_visible(const Obstacle* obs) {
    if (obs == NULL || !obs->base.is_active) return false;

    int screen_height = TRACK_VISIBLE_ROWS * TRACK_TILE_HEIGHT;
    return obs->base.y < screen_height && obs->base.y + obs->base.height > 0;
}

bool obstacle_collides_with_car(const Obstacle* obs, const Car* car) {
    if (obs == NULL || !obs->base.is_active) return false;
    if (car == NULL || !car->base.is_active) return false;

    if (car->lane != obs->lane) return false;

    int car_y_top = (int)car->base.y;
    int car_y_bot = car_y_top + CAR_HEIGHT;
    int obs_y_top = (int)obs->base.y;
    int obs_y_bot = obs_y_top + (int)obs->base.height;

    return car_y_top < obs_y_bot && car_y_bot > obs_y_top;
}
