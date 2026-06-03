#ifndef __PROJ_GAME_H
#define __PROJ_GAME_H


#include "../car/car.h"
#include "../track/track.h"
#include "../obstacle/obstacle.h"

typedef enum {
    MAIN_MENU,
    GAMEPLAY,
    PAUSE,
    GAME_OVER,
    EXIT
} GameState;

void game_init(void);
void game_tick(void);
GameState game_get_state(void);
void game_set_state(GameState new_state);

#endif /* __PROJ_GAME_H */
