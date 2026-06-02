#ifndef __PROJ_VIEW_H
#define __PROJ_VIEW_H

#include "../model/sprite/sprite.h"
#include "../model/game/game.h"

// Screen layout: 192px grass | 640px road (10x64) | 192px grass
#define ROAD_OFFSET_X 192


void view_init_buffers(void);
void draw_sprite(Sprite *sp);
void draw_car(Car *car);
void draw_obstacle(Obstacle *obs);
void draw_clear(uint32_t bg_color);
void copy_buffer_to_video(void);

#endif /* __PROJ_VIEW_H */
