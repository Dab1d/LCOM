#ifndef __PROJ_CAR_VIEW_H
#define __PROJ_CAR_VIEW_H

#include "../../model/car/car.h"

typedef struct {
    Sprite *sprites[4];  // um por CarState — indexado por car->state
} CarView;

CarView* car_view_create(int width, int height);
void     car_view_update(CarView *cv, Car *car);
void     car_view_destroy(CarView *cv);

#endif /* __PROJ_CAR_VIEW_H */
