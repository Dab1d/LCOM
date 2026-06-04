#include "menu_view.h"
#include "../../view.h"
#include "../../../model/resources/resources.h"
#include "../../../controller/input/input.h"

#define SCREEN_W 1024

#define MENU_START 0
#define MENU_EXIT  1

void menu_view_draw(int selection, TrackTheme theme) {
    Sprite *title     = resources_get_menu_title();
    Sprite *start_btn = resources_get_menu_start_btn();
    Sprite *exit_btn  = resources_get_menu_exit_btn();

    if (title) {
        int tw = title->width  * 3 / 2;
        int th = title->height * 3 / 2;
        draw_sprite_scaled(title, (SCREEN_W - tw) / 2, 130, tw, th);
    }
    if (start_btn) {
        int bw = start_btn->width  * 5 / 4;
        int bh = start_btn->height * 5 / 4;
        if (selection == MENU_START) {
            int w = bw * 9 / 8;
            int h = bh * 9 / 8;
            draw_sprite_scaled(start_btn, (SCREEN_W - w) / 2, 420 - (h - bh) / 2, w, h);
        } else {
            draw_sprite_scaled(start_btn, (SCREEN_W - bw) / 2, 420, bw, bh);
        }
    }
    if (exit_btn) {
        int bw = exit_btn->width  * 5 / 4;
        int bh = exit_btn->height * 5 / 4;
        if (selection == MENU_EXIT) {
            int w = bw * 9 / 8;
            int h = bh * 9 / 8;
            draw_sprite_scaled(exit_btn, (SCREEN_W - w) / 2, 530 - (h - bh) / 2, w, h);
        } else {
            draw_sprite_scaled(exit_btn, (SCREEN_W - bw) / 2, 530, bw, bh);
        }
    }
    /* preview do bioma: tile 96x96 centrado abaixo dos botões + indicador ← → */
    Sprite *road_tile = resources_get_tile_sprite_themed(0, theme);
    if (road_tile) {
        int px = (SCREEN_W - 96) / 2;
        draw_sprite_scaled(road_tile, px, 640, 96, 96);
        /* setas de seleção */
        draw_sprite_scaled(road_tile, px - 64, 640, 48, 48);
        draw_sprite_scaled(road_tile, px + 96 + 16, 640, 48, 48);
    }
    draw_sprite(resources_get_cursor_sprite(), input_cursor_x(), input_cursor_y());
}
