#include "obstacle_view.h"
#include <stdlib.h>

#define OBSTACLE_COLOR 0xFF2222  // placeholder vermelho

ObstacleView* obstacle_view_create(int width, int height) {
    ObstacleView *ov = malloc(sizeof(ObstacleView));
    if (!ov) return NULL;

    Sprite *sp = malloc(sizeof(Sprite));
    if (!sp) { free(ov); return NULL; }

    sp->pixmap = malloc(width * height * sizeof(uint32_t));
    if (!sp->pixmap) { free(sp); free(ov); return NULL; }

    for (int i = 0; i < width * height; i++) sp->pixmap[i] = OBSTACLE_COLOR;

    sp->x      = 0;
    sp->y      = 0;
    sp->width  = width;
    sp->height = height;

    ov->sprite = sp;
    return ov;
}

void obstacle_view_update(ObstacleView *ov, Obstacle *obs) {
    if (!ov || !obs) return;

    ov->sprite->x = (int)obs->base.x;
    ov->sprite->y = (int)obs->base.y;

    obs->base.sprite = ov->sprite;
}

void obstacle_view_destroy(ObstacleView *ov) {
    if (!ov) return;

    if (ov->sprite) {
        free(ov->sprite->pixmap);
        free(ov->sprite);
    }
    free(ov);
}
