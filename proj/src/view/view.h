#ifndef __PROJ_VIEW_H
#define __PROJ_VIEW_H

#include "../model/sprite/sprite.h"
#include "../model/elements/car/car.h"
#include "../model/elements/obstacle/obstacle.h"
#include "../controller/palette/palette.h"

/* Screen layout: 192px grass | 640px road (10x64) | 192px grass */
#define ROAD_OFFSET_X 192

void view_init_buffers(void);
void draw_sprite(Sprite *sp, int x, int y);
void draw_sprite_scaled(Sprite *sp, int x, int y, int w, int h);
void draw_rect(int x, int y, int w, int h, uint8_t color);
void draw_clear(uint8_t color_index);
void copy_buffer_to_video(void);

#endif /* __PROJ_VIEW_H */
