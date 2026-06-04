#include "obstacle_view.h"
#include "../../../model/resources/resources.h"
#include "../../view.h"

void obstacle_view_draw(Obstacle *obs, int theme) {
    if (!obs || !obs->base.is_active) return;
    Sprite *sp;
    switch (obs->type) {
        case OBSTACLE_BANANA: sp = resources_get_banana_sprite();            break;
        case OBSTACLE_OIL:    sp = resources_get_oil_puddle_sprite();        break;
        default:              sp = resources_get_obstacle_sprite_themed(theme); break;
    }
    if (!sp) return;
    draw_sprite(sp, (int)obs->base.x + ROAD_OFFSET_X, (int)obs->base.y);
}
