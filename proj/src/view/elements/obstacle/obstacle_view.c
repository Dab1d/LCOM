#include "obstacle_view.h"
#include "../../../model/resources/resources.h"
#include "../../view.h"

void obstacle_view_draw(Obstacle *obs, int theme) {
    if (!obs || !obs->base.is_active) return;
    Sprite *sp = (obs->type == OBSTACLE_BANANA)
                 ? resources_get_banana_sprite()
                 : resources_get_obstacle_sprite_themed(theme);
    if (!sp) return;
    draw_sprite(sp, (int)obs->base.x + ROAD_OFFSET_X, (int)obs->base.y);
}
