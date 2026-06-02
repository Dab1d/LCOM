#ifndef __PROJ_OBSTACLE_VIEW_H
#define __PROJ_OBSTACLE_VIEW_H

#include "../../model/obstacle/obstacle.h"

typedef struct {
    Sprite *sprite;
} ObstacleView;

ObstacleView* obstacle_view_create(void);
void          obstacle_view_update(ObstacleView *ov, Obstacle *obs);
void          obstacle_view_destroy(ObstacleView *ov);

#endif /* __PROJ_OBSTACLE_VIEW_H */
