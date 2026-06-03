#include "win_view.h"
#include "../view.h"
#include "../../model/resources/resources.h"
#include "../../model/car/car.h"

void win_view_draw(int winner) {
    if (winner < 1 || winner > 2) return;
    Sprite *car = resources_get_car_sprite(winner - 1, CAR_STATE_NORMAL);
    draw_sprite(car, WIN_CAR_X, WIN_CAR_Y);
}
