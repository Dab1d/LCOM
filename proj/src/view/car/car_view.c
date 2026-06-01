#include "car_view.h"
#include <stdlib.h>

// Cores placeholder por estado (0x00RRGGBB) — substituir por XPMs quando existirem
static const uint32_t STATE_COLORS[4] = {
    0x0055FF,  // NORMAL   - azul
    0xFFCC00,  // DAMAGED  - amarelo
    0xFF6600,  // BURNING  - laranja
    0x555555,  // EXPLODED - cinzento
};

static Sprite* make_solid_sprite(uint32_t color, int w, int h) {
    Sprite *sp = malloc(sizeof(Sprite));
    if (!sp) return NULL;

    sp->pixmap = malloc(w * h * sizeof(uint32_t));
    if (!sp->pixmap) { free(sp); return NULL; }

    for (int i = 0; i < w * h; i++) sp->pixmap[i] = color;

    sp->x = sp->y = 0;
    sp->width  = w;
    sp->height = h;
    return sp;
}

CarView* car_view_create(int width, int height) {
    CarView *cv = malloc(sizeof(CarView));
    if (!cv) return NULL;

    for (int s = 0; s < 4; s++) {
        cv->sprites[s] = make_solid_sprite(STATE_COLORS[s], width, height);
        if (!cv->sprites[s]) {
            for (int j = 0; j < s; j++) {
                free(cv->sprites[j]->pixmap);
                free(cv->sprites[j]);
            }
            free(cv);
            return NULL;
        }
    }
    return cv;
}

void car_view_update(CarView *cv, Car *car) {
    if (!cv || !car) return;

    Sprite *sp = cv->sprites[car->state];
    sp->x = (int)car->base.x;
    sp->y = CAR_SCREEN_ROW * TRACK_TILE_HEIGHT;

    car->base.sprite = sp;
}

void car_view_destroy(CarView *cv) {
    if (!cv) return;

    for (int s = 0; s < 4; s++) {
        if (cv->sprites[s]) {
            free(cv->sprites[s]->pixmap);
            free(cv->sprites[s]);
        }
    }
    free(cv);
}
