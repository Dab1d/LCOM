#include <lcom/lcf.h>
#include "resources.h"
#include "../elements/car/car.h"
#include "../elements/track/track.h"
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
#include "../../assets/xpm/biomes/desert/objects/oil_puddle.xpm"
#include "../../assets/xpm/biomes/desert/scenery/fence.xpm"
#include "../../assets/xpm/biomes/desert/tiles/tile_sand_pebbles.xpm"

#include "../../assets/xpm/elements/cars/car_blue.xpm"
#include "../../assets/xpm/elements/cars/car_blue_dmg1.xpm"
#include "../../assets/xpm/elements/cars/car_blue_dmg2.xpm"
#include "../../assets/xpm/elements/cars/car_blue_destroyed.xpm"

#include "../../assets/xpm/elements/cars/car_red.xpm"
#include "../../assets/xpm/elements/cars/car_red_dmg1.xpm"
#include "../../assets/xpm/elements/cars/car_red_dmg2.xpm"
#include "../../assets/xpm/elements/cars/car_red_destroyed.xpm"

/* ── car selection formats (s1=normal, s2=damaged, s3=burning, s4=exploded) ── */
/* ── car rotation sprites (8 rotations, step 45°: 00,02,04,06,08,10,12,14) ── */
#include "../../assets/xpm/elements/cars/carBlue00/carB00_s1.xpm"
#include "../../assets/xpm/elements/cars/carBlue02/carB02_s1.xpm"
#include "../../assets/xpm/elements/cars/carBlue04/carB04_s1.xpm"
#include "../../assets/xpm/elements/cars/carBlue06/carB06_s1.xpm"
#include "../../assets/xpm/elements/cars/carBlue08/carB08_s1.xpm"
#include "../../assets/xpm/elements/cars/carBlue10/carB10_s1.xpm"
#include "../../assets/xpm/elements/cars/carBlue12/carB12_s1.xpm"
#include "../../assets/xpm/elements/cars/carBlue14/carB14_s1.xpm"
#include "../../assets/xpm/elements/cars/carRed00/carR00_s1.xpm"
#include "../../assets/xpm/elements/cars/carRed02/carR02_s1.xpm"
#include "../../assets/xpm/elements/cars/carRed04/carR04_s1.xpm"
#include "../../assets/xpm/elements/cars/carRed06/carR06_s1.xpm"
#include "../../assets/xpm/elements/cars/carRed08/carR08_s1.xpm"
#include "../../assets/xpm/elements/cars/carRed10/carR10_s1.xpm"
#include "../../assets/xpm/elements/cars/carRed12/carR12_s1.xpm"
#include "../../assets/xpm/elements/cars/carRed14/carR14_s1.xpm"

#include "../../assets/xpm/pause/pause_panel.xpm"
#include "../../assets/xpm/elements/banana.xpm"
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
#include "../../assets/xpm/elements/cursor.xpm"
#include "../../assets/xpm/elements/heart.xpm"

#include "../../assets/xpm/modes/mode_select_title.xpm"
#include "../../assets/xpm/modes/mode_race_card.xpm"
#include "../../assets/xpm/modes/mode_endurance_card.xpm"
#include "../../assets/xpm/modes/title_race.xpm"
#include "../../assets/xpm/modes/title_endurance.xpm"

#include "../../assets/xpm/win/blue_wins.xpm"
#include "../../assets/xpm/win/red_wins.xpm"
#include "../../assets/xpm/win/win_play_again_btn.xpm"
#include "../../assets/xpm/win/win_menu_btn.xpm"

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

    res.oil_puddle_sprite   = create_sprite((xpm_map_t)oil_puddle_xpm);
    res.fence_sprite        = create_sprite((xpm_map_t)fence_xpm);
    res.sand_pebbles_sprite = create_sprite((xpm_map_t)tile_sand_pebbles_xpm);
    if (!res.oil_puddle_sprite || !res.fence_sprite || !res.sand_pebbles_sprite) return 1;

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

    res.mode_select_title   = create_sprite((xpm_map_t)mode_select_title);
    if (!res.mode_select_title) return 1;
    res.mode_race_card      = create_sprite((xpm_map_t)mode_race_card);
    if (!res.mode_race_card) return 1;
    res.mode_endurance_card = create_sprite((xpm_map_t)mode_endurance_card);
    if (!res.mode_endurance_card) return 1;
    res.mode_race_label      = create_sprite((xpm_map_t)title_race);
    if (!res.mode_race_label) return 1;
    res.mode_endurance_label = create_sprite((xpm_map_t)title_endurance);
    if (!res.mode_endurance_label) return 1;

    {
        static xpm_map_t fmt_blue_s1[CAR_FORMAT_MAX] = {
            (xpm_map_t)car_blue_00_s1, (xpm_map_t)car_blue_02_s1,
            (xpm_map_t)car_blue_04_s1, (xpm_map_t)car_blue_06_s1,
            (xpm_map_t)car_blue_08_s1, (xpm_map_t)car_blue_10_s1,
            (xpm_map_t)car_blue_12_s1, (xpm_map_t)car_blue_14_s1,
        };
        static xpm_map_t fmt_red_s1[CAR_FORMAT_MAX] = {
            (xpm_map_t)car_red_00_s1, (xpm_map_t)car_red_02_s1,
            (xpm_map_t)car_red_04_s1, (xpm_map_t)car_red_06_s1,
            (xpm_map_t)car_red_08_s1, (xpm_map_t)car_red_10_s1,
            (xpm_map_t)car_red_12_s1, (xpm_map_t)car_red_14_s1,
        };
        res.car_format_count = 0;
        for (int f = 0; f < CAR_FORMAT_MAX; f++) {
            Sprite *sb = create_sprite(fmt_blue_s1[f]);
            Sprite *sr = create_sprite(fmt_red_s1[f]);
            if (!sb || !sr) {
                if (sb) sprite_destroy(sb);
                if (sr) sprite_destroy(sr);
                break;
            }
            res.car_format_sprites[f][0][CAR_STATE_NORMAL] = sb;
            res.car_format_sprites[f][1][CAR_STATE_NORMAL] = sr;
            for (int s = 1; s < 4; s++) {
                res.car_format_sprites[f][0][s] = NULL;
                res.car_format_sprites[f][1][s] = NULL;
            }
            res.car_format_count++;
        }
    }

    res.win_img[0] = create_sprite((xpm_map_t)blue_wins);
    if (!res.win_img[0]) return 1;
    res.win_img[1] = create_sprite((xpm_map_t)red_wins);
    if (!res.win_img[1]) return 1;
    res.win_play_again_btn = create_sprite((xpm_map_t)win_play_again_btn);
    if (!res.win_play_again_btn) return 1;
    res.win_menu_btn = create_sprite((xpm_map_t)win_menu_btn);
    if (!res.win_menu_btn) return 1;

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
    if (res.banana_sprite)      { sprite_destroy(res.banana_sprite);      res.banana_sprite      = NULL; }
    if (res.oil_puddle_sprite)  { sprite_destroy(res.oil_puddle_sprite);  res.oil_puddle_sprite  = NULL; }
    if (res.fence_sprite)       { sprite_destroy(res.fence_sprite);       res.fence_sprite       = NULL; }
    if (res.sand_pebbles_sprite){ sprite_destroy(res.sand_pebbles_sprite);res.sand_pebbles_sprite= NULL; }
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
    if (res.mode_select_title)   { sprite_destroy(res.mode_select_title);   res.mode_select_title   = NULL; }
    if (res.mode_race_card)      { sprite_destroy(res.mode_race_card);      res.mode_race_card      = NULL; }
    if (res.mode_endurance_card) { sprite_destroy(res.mode_endurance_card); res.mode_endurance_card = NULL; }
    if (res.mode_race_label)      { sprite_destroy(res.mode_race_label);      res.mode_race_label      = NULL; }
    if (res.mode_endurance_label) { sprite_destroy(res.mode_endurance_label); res.mode_endurance_label = NULL; }
    for (int f = 0; f < res.car_format_count; f++)
        for (int p = 0; p < 2; p++)
            for (int s = 0; s < 4; s++)
                if (res.car_format_sprites[f][p][s]) {
                    sprite_destroy(res.car_format_sprites[f][p][s]);
                    res.car_format_sprites[f][p][s] = NULL;
                }
    res.car_format_count = 0;
    for (int i = 0; i < 2; i++)
        if (res.win_img[i]) { sprite_destroy(res.win_img[i]); res.win_img[i] = NULL; }
    if (res.win_play_again_btn) { sprite_destroy(res.win_play_again_btn); res.win_play_again_btn = NULL; }
    if (res.win_menu_btn)       { sprite_destroy(res.win_menu_btn);       res.win_menu_btn       = NULL; }
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

Sprite* resources_get_digit_sprite(int digit) {
    if (digit < 0 || digit > 9) return NULL;
    return res.digit_sprites[digit];
}

Sprite* resources_get_colon_sprite(void) { return res.colon_sprite; }

Sprite* resources_get_obstacle_sprite_themed(int theme) {
    if (theme == 1) return res.obstacle_desert_sprite;
    return res.obstacle_sprite;
}

Sprite* resources_get_fence_sprite(void)        { return res.fence_sprite; }
Sprite* resources_get_oil_puddle_sprite(void)   { return res.oil_puddle_sprite; }
Sprite* resources_get_sand_pebbles_sprite(void) { return res.sand_pebbles_sprite; }
Sprite* resources_get_mode_select_title(void)   { return res.mode_select_title; }
Sprite* resources_get_mode_race_card(void)       { return res.mode_race_card; }
Sprite* resources_get_mode_endurance_card(void)  { return res.mode_endurance_card; }
Sprite* resources_get_mode_race_label(void)      { return res.mode_race_label; }
Sprite* resources_get_mode_endurance_label(void) { return res.mode_endurance_label; }

int resources_get_car_format_count(void) { return res.car_format_count; }

Sprite* resources_get_car_format_preview(int fmt, int player) {
    if (fmt < 0 || fmt >= res.car_format_count || player < 0 || player > 1) return NULL;
    return res.car_format_sprites[fmt][player][CAR_STATE_NORMAL];
}

void resources_apply_car_format(int fmt1, int fmt2) {
    if (fmt1 < 0 || fmt1 >= res.car_format_count) return;
    if (fmt2 < 0 || fmt2 >= res.car_format_count) return;
    for (int s = 0; s < 4; s++) {
        if (res.car_format_sprites[fmt1][0][s])
            res.car_sprites[0][s] = res.car_format_sprites[fmt1][0][s];
        if (res.car_format_sprites[fmt2][1][s])
            res.car_sprites[1][s] = res.car_format_sprites[fmt2][1][s];
    }
}

Sprite* resources_get_win_img(int winner) {
    if (winner == 1) return res.win_img[0]; /* blue wins */
    if (winner == 2) return res.win_img[1]; /* red wins  */
    return NULL;
}
Sprite* resources_get_win_play_again_btn(void) { return res.win_play_again_btn; }
Sprite* resources_get_win_menu_btn(void)       { return res.win_menu_btn; }
