#include "view.h"
#include "video_gr.h"
#include <stdlib.h>   // malloc
#include <string.h>   // memcpy

// back_buffer tem de estar declarado ANTES de ser usado
static uint32_t *back_buffer = NULL;

void view_init_buffers(void) {
    uint16_t w = vg_get_x_res();
    uint16_t h = vg_get_y_res();
    back_buffer = (uint32_t*) malloc(w * h * vg_get_bytes_per_pixel());
}

void draw_sprite(Sprite *sp) {
    if (sp == NULL || sp->pixmap == NULL) return;

    uint16_t w = vg_get_x_res();

    for (int row = 0; row < sp->height; row++) {
        for (int col = 0; col < sp->width; col++) {
            uint32_t color = sp->pixmap[row * sp->width + col];
            if (color == TRANSPARENT_COLOR) continue;

            int screen_x = sp->x + col;
            int screen_y = sp->y + row;

            back_buffer[screen_y * w + screen_x] = color;
        }
    }
}

void draw_car(Car *car) {
    if (car == NULL) return;
    draw_sprite(car->base.sprite);  // sprite está em base, não diretamente em Car
}

void draw_obstacle(Obstacle *obs) {
    if (obs == NULL) return;
    draw_sprite(obs->base.sprite);  // idem
}

void draw_clear(uint32_t bg_color) {
    uint16_t w = vg_get_x_res();
    uint16_t h = vg_get_y_res();
    for (int i = 0; i < w * h; i++)
        back_buffer[i] = bg_color;
}

void copy_buffer_to_video(void) {
    uint16_t w = vg_get_x_res();
    uint16_t h = vg_get_y_res();
    memcpy(vg_get_video_mem(), back_buffer, w * h * vg_get_bytes_per_pixel());
}
