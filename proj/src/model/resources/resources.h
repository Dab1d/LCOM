#ifndef __PROJ_RESOURCES_H
#define __PROJ_RESOURCES_H

#include "../sprite/sprite.h"

typedef struct {
    Sprite *car_sprites[2][4]; // [player-1][CarState]
    Sprite *obstacle_sprite;
    Sprite *tile_sprites[4];   // indexed by TileType
    Sprite *grass_sprite;
    Sprite *tree_sprite;
} Resources;

int  resources_load(void);
void resources_destroy(void);

Sprite* resources_get_car_sprite(int player, int state);
Sprite* resources_get_obstacle_sprite(void);
Sprite* resources_get_tile_sprite(int type);
Sprite* resources_get_grass_sprite(void);
Sprite* resources_get_tree_sprite(void);

#endif /* __PROJ_RESOURCES_H */
