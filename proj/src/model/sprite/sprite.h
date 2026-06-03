#ifndef __PROJ_SPRITE_H
#define __PROJ_SPRITE_H

#include <stddef.h>
#include <stdint.h>
#include <lcom/xpm.h>

typedef struct {
    int width, height;
    uint8_t *pixmap;   /* índices de paleta, 1 byte/pixel (XPM_INDEXED) */
} Sprite;

Sprite* create_sprite(xpm_map_t map);
void    sprite_destroy(Sprite *sp);

#endif /* __PROJ_SPRITE_H */
