#include "sprite.h"
#include <lcom/lcf.h>
#include <stdlib.h>

Sprite* create_sprite(xpm_map_t map) {
    xpm_image_t img;
    uint8_t *data = xpm_load(map, XPM_8_8_8_8, &img);
    if (!data) return NULL;

    Sprite *sp = malloc(sizeof(Sprite));
    if (!sp) { free(data); return NULL; }

    sp->pixmap = malloc(img.width * img.height * sizeof(uint32_t));
    if (!sp->pixmap) { free(sp); free(data); return NULL; }

    uint32_t *src = (uint32_t*)data;
    for (int i = 0; i < img.width * img.height; i++) {
        // XPM_8_8_8_8 marks transparent pixels as TRANSPARENCY_COLOR_8_8_8_8 (0xFF000000)
        // map those to our draw_sprite transparency sentinel
        sp->pixmap[i] = (src[i] == TRANSPARENCY_COLOR_8_8_8_8) ? TRANSPARENT_COLOR : src[i];
    }

    sp->x      = 0;
    sp->y      = 0;
    sp->width  = img.width;
    sp->height = img.height;

    free(data);
    return sp;
}

void sprite_destroy(Sprite *sp) {
    if (!sp) return;
    free(sp->pixmap);
    free(sp);
}
