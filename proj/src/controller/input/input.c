#include "input.h"
#include "kbc.h"
#include "../../model/cursor/cursor.h"
#include <stdbool.h>
#include <stdlib.h>

#define ESC_MAKECODE        0x01
#define ENTER_MAKECODE      0x1C
#define ARROW_PREFIX        0xE0
#define ARROW_LEFT_CODE     0x4B
#define ARROW_RIGHT_CODE    0x4D
#define ARROW_UP_CODE       0x48
#define ARROW_DOWN_CODE     0x50

/* Menu button layout — must match the positions used in game_render */
#define MENU_BTN_W    256
#define MENU_BTN_H     64
#define MENU_SCREEN_W 1024
#define MENU_START_X  ((MENU_SCREEN_W - MENU_BTN_W) / 2)
#define MENU_START_Y  420
#define MENU_EXIT_X   ((MENU_SCREEN_W - MENU_BTN_W) / 2)
#define MENU_EXIT_Y   510

#define MOUSE_LANE_THRESHOLD 10

static bool prev_extended  = false;
static Cursor *menu_cursor = NULL;
static int mouse_dx_accum  = 0;

void input_init_cursor(int screen_w, int screen_h) {
    if (menu_cursor) { destroy_cursor(menu_cursor); }
    menu_cursor = create_cursor(screen_w / 2, screen_h / 2, screen_w, screen_h);
}

void input_mouse_update(int dx, int dy, bool lb) {
    if (menu_cursor) cursor_update(menu_cursor, dx, dy, lb);
    mouse_dx_accum += dx;
}

int input_mouse_car2_left(void) {
    if (mouse_dx_accum <= -MOUSE_LANE_THRESHOLD) { mouse_dx_accum = 0; return 1; }
    return 0;
}

int input_mouse_car2_right(void) {
    if (mouse_dx_accum >= MOUSE_LANE_THRESHOLD) { mouse_dx_accum = 0; return 1; }
    return 0;
}

void input_update(void) {
    prev_extended = (get_current_scancode() == ARROW_PREFIX);
}

int input_esc_pressed(void) {
    return get_current_scancode() == ESC_MAKECODE;
}

int input_keyboard_start_pressed(void)   { return get_current_scancode() == ENTER_MAKECODE; }
int input_keyboard_restart_pressed(void) { return get_current_scancode() == ENTER_MAKECODE; }
int input_keyboard_menu_pressed(void)    { return get_current_scancode() == ESC_MAKECODE; }

int input_keyboard_car_left_pressed(void) {
    return prev_extended && get_current_scancode() == ARROW_LEFT_CODE;
}

int input_keyboard_car_right_pressed(void) {
    return prev_extended && get_current_scancode() == ARROW_RIGHT_CODE;
}

int input_menu_nav_up(void) {
    return prev_extended && get_current_scancode() == ARROW_UP_CODE;
}

int input_menu_nav_down(void) {
    return prev_extended && get_current_scancode() == ARROW_DOWN_CODE;
}

static int over_rect(int rx, int ry, int rw, int rh) {
    if (!menu_cursor) return 0;
    int cx = cursor_get_x(menu_cursor), cy = cursor_get_y(menu_cursor);
    return cx >= rx && cx < rx + rw && cy >= ry && cy < ry + rh;
}

int input_mouse_over_start(void) { return over_rect(MENU_START_X, MENU_START_Y, MENU_BTN_W, MENU_BTN_H); }
int input_mouse_over_exit(void)  { return over_rect(MENU_EXIT_X,  MENU_EXIT_Y,  MENU_BTN_W, MENU_BTN_H); }

int input_mouse_start_pressed(void) {
    return menu_cursor && cursor_left_clicked(menu_cursor) && input_mouse_over_start();
}
int input_mouse_exit_pressed(void) {
    return menu_cursor && cursor_left_clicked(menu_cursor) && input_mouse_over_exit();
}
int input_mouse_restart_pressed(void) { return 0; }
int input_mouse_menu_pressed(void)    { return 0; }

int input_menu_start_pressed(void) {
    return input_keyboard_start_pressed() || input_mouse_start_pressed();
}

int input_gameover_restart_pressed(void) {
    return input_keyboard_restart_pressed() || input_mouse_restart_pressed();
}

int input_gameover_menu_pressed(void) {
    return input_keyboard_menu_pressed() || input_mouse_menu_pressed();
}
