#include <lcom/lcf.h>
#include "resources.h"
#include "../car/car.h"
#include "../track/track.h"
#include <stdlib.h>

#include "../../../assets/xpm/redcar_s1_1.xpm"
#include "../../../assets/xpm/xpm_assets.h"

/* -------------------------------------------------------------------------
 * Helpers
 * ------------------------------------------------------------------------- */

static Sprite *make_solid_sprite(uint32_t color, int w, int h) {
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

static Sprite *make_grass_sprite(void) {
    int sz = TRACK_TILE_HEIGHT;
    Sprite *sp = malloc(sizeof(Sprite));
    if (!sp) return NULL;
    sp->pixmap = malloc(sz * sz * sizeof(uint32_t));
    if (!sp->pixmap) { free(sp); return NULL; }
    for (int i = 0; i < sz * sz; i++)
        sp->pixmap[i] = (rand() % 4 == 0) ? 0x2A6030 : 0x3A7D44;
    sp->x = sp->y = 0;
    sp->width = sp->height = sz;
    return sp;
}

/* -------------------------------------------------------------------------
 * Resources
 * ------------------------------------------------------------------------- */

static Resources res;

static const uint32_t P1_CAR_COLORS[4] = {0x0055FF, 0x4488FF, 0x0022AA, 0x555555};
static const uint32_t P2_CAR_COLORS[4] = {0xFF2200, 0xFF8800, 0xAA1100, 0x555555};
static const uint32_t TILE_COLORS[4]   = {0x444444, 0x00CC44, 0x888888, 0xFFFFFF};

int resources_load(void) {
    int s, t;
    char **p1_xpms[4];
    char **p2_xpms[4];

    /* --- player 1 car sprites (azul) --- */
    p1_xpms[0] = NULL;
    p1_xpms[1] = NULL;
    p1_xpms[2] = NULL;
    p1_xpms[3] = NULL;
    for (s = 0; s < 4; s++) {
        if (p1_xpms[s] != NULL)
            res.car_sprites[0][s] = create_sprite((xpm_map_t)p1_xpms[s]);
        else
            res.car_sprites[0][s] = make_solid_sprite(P1_CAR_COLORS[s], CAR_WIDTH, CAR_HEIGHT);
        if (!res.car_sprites[0][s]) return 1;
    }

    /* --- player 2 car sprites (vermelho) --- */
    p2_xpms[0] = redcar_s1_1_xpm;
    p2_xpms[1] = NULL;
    p2_xpms[2] = NULL;
    p2_xpms[3] = NULL;
    for (s = 0; s < 4; s++) {
        if (p2_xpms[s] != NULL)
            res.car_sprites[1][s] = create_sprite((xpm_map_t)p2_xpms[s]);
        else
            res.car_sprites[1][s] = make_solid_sprite(P2_CAR_COLORS[s], CAR_WIDTH, CAR_HEIGHT);
        if (!res.car_sprites[1][s]) return 1;
    }

    /* --- obstacle sprite --- */
    res.obstacle_sprite = make_solid_sprite(0xFF2222, CAR_LANE_WIDTH, TRACK_TILE_HEIGHT);
    if (!res.obstacle_sprite) return 1;

    /* --- tile sprites --- */
    for (t = 0; t < 4; t++) {
        res.tile_sprites[t] = make_solid_sprite(TILE_COLORS[t], CAR_LANE_WIDTH, TRACK_TILE_HEIGHT);
        if (!res.tile_sprites[t]) return 1;
    }

    /* --- scenery sprites --- */
    res.grass_sprite = make_grass_sprite();
    if (!res.grass_sprite) return 1;

    res.tree_sprite = make_solid_sprite(0x1A5C1A, 32, 32);
    if (!res.tree_sprite) return 1;

    return 0;
}

void resources_destroy(void) {
    int p, s, t;
    for (p = 0; p < 2; p++)
        for (s = 0; s < 4; s++) { sprite_destroy(res.car_sprites[p][s]); res.car_sprites[p][s] = NULL; }
    for (t = 0; t < 4; t++) { sprite_destroy(res.tile_sprites[t]); res.tile_sprites[t] = NULL; }
    sprite_destroy(res.obstacle_sprite); res.obstacle_sprite = NULL;
    sprite_destroy(res.grass_sprite);    res.grass_sprite    = NULL;
    sprite_destroy(res.tree_sprite);     res.tree_sprite     = NULL;
}

const Resources *get_resources(void) {
    return &res;
}
