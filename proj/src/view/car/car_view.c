#include "car_view.h"
#include "../../model/resources/resources.h"
#include "../view.h"

void car_view_draw(Car *car) {
    if (!car) return;
    Sprite *sp = resources_get_car_sprite(car->player - 1, car->state);
    if (!sp) return;
    draw_sprite(sp, (int)car->base.x + ROAD_OFFSET_X, (int)car->base.y);
}
