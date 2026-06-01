#ifndef __PROJ_INPUT_H
#define __PROJ_INPUT_H

#include <stdint.h>

int input_esc_pressed(void);

int input_menu_start_pressed(void);
int input_gameover_restart_pressed(void);
int input_gameover_menu_pressed(void);

int input_keyboard_start_pressed(void);
int input_mouse_start_pressed(void);
int input_keyboard_restart_pressed(void);
int input_mouse_restart_pressed(void);
int input_keyboard_menu_pressed(void);
int input_mouse_menu_pressed(void);

#endif /* __PROJ_INPUT_H */

//não há nada para a pausa?
