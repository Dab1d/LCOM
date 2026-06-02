#include "car_view.h"
#include "../../model/resources/resources.h"
#include "../view.h"

void car_view_update(Car *car) {
    if (!car) return;
    const Resources *res = get_resources();
    Sprite *sp = res->car_sprites[car->player - 1][car->state];
    sp->x = (int)car->base.x + ROAD_OFFSET_X;
    sp->y = (int)car->base.y;
    car->base.sprite = sp;
}
