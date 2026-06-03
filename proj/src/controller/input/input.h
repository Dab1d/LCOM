#ifndef __PROJ_INPUT_H
#define __PROJ_INPUT_H

#include <stdint.h>
#include <stdbool.h>

// Call at the end of every keyboard interrupt to update extended-key state
void input_update(void);
void input_flush(void);

// Call once at startup to create the menu cursor
void input_init_cursor(int screen_w, int screen_h);

// Call on every complete mouse packet to move the cursor
void input_mouse_update(int dx, int dy, bool lb, bool rb);

int input_esc_pressed(void);

// Combined keyboard + mouse checks used by game states
int input_menu_start_pressed(void);
int input_gameover_restart_pressed(void);
int input_gameover_menu_pressed(void);

// Keyboard
int input_keyboard_start_pressed(void);
int input_keyboard_restart_pressed(void);
int input_keyboard_menu_pressed(void);
int input_keyboard_car_left_pressed(void);
int input_keyboard_car_right_pressed(void);
int input_keyboard_car1_left_pressed(void);
int input_keyboard_car1_right_pressed(void);
int input_keyboard_pause_pressed(void);
int input_keyboard_up_pressed(void);
int input_keyboard_down_pressed(void);
int input_keyboard_confirm_pressed(void);

// Menu keyboard navigation
int input_menu_nav_up(void);
int input_menu_nav_down(void);

// Gameplay mouse → car2 lane control (consumes accumulated dx)
int input_mouse_car2_left(void);
int input_mouse_car2_right(void);

// Mouse menu: position hover and click detection
int input_mouse_over_start(void);
int input_mouse_over_exit(void);
int input_mouse_start_pressed(void);
int input_mouse_exit_pressed(void);
int input_mouse_restart_pressed(void);
int input_mouse_menu_pressed(void);

#endif /* __PROJ_INPUT_H */
