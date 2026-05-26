#ifndef __PROJ_VIEW_H
#define __PROJ_VIEW_H

#include "../model/sprite/sprite.h"
#include "../model/game/game.h"

#define TRANSPARENT_COLOR 0xFF00FF  

void draw_sprite(Sprite *sp);
void draw_car(Car *car);
void draw_obstacle(Obstacle *obs);
void draw_clear(uint32_t bg_color);

#endif /* __PROJ_VIEW_H */
