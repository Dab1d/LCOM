#ifndef __PROJ_GAME_H
#define __PROJ_GAME_H

#include "../sprite/sprite.h"
//depois será preciso dar include dos models que formos
//criando 

typedef enum {
    MAIN_MENU,
    GAMEPLAY,
    PAUSE,
    GAME_OVER, //diz qual jogador ganhou
    EXIT
} GameState;



void game_init(void);
GameState game_get_state(void);
void game_set_state( GameState new_state);
int game_check_collision(void);

typedef struct{
    Sprite *sprite;
    int speed;
} Car;

typedef struct{
    Sprite *sprite;
} Obstacle;

#endif /* __PROJ_GAME_H */

