#include "input.h"
#include "kbc.h"
#include <stdbool.h>

#define ESC_MAKECODE        0x01
#define ENTER_MAKECODE      0x1C
#define ARROW_PREFIX        0xE0
#define ARROW_LEFT_CODE     0x4B
#define ARROW_RIGHT_CODE    0x4D
#define ARROW_UP_CODE       0x48
#define ARROW_DOWN_CODE     0x50

static bool prev_extended = false;

// Must be called at the end of each keyboard interrupt so the next
// interrupt knows whether the current byte was an E0 prefix.
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

int input_keyboard_pause_pressed(void)  { return get_current_scancode() == ESC_MAKECODE; }
int input_keyboard_up_pressed(void)     { return prev_extended && get_current_scancode() == ARROW_UP_CODE; }
int input_keyboard_down_pressed(void)   { return prev_extended && get_current_scancode() == ARROW_DOWN_CODE; }
int input_keyboard_confirm_pressed(void){ return get_current_scancode() == ENTER_MAKECODE; }

// Mouse stubs — filled in when the mouse player is wired up
int input_mouse_start_pressed(void)   { return 0; }
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
