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
GameState game_get_state(void);
void game_set_state(GameState new_state);
void game_process_collisions(void);  // stub — implementar quando os modelos existirem
void game_update(void);
void game_process_input(void);
void game_render(void);
bool game_is_over(void);
void game_process_collisions(void);

#endif /* __PROJ_GAME_H */
