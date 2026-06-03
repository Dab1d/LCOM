#include <lcom/lcf.h>
#include "resources.h"
#include "../car/car.h"
#include "../track/track.h"
#include <stdlib.h>

#include "../../assets/xpm/tiles/tile_road.xpm"
#include "../../assets/xpm/tiles/tile_obstacle.xpm"
#include "../../assets/xpm/tiles/tile_boost.xpm"
#include "../../assets/xpm/tiles/tile_finish.xpm"
#include "../../assets/xpm/obstacle.xpm"
#include "../../assets/xpm/scenery/grass.xpm"
#include "../../assets/xpm/scenery/tree.xpm"
#include "../../assets/car_blue.xpm"
#include "../../assets/car_red.xpm"

static Resources res;

int resources_load(void) {
    res.car_sprites[0][CAR_STATE_NORMAL]   = create_sprite((xpm_map_t)car_blue);
    res.car_sprites[0][CAR_STATE_DAMAGED]  = NULL;
    res.car_sprites[0][CAR_STATE_BURNING]  = NULL;
    res.car_sprites[0][CAR_STATE_EXPLODED] = NULL;
    if (!res.car_sprites[0][CAR_STATE_NORMAL]) return 1;

    res.car_sprites[1][CAR_STATE_NORMAL]   = create_sprite((xpm_map_t)car_red);
    res.car_sprites[1][CAR_STATE_DAMAGED]  = NULL;
    res.car_sprites[1][CAR_STATE_BURNING]  = NULL;
    res.car_sprites[1][CAR_STATE_EXPLODED] = NULL;
    if (!res.car_sprites[1][CAR_STATE_NORMAL]) return 1;

    res.tile_sprites[TILE_EMPTY]    = create_sprite((xpm_map_t)tile_road_xpm);
    res.tile_sprites[TILE_OBSTACLE] = create_sprite((xpm_map_t)tile_obstacle_xpm);
    res.tile_sprites[TILE_BOOST]    = create_sprite((xpm_map_t)tile_boost_xpm);
    res.tile_sprites[TILE_FINISH]   = create_sprite((xpm_map_t)tile_finish_xpm);
    for (int t = 0; t < 4; t++)
        if (!res.tile_sprites[t]) return 1;

    res.obstacle_sprite = create_sprite((xpm_map_t)obstacle_xpm);
    if (!res.obstacle_sprite) return 1;

    res.grass_sprite = create_sprite((xpm_map_t)grass_xpm);
    if (!res.grass_sprite) return 1;

    res.tree_sprite = create_sprite((xpm_map_t)tree_xpm);
    if (!res.tree_sprite) return 1;

    return 0;
}

void resources_destroy(void) {
    for (int p = 0; p < 2; p++)
        for (int s = 0; s < 4; s++)
            if (res.car_sprites[p][s]) { sprite_destroy(res.car_sprites[p][s]); res.car_sprites[p][s] = NULL; }
    for (int t = 0; t < 4; t++)
        if (res.tile_sprites[t]) { sprite_destroy(res.tile_sprites[t]); res.tile_sprites[t] = NULL; }
    if (res.obstacle_sprite) { sprite_destroy(res.obstacle_sprite); res.obstacle_sprite = NULL; }
    if (res.grass_sprite)    { sprite_destroy(res.grass_sprite);    res.grass_sprite    = NULL; }
    if (res.tree_sprite)     { sprite_destroy(res.tree_sprite);     res.tree_sprite     = NULL; }
}

Sprite* resources_get_car_sprite(int player, int state) {
    Sprite *sp = res.car_sprites[player][state];
    if (!sp) sp = res.car_sprites[player][CAR_STATE_NORMAL];
    return sp;
}

Sprite* resources_get_obstacle_sprite(void) {
    return res.obstacle_sprite;
}

Sprite* resources_get_tile_sprite(int type) {
    return res.tile_sprites[type];
}

Sprite* resources_get_grass_sprite(void) {
    return res.grass_sprite;
}

Sprite* resources_get_tree_sprite(void) {
    return res.tree_sprite;
}
