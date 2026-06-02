#include "obstacle_view.h"
#include "obstacle_xpm.h"
#include "../../model/car/car.h"
#include "../view.h"
#include <stdlib.h>

#define OBSTACLE_COLOR 0xFF2222

ObstacleView* obstacle_view_create(void) {
    ObstacleView *ov = malloc(sizeof(ObstacleView));
    if (!ov) return NULL;

#if HAS_OBSTACLE_XPM
    ov->sprite = sprite_from_xpm((xpm_map_t)obstacle_xpm);
#else
    int w = CAR_LANE_WIDTH;
    int h = TRACK_TILE_HEIGHT;

    Sprite *sp = malloc(sizeof(Sprite));
    if (!sp) { free(ov); return NULL; }

    sp->pixmap = malloc(w * h * sizeof(uint32_t));
    if (!sp->pixmap) { free(sp); free(ov); return NULL; }

    for (int i = 0; i < w * h; i++) sp->pixmap[i] = OBSTACLE_COLOR;

    sp->x = sp->y = 0;
    sp->width  = w;
    sp->height = h;
    ov->sprite = sp;
#endif

    if (!ov->sprite) { free(ov); return NULL; }
    return ov;
}

void obstacle_view_update(ObstacleView *ov, Obstacle *obs) {
    if (!ov || !obs) return;

    ov->sprite->x = (int)obs->base.x + ROAD_OFFSET_X;
    ov->sprite->y = (int)obs->base.y;

    obs->base.sprite = ov->sprite;
}

void obstacle_view_destroy(ObstacleView *ov) {
    if (!ov) return;
    sprite_destroy(ov->sprite);
    free(ov);
}
