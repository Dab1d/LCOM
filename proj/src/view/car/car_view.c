#include "car_view.h"
#include "car_xpm.h"
#include "../view.h"
#include <stdlib.h>

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

#if HAS_CAR_XPM
    xpm_row_t *xpms[4] = {car_normal_xpm, car_damaged_xpm, car_burning_xpm, car_exploded_xpm};
    for (int s = 0; s < 4; s++) {
        cv->sprites[s] = sprite_from_xpm((xpm_map_t)xpms[s]);
        if (!cv->sprites[s]) {
            for (int j = 0; j < s; j++) sprite_destroy(cv->sprites[j]);
            free(cv);
            return NULL;
        }
    }
#else
    for (int s = 0; s < 4; s++) {
        cv->sprites[s] = make_solid_sprite(STATE_COLORS[s], width, height);
        if (!cv->sprites[s]) {
            for (int j = 0; j < s; j++) sprite_destroy(cv->sprites[j]);
            free(cv);
            return NULL;
        }
    }
#endif

    return cv;
}

void car_view_update(CarView *cv, Car *car) {
    if (!cv || !car) return;

    Sprite *sp = cv->sprites[car->state];
    sp->x = (int)car->base.x + ROAD_OFFSET_X;
    sp->y = (int)car->base.y;

    car->base.sprite = sp;
}

void car_view_destroy(CarView *cv) {
    if (!cv) return;

    for (int s = 0; s < 4; s++)
        sprite_destroy(cv->sprites[s]);

    free(cv);
}
