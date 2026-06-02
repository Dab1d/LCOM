#ifndef __PROJ_SPRITE_H
#define __PROJ_SPRITE_H

#include <stdint.h>
#include <stddef.h>
#include <lcom/xpm.h>

#define TRANSPARENT_COLOR 0xFF00FF

typedef struct {
    int x, y;           // posição no ecrã
    int width, height;  // dimensões
    uint32_t *pixmap;   // pixels do XPM já convertidos
} Sprite;

Sprite* sprite_from_xpm(xpm_map_t map);
void    sprite_destroy(Sprite *sp);

#endif /* __PROJ_SPRITE_H */

