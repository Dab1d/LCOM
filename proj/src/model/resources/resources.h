#ifndef __PROJ_RESOURCES_H
#define __PROJ_RESOURCES_H

#include "../sprite/sprite.h"

typedef struct {
    Sprite *car_sprites[2][4]; // [player-1][CarState]
    Sprite *obstacle_sprite;
    Sprite *boost_sprite;
    Sprite *tile_sprites[4];         // city tiles, indexed by TileType
    Sprite *tile_sprites_desert[4];  // desert tiles, indexed by TileType
    Sprite *grass_sprite;
    Sprite *sand_sprite;
    Sprite *tree_sprite;
    Sprite *cactus_sprite;
    Sprite *divider_sprite;
    Sprite *obstacle_desert_sprite;   /* barril — mesmo efeito que rock */
    Sprite *haybale_sprite;           /* fardo — mesmo efeito que rock */
    Sprite *menu_title;
    Sprite *menu_start_btn;
    Sprite *menu_exit_btn;
    Sprite *pause_panel;
    Sprite *pause_resume_btn[2]; // [0]=normal [1]=selected
    Sprite *pause_quit_btn[2];   // [0]=normal [1]=selected
    Sprite *cursor_sprite;
    Sprite *banana_sprite;
    Sprite *heart_sprite;
    Sprite *digit_sprites[10];
    Sprite *colon_sprite;
} Resources;

int  resources_load(void);
void resources_destroy(void);

Sprite* resources_get_car_sprite(int player, int state);
Sprite* resources_get_obstacle_sprite(void);
Sprite* resources_get_boost_sprite(void);
Sprite* resources_get_tile_sprite(int type);
Sprite* resources_get_grass_sprite(void);
Sprite* resources_get_tree_sprite(void);
Sprite* resources_get_ground_sprite(int theme);
Sprite* resources_get_scenery_sprite(int theme);
Sprite* resources_get_tile_sprite_themed(int type, int theme);
Sprite* resources_get_divider_sprite(void);
Sprite* resources_get_menu_title(void);
Sprite* resources_get_menu_start_btn(void);
Sprite* resources_get_menu_exit_btn(void);
Sprite* resources_get_pause_panel(void);
Sprite* resources_get_pause_resume_btn(int selected);
Sprite* resources_get_pause_quit_btn(int selected);
Sprite* resources_get_cursor_sprite(void);
Sprite* resources_get_banana_sprite(void);
Sprite* resources_get_heart_sprite(void);
Sprite* resources_get_digit_sprite(int digit);
Sprite* resources_get_colon_sprite(void);
Sprite* resources_get_obstacle_sprite_themed(int theme);

#endif /* __PROJ_RESOURCES_H */
