#ifndef __PROJ_GAME_H
#define __PROJ_GAME_H

#include "../car/car.h"
#include "../track/track.h"
#include "../obstacle/obstacle.h"
#include "../../view/scenery/scenery_view.h"

#define MAX_OBSTACLES 200

typedef enum {
    MAIN_MENU,
    GAMEPLAY,
    PAUSE,
    GAME_OVER,
    EXIT
} GameState;

typedef struct {
    GameState    state;
    int          pause_selected; /* 0=RESUME 1=QUIT */
    int          winner;         /* 0=nenhum 1=P1 2=P2 */
    Track       *track;          /* velocidade: track->scroll_speed */
    Car         *car1;           /* vidas: car1->lives  score: car1->score */
    Car         *car2;
    SceneryView *scenery;
    Obstacle    *obstacles[MAX_OBSTACLES];
    int          obstacle_count;
} Game;

void game_create(Game *game);
void game_reset(Game *game);

void game_init(void);
void game_tick(void);
GameState game_get_state(void);
void game_set_state(GameState new_state);
const Game* game_get(void);

#endif /* __PROJ_GAME_H */
