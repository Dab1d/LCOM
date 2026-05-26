#include "view.h"
#include "../../lab5/video_gr.h"  // vg_draw_pixel, vg_draw_rectangle

void draw_sprite(Sprite *sp) {
    if (sp == NULL || sp->pixmap == NULL) return;

    for (int row = 0; row < sp->height; row++) {
        for (int col = 0; col < sp->width; col++) {
            uint32_t color = sp->pixmap[row * sp->width + col];

            // ignora cor de transparência
            if (color == TRANSPARENT_COLOR) continue;

            vg_draw_pixel(sp->x + col, sp->y + row, color);
        }
    }
}

void draw_car(Car *car) {
    if (car == NULL) return;
    draw_sprite(car->sprite);
}

void draw_obstacle(Obstacle *obs) {
    if (obs == NULL) return;
    draw_sprite(obs->sprite);
}

void draw_clear(uint32_t bg_color) {
    // pinta o ecrã inteiro com a cor de fundo antes de cada frame
    vg_draw_rectangle(0, 0, 1024, 768, bg_color);  
}