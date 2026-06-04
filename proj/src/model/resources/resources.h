#ifndef __PROJ_RESOURCES_H
#define __PROJ_RESOURCES_H

#include "../sprite/sprite.h"

typedef struct {
    Sprite *car_sprites[2][4]; // [player-1][CarState]
    Sprite *obstacle_sprite;
    Sprite *boost_sprite;
    Sprite *tile_sprites[4];   // indexed by TileType
    Sprite *grass_sprite;
    Sprite *tree_sprite;
    Sprite *menu_title;
    Sprite *menu_start_btn;
    Sprite *menu_exit_btn;
    Sprite *pause_panel;
    Sprite *pause_resume_btn[2]; // [0]=normal [1]=selected
    Sprite *pause_quit_btn[2];   // [0]=normal [1]=selected
} Resources;

int  resources_load(void);
void resources_destroy(void);

Sprite* resources_get_car_sprite(int player, int state);
Sprite* resources_get_obstacle_sprite(void);
Sprite* resources_get_boost_sprite(void);
Sprite* resources_get_tile_sprite(int type);
Sprite* resources_get_grass_sprite(void);
Sprite* resources_get_tree_sprite(void);
Sprite* resources_get_menu_title(void);
Sprite* resources_get_menu_start_btn(void);
Sprite* resources_get_menu_exit_btn(void);
Sprite* resources_get_pause_panel(void);
Sprite* resources_get_pause_resume_btn(int selected);
Sprite* resources_get_pause_quit_btn(int selected);

#endif /* __PROJ_RESOURCES_H */
