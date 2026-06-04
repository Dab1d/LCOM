#include <lcom/lcf.h>
#include "resources.h"
#include "../car/car.h"
#include "../track/track.h"
#include <stdlib.h>

/* ── city ── */
#include "../../assets/xpm/biomes/city/tiles/tile_road.xpm"
#include "../../assets/xpm/biomes/city/tiles/tile_obstacle.xpm"
#include "../../assets/xpm/biomes/city/tiles/tile_boost.xpm"
#include "../../assets/xpm/biomes/city/tiles/tile_finish.xpm"
#include "../../assets/xpm/biomes/city/scenery/grass1.xpm"
#include "../../assets/xpm/biomes/city/scenery/tree.xpm"
#include "../../assets/xpm/biomes/city/objects/obstacle.xpm"
#include "../../assets/xpm/biomes/city/objects/boost.xpm"

/* ── desert ── */
#include "../../assets/xpm/biomes/desert/tiles/tile_road_desert.xpm"
#include "../../assets/xpm/biomes/desert/tiles/tile_sand.xpm"
#include "../../assets/xpm/biomes/desert/tiles/tile_divider.xpm"
#include "../../assets/xpm/biomes/desert/tiles/tile_finish_desert.xpm"
#include "../../assets/xpm/biomes/desert/scenery/cactus_tall.xpm"
#include "../../assets/xpm/biomes/desert/objects/obstacle_barrel.xpm"
#include "../../assets/xpm/biomes/desert/objects/obstacle_haybale.xpm"

#include "../../assets/xpm/cars/car_blue.xpm"
#include "../../assets/xpm/cars/car_blue_dmg1.xpm"
#include "../../assets/xpm/cars/car_blue_dmg2.xpm"
#include "../../assets/xpm/cars/car_blue_destroyed.xpm"

#include "../../assets/xpm/cars/car_red.xpm"
#include "../../assets/xpm/cars/car_red_dmg1.xpm"
#include "../../assets/xpm/cars/car_red_dmg2.xpm"
#include "../../assets/xpm/cars/car_red_destroyed.xpm"

#include "../../assets/xpm/pause/pause_panel.xpm"
#include "../../assets/xpm/banana.xpm"
#include "../../assets/xpm/pause/pause_resume_btn.xpm"
#include "../../assets/xpm/pause/pause_resume_btn_sel.xpm"
#include "../../assets/xpm/pause/pause_quit_btn.xpm"
#include "../../assets/xpm/pause/pause_quit_btn_sel.xpm"

#include "../../assets/xpm/digits/digit_0.xpm"
#include "../../assets/xpm/digits/digit_1.xpm"
#include "../../assets/xpm/digits/digit_2.xpm"
#include "../../assets/xpm/digits/digit_3.xpm"
#include "../../assets/xpm/digits/digit_4.xpm"
#include "../../assets/xpm/digits/digit_5.xpm"
#include "../../assets/xpm/digits/digit_6.xpm"
#include "../../assets/xpm/digits/digit_7.xpm"
#include "../../assets/xpm/digits/digit_8.xpm"
#include "../../assets/xpm/digits/digit_9.xpm"
#include "../../assets/xpm/digits/digit_colon.xpm"

#include "../../assets/xpm/main/getaway_car_title.xpm"
#include "../../assets/xpm/main/start_button.xpm"
#include "../../assets/xpm/main/exit_button.xpm"
#include "../../assets/xpm/cursor.xpm"
#include "../../assets/xpm/heart.xpm"

static Resources res;

int resources_load(void) {
    res.car_sprites[0][CAR_STATE_NORMAL]   = create_sprite((xpm_map_t)car_blue);
    res.car_sprites[0][CAR_STATE_DAMAGED]  = create_sprite((xpm_map_t)car_blue_dmg1);
    res.car_sprites[0][CAR_STATE_BURNING]  = create_sprite((xpm_map_t)car_blue_dmg2);
    res.car_sprites[0][CAR_STATE_EXPLODED] = create_sprite((xpm_map_t)car_blue_destroyed);
    for (int s = 0; s < 4; s++)
        if (!res.car_sprites[0][s]) return 1;

    res.car_sprites[1][CAR_STATE_NORMAL]   = create_sprite((xpm_map_t)car_red);
    res.car_sprites[1][CAR_STATE_DAMAGED]  = create_sprite((xpm_map_t)car_red_dmg1);
    res.car_sprites[1][CAR_STATE_BURNING]  = create_sprite((xpm_map_t)car_red_dmg2);
    res.car_sprites[1][CAR_STATE_EXPLODED] = create_sprite((xpm_map_t)car_red_destroyed);
    for (int s = 0; s < 4; s++)
        if (!res.car_sprites[1][s]) return 1;

    res.tile_sprites[TILE_EMPTY]    = create_sprite((xpm_map_t)tile_road_xpm);
    res.tile_sprites[TILE_OBSTACLE] = create_sprite((xpm_map_t)tile_obstacle_xpm);
    res.tile_sprites[TILE_BOOST]    = create_sprite((xpm_map_t)tile_boost_xpm);
    res.tile_sprites[TILE_FINISH]   = create_sprite((xpm_map_t)tile_finish_xpm);
    for (int t = 0; t < 4; t++)
        if (!res.tile_sprites[t]) return 1;

    res.tile_sprites_desert[TILE_EMPTY]    = create_sprite((xpm_map_t)tile_road_desert_xpm);
    res.tile_sprites_desert[TILE_OBSTACLE] = create_sprite((xpm_map_t)tile_obstacle_xpm);
    res.tile_sprites_desert[TILE_BOOST]    = create_sprite((xpm_map_t)tile_boost_xpm);
    res.tile_sprites_desert[TILE_FINISH]   = create_sprite((xpm_map_t)tile_finish_desert_xpm);
    for (int t = 0; t < 4; t++)
        if (!res.tile_sprites_desert[t]) return 1;

    res.sand_sprite   = create_sprite((xpm_map_t)tile_sand_xpm);
    res.cactus_sprite = create_sprite((xpm_map_t)cactus_tall_xpm);
    res.divider_sprite= create_sprite((xpm_map_t)tile_divider_xpm);
    if (!res.sand_sprite || !res.cactus_sprite || !res.divider_sprite) return 1;

    res.obstacle_desert_sprite = create_sprite((xpm_map_t)obstacle_barrel_xpm);
    res.haybale_sprite         = create_sprite((xpm_map_t)obstacle_haybale_xpm);
    if (!res.obstacle_desert_sprite || !res.haybale_sprite) return 1;

    res.obstacle_sprite = create_sprite((xpm_map_t)obstacle_xpm);
    if (!res.obstacle_sprite) return 1;

    res.grass_sprite = create_sprite((xpm_map_t)grass1);
    if (!res.grass_sprite) return 1;

    res.tree_sprite = create_sprite((xpm_map_t)tree);
    if (!res.tree_sprite) return 1;

    res.menu_title     = create_sprite((xpm_map_t)getaway_car_title);
    if (!res.menu_title) return 1;

    res.menu_start_btn = create_sprite((xpm_map_t)start_button);
    if (!res.menu_start_btn) return 1;

    res.menu_exit_btn  = create_sprite((xpm_map_t)exit_button);
    if (!res.menu_exit_btn) return 1;

    res.boost_sprite = create_sprite((xpm_map_t)boost_xpm);
    if (!res.boost_sprite) return 1;

    res.pause_panel        = create_sprite((xpm_map_t)pause_panel_xpm);
    res.pause_resume_btn[0] = create_sprite((xpm_map_t)pause_resume_btn_xpm);
    res.pause_resume_btn[1] = create_sprite((xpm_map_t)pause_resume_btn_sel_xpm);
    res.pause_quit_btn[0]   = create_sprite((xpm_map_t)pause_quit_btn_xpm);
    res.pause_quit_btn[1]   = create_sprite((xpm_map_t)pause_quit_btn_sel_xpm);
    if (!res.pause_panel || !res.pause_resume_btn[0] || !res.pause_resume_btn[1]
     || !res.pause_quit_btn[0] || !res.pause_quit_btn[1]) return 1;

    res.cursor_sprite = create_sprite((xpm_map_t)cursor_xpm);
    if (!res.cursor_sprite) return 1;

    res.banana_sprite = create_sprite((xpm_map_t)banana_xpm);
    if (!res.banana_sprite) return 1;

    res.heart_sprite = create_sprite((xpm_map_t)heart_xpm);
    if (!res.heart_sprite) return 1;

    static xpm_map_t digit_xpms[10] = {
        (xpm_map_t)digit_0, (xpm_map_t)digit_1, (xpm_map_t)digit_2,
        (xpm_map_t)digit_3, (xpm_map_t)digit_4, (xpm_map_t)digit_5,
        (xpm_map_t)digit_6, (xpm_map_t)digit_7, (xpm_map_t)digit_8,
        (xpm_map_t)digit_9
    };
    for (int i = 0; i < 10; i++) {
        res.digit_sprites[i] = create_sprite(digit_xpms[i]);
        if (!res.digit_sprites[i]) return 1;
    }
    res.colon_sprite = create_sprite((xpm_map_t)digit_colon);
    if (!res.colon_sprite) return 1;

    return 0;
}

void resources_destroy(void) {
    for (int p = 0; p < 2; p++)
        for (int s = 0; s < 4; s++)
            if (res.car_sprites[p][s]) { sprite_destroy(res.car_sprites[p][s]); res.car_sprites[p][s] = NULL; }
    for (int t = 0; t < 4; t++) {
        if (res.tile_sprites[t])        { sprite_destroy(res.tile_sprites[t]);        res.tile_sprites[t]        = NULL; }
        if (res.tile_sprites_desert[t]) { sprite_destroy(res.tile_sprites_desert[t]); res.tile_sprites_desert[t] = NULL; }
    }
    if (res.sand_sprite)            { sprite_destroy(res.sand_sprite);            res.sand_sprite            = NULL; }
    if (res.cactus_sprite)          { sprite_destroy(res.cactus_sprite);          res.cactus_sprite          = NULL; }
    if (res.divider_sprite)         { sprite_destroy(res.divider_sprite);         res.divider_sprite         = NULL; }
    if (res.obstacle_desert_sprite) { sprite_destroy(res.obstacle_desert_sprite); res.obstacle_desert_sprite = NULL; }
    if (res.haybale_sprite)         { sprite_destroy(res.haybale_sprite);         res.haybale_sprite         = NULL; }
    if (res.obstacle_sprite) { sprite_destroy(res.obstacle_sprite); res.obstacle_sprite = NULL; }
    if (res.boost_sprite)    { sprite_destroy(res.boost_sprite);    res.boost_sprite    = NULL; }
    if (res.grass_sprite)    { sprite_destroy(res.grass_sprite);    res.grass_sprite    = NULL; }
    if (res.tree_sprite)     { sprite_destroy(res.tree_sprite);     res.tree_sprite     = NULL; }
    if (res.pause_panel)     { sprite_destroy(res.pause_panel);     res.pause_panel     = NULL; }
    if (res.banana_sprite)   { sprite_destroy(res.banana_sprite);   res.banana_sprite   = NULL; }
    for (int i = 0; i < 2; i++) {
        if (res.pause_resume_btn[i]) { sprite_destroy(res.pause_resume_btn[i]); res.pause_resume_btn[i] = NULL; }
        if (res.pause_quit_btn[i])   { sprite_destroy(res.pause_quit_btn[i]);   res.pause_quit_btn[i]   = NULL; }
    }
    if (res.menu_title)      { sprite_destroy(res.menu_title);      res.menu_title      = NULL; }
    if (res.menu_start_btn)  { sprite_destroy(res.menu_start_btn);  res.menu_start_btn  = NULL; }
    if (res.menu_exit_btn)   { sprite_destroy(res.menu_exit_btn);   res.menu_exit_btn   = NULL; }
    if (res.cursor_sprite)   { sprite_destroy(res.cursor_sprite);   res.cursor_sprite   = NULL; }
    if (res.heart_sprite)    { sprite_destroy(res.heart_sprite);    res.heart_sprite    = NULL; }
    for (int i = 0; i < 10; i++)
        if (res.digit_sprites[i]) { sprite_destroy(res.digit_sprites[i]); res.digit_sprites[i] = NULL; }
    if (res.colon_sprite) { sprite_destroy(res.colon_sprite); res.colon_sprite = NULL; }
}

Sprite* resources_get_car_sprite(int player, int state) {
    Sprite *sp = res.car_sprites[player][state];
    if (!sp) sp = res.car_sprites[player][CAR_STATE_NORMAL];
    return sp;
}

Sprite* resources_get_obstacle_sprite(void) {
    return res.obstacle_sprite;
}

Sprite* resources_get_boost_sprite(void) {
    return res.boost_sprite;
}

Sprite* resources_get_tile_sprite(int type) {
    return res.tile_sprites[type];
}

Sprite* resources_get_tile_sprite_themed(int type, int theme) {
    if (theme == 1) return res.tile_sprites_desert[type];
    return res.tile_sprites[type];
}

Sprite* resources_get_ground_sprite(int theme) {
    if (theme == 1) return res.sand_sprite;
    return res.grass_sprite;
}

Sprite* resources_get_scenery_sprite(int theme) {
    if (theme == 1) return res.cactus_sprite;
    return res.tree_sprite;
}

Sprite* resources_get_divider_sprite(void) { return res.divider_sprite; }

Sprite* resources_get_grass_sprite(void) {
    return res.grass_sprite;
}

Sprite* resources_get_tree_sprite(void) {
    return res.tree_sprite;
}

Sprite* resources_get_pause_panel(void) {
    return res.pause_panel;
}

Sprite* resources_get_pause_resume_btn(int selected) {
    return res.pause_resume_btn[selected ? 1 : 0];
}

Sprite* resources_get_pause_quit_btn(int selected) {
    return res.pause_quit_btn[selected ? 1 : 0];
}

Sprite* resources_get_menu_title(void)     { return res.menu_title; }
Sprite* resources_get_menu_start_btn(void) { return res.menu_start_btn; }
Sprite* resources_get_menu_exit_btn(void)  { return res.menu_exit_btn; }
Sprite* resources_get_cursor_sprite(void)  { return res.cursor_sprite; }
Sprite* resources_get_banana_sprite(void)  { return res.banana_sprite; }
Sprite* resources_get_heart_sprite(void)   { return res.heart_sprite; }

<<<<<<< HEAD
Sprite* resources_get_digit_sprite(int digit) {
    if (digit < 0 || digit > 9) return NULL;
    return res.digit_sprites[digit];
}

Sprite* resources_get_colon_sprite(void) { return res.colon_sprite; }
=======
Sprite* resources_get_obstacle_sprite_themed(int theme) {
    if (theme == 1) return res.obstacle_desert_sprite;
    return res.obstacle_sprite;
}
>>>>>>> ee022a9 (add desert biome: themed tiles, scenery, obstacles, menu preview)
