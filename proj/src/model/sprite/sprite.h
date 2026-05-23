#ifndef __PROJ_SPRITE_H
#define __PROJ_SPRITE_H

#include <stdint.h>

typedef struct {
    int x, y;           // posição no ecrã
    int width, height;  // dimensões
    uint32_t *pixmap;   // pixels do XPM já convertidos
} Sprite;

#endif /* __PROJ_SPRITE_H */

