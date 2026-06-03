#include "sprite.h"
#include <lcom/lcf.h>
#include <stdlib.h>

Sprite* create_sprite(xpm_map_t map) {
    Sprite *sp = malloc(sizeof(Sprite));
    if (!sp) return NULL;

    xpm_image_t img;
    sp->pixmap = xpm_load(map, XPM_INDEXED, &img);
    if (!sp->pixmap) { free(sp); return NULL; }

    sp->width  = img.width;
    sp->height = img.height;
    return sp;
}

void sprite_destroy(Sprite *sp) {
    if (!sp) return;
    free(sp->pixmap);
    free(sp);
}
