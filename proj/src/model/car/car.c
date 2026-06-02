#include "car.h"
#include <stdlib.h>
#include "../track/track.h"

static double lane_to_x(int lane) {
    return (double)(lane * CAR_LANE_WIDTH);
}

Car* create_car(int initial_lane, int lane_min, int lane_max, int car_width, int car_height) {
    Car* car = (Car*) malloc(sizeof(Car));
    if (car == NULL) return NULL;

    init_element(&car->base, lane_to_x(initial_lane), 0.0, car_width, car_height);

    car->lane           = initial_lane;
    car->track_progress = 0;
    car->state          = CAR_STATE_NORMAL;
    car->lane_min = lane_min;
    car->lane_max = lane_max;
    car_init_session(car, CAR_INITIAL_LIVES);

    return car;
}

void destroy_car(Car* car) {
    if (car != NULL) {
        free(car);
    }
}

void car_move_lane(Car* car, int direction) {
    if (car == NULL || !car->base.is_active) return;
    if (car->state == CAR_STATE_EXPLODED)    return;

    int new_lane = car->lane + direction;
    if (new_lane < 0 || new_lane >= TRACK_LANES) return;

    car->lane   = new_lane;
    car->base.x = lane_to_x(new_lane);
}

void car_take_damage(Car* car) {
    if (car == NULL || !car->base.is_active) return;

    if (car->lives > 0) car->lives--;

    switch (car->state) {
        case CAR_STATE_NORMAL:
            car->state = CAR_STATE_DAMAGED;
            break;
        case CAR_STATE_DAMAGED:
            car->state = CAR_STATE_BURNING;
            break;
        case CAR_STATE_BURNING:
            car->state          = CAR_STATE_EXPLODED;
            car->base.is_active = false; // Retira o carro do jogo
            break;
        case CAR_STATE_EXPLODED:
            break;
    }
}

void car_apply_boost(Car* car, int tiles) {
    if (car == NULL || !car->base.is_active) return;
    if (car->state == CAR_STATE_EXPLODED)    return;

    car->track_progress += tiles;
}

void reset_car(Car* car, int initial_lane) {
    if (car == NULL) return;

    car->lane           = initial_lane;
    car->base.x         = lane_to_x(initial_lane);
    car->base.y         = 0.0;
    car->base.is_active = true;
    car->track_progress = 0;
    car->state          = CAR_STATE_NORMAL;
    car_init_session(car, CAR_INITIAL_LIVES);
}

void car_init_session(Car* car, int initial_lives) {
    if (car == NULL) return;
    car->score = 0;
    car->lives = initial_lives;
}
