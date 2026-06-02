#ifndef __PROJ_GAME_H
#define __PROJ_GAME_H

#include <stdbool.h>
#include "../car/car.h"
#include "../track/track.h"
#include "../obstacle/obstacle.h"
#include "../cursor/cursor.h"

typedef enum {
    MAIN_MENU,
    GAMEPLAY,
    PAUSE,
    GAME_OVER,
    EXIT
} GameState;

void game_init(void);
GameState game_get_state(void);
void game_set_state(GameState new_state);
void game_update(void);
void game_process_input(void);
void game_process_mouse(int dx, int dy, bool lb);
void game_render(void);
bool game_is_over(void);
void game_process_collisions(void);
const Cursor *game_get_cursor(void);

#endif /* __PROJ_GAME_H */
