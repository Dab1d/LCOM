#include "obstacle_view.h"
#include "../../model/resources/resources.h"
#include "../view.h"

void obstacle_view_update(Obstacle *obs) {
    if (!obs) return;
    const Resources *res = get_resources();
    Sprite *sp = res->obstacle_sprite;
    sp->x = (int)obs->base.x + ROAD_OFFSET_X;
    sp->y = (int)obs->base.y;
    obs->base.sprite = sp;
}
