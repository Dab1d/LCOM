#ifndef __PROJ_INPUT_H
#define __PROJ_INPUT_H

#include <stdint.h>

// Call at the end of every keyboard interrupt to update extended-key state
void input_update(void);

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
int input_keyboard_pause_pressed(void);
int input_keyboard_up_pressed(void);
int input_keyboard_down_pressed(void);
int input_keyboard_confirm_pressed(void);

// Mouse (stubs until mouse player is wired up)
int input_mouse_start_pressed(void);
int input_mouse_restart_pressed(void);
int input_mouse_menu_pressed(void);

#endif /* __PROJ_INPUT_H */
