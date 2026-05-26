#ifndef __PROJ_INPUT_H
#define __PROJ_INPUT_H

#include <stdint.h>

int input_menu_start_pressed(void);
//if the player is in the menu and presses start to start the game

int input_gameover_restart_pressed(void);
//the game finishes and the player presses restart

int input_gameover_menu_pressed(void);
//the game ends and the player wants to go back to the menu

int input_keyboard_start_pressed(void);
int input_mouse_start_pressed(void);
int input_keyboard_restart_pressed(void);
int input_mouse_restart_pressed(void);
int input_keyboard_menu_pressed(void);
int input_mouse_menu_pressed(void);


#endif /* __PROJ_INPUT_H */

//não há nada para a pausa?
