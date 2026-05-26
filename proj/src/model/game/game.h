#ifndef __PROJ_GAME_H
#define __PROJ_GAME_H


#include "../car/car.h"
// #include "../obstacle/obstacle.h"

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
void game_process_collisions(void);  // stub — implementar quando os modelos existirem

#endif /* __PROJ_GAME_H */