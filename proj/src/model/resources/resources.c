#include <lcom/lcf.h>
#include "resources.h"
#include "../car/car.h"
#include "../track/track.h"
#include <stdlib.h>

#include "../../assets/xpm/tiles/tile_road.xpm"
#include "../../assets/xpm/tiles/tile_obstacle.xpm"
#include "../../assets/xpm/tiles/tile_boost.xpm"
#include "../../assets/xpm/tiles/tile_finish.xpm"

#include "../../assets/xpm/objects/obstacle.xpm"
#include "../../assets/xpm/objects/boost.xpm"
#include "../../assets/xpm/scenery/grass.xpm"
#include "../../assets/xpm/scenery/tree.xpm"

#include "../../assets/xpm/cars/car_blue.xpm"
#include "../../assets/xpm/cars/car_blue_dmg1.xpm"
#include "../../assets/xpm/cars/car_blue_dmg2.xpm"
#include "../../assets/xpm/cars/car_blue_destroyed.xpm"

#include "../../assets/xpm/cars/car_red.xpm"
#include "../../assets/xpm/cars/car_red_dmg1.xpm"
#include "../../assets/xpm/cars/car_red_dmg2.xpm"
#include "../../assets/xpm/cars/car_red_destroyed.xpm"

#include "../../assets/xpm/pause/pause_panel.xpm"
#include "../../assets/xpm/pause/pause_resume_btn.xpm"
#include "../../assets/xpm/pause/pause_resume_btn_sel.xpm"
#include "../../assets/xpm/pause/pause_quit_btn.xpm"
#include "../../assets/xpm/pause/pause_quit_btn_sel.xpm"

#include "../../assets/xpm/main/getaway_car_title.xpm"
#include "../../assets/xpm/main/start_button.xpm"
#include "../../assets/xpm/main/exit_button.xpm"
#include "../../assets/xpm/cursor.xpm"

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

    res.obstacle_sprite = create_sprite((xpm_map_t)obstacle_xpm);
    if (!res.obstacle_sprite) return 1;

    res.grass_sprite = create_sprite((xpm_map_t)grass_xpm);
    if (!res.grass_sprite) return 1;

    res.tree_sprite = create_sprite((xpm_map_t)tree_xpm);
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

    return 0;
}

void resources_destroy(void) {
    for (int p = 0; p < 2; p++)
        for (int s = 0; s < 4; s++)
            if (res.car_sprites[p][s]) { sprite_destroy(res.car_sprites[p][s]); res.car_sprites[p][s] = NULL; }
    for (int t = 0; t < 4; t++)
        if (res.tile_sprites[t]) { sprite_destroy(res.tile_sprites[t]); res.tile_sprites[t] = NULL; }
    if (res.obstacle_sprite) { sprite_destroy(res.obstacle_sprite); res.obstacle_sprite = NULL; }
    if (res.boost_sprite)    { sprite_destroy(res.boost_sprite);    res.boost_sprite    = NULL; }
    if (res.grass_sprite)    { sprite_destroy(res.grass_sprite);    res.grass_sprite    = NULL; }
    if (res.tree_sprite)     { sprite_destroy(res.tree_sprite);     res.tree_sprite     = NULL; }
    if (res.pause_panel)     { sprite_destroy(res.pause_panel);     res.pause_panel     = NULL; }
    for (int i = 0; i < 2; i++) {
        if (res.pause_resume_btn[i]) { sprite_destroy(res.pause_resume_btn[i]); res.pause_resume_btn[i] = NULL; }
        if (res.pause_quit_btn[i])   { sprite_destroy(res.pause_quit_btn[i]);   res.pause_quit_btn[i]   = NULL; }
    }
    if (res.menu_title)      { sprite_destroy(res.menu_title);      res.menu_title      = NULL; }
    if (res.menu_start_btn)  { sprite_destroy(res.menu_start_btn);  res.menu_start_btn  = NULL; }
    if (res.menu_exit_btn)   { sprite_destroy(res.menu_exit_btn);   res.menu_exit_btn   = NULL; }
    if (res.cursor_sprite)   { sprite_destroy(res.cursor_sprite);   res.cursor_sprite   = NULL; }
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
