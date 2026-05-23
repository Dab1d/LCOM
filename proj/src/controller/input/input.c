#include "input.h"

//place holders
int input_keyboard_start_pressed(void)   { return 0; }
int input_mouse_start_pressed(void)      { return 0; }
int input_keyboard_restart_pressed(void) { return 0; }
int input_mouse_restart_pressed(void)    { return 0; }
int input_keyboard_menu_pressed(void)    { return 0; }
int input_mouse_menu_pressed(void)       { return 0; }

int input_menu_start_pressed(void) {
    return input_keyboard_start_pressed() || input_mouse_start_pressed();
}

int input_gameover_restart_pressed(void) {
    return input_keyboard_restart_pressed() || input_mouse_restart_pressed();
}

int input_gameover_menu_pressed(void) {
    return input_keyboard_menu_pressed() || input_mouse_menu_pressed();
}