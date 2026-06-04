/**
 * @file scenery.h
 * @brief Lateral scenery: tree/cactus instances that scroll alongside the track.
 */

#ifndef __PROJ_SCENERY_H
#define __PROJ_SCENERY_H

#include "../elements/track/track.h"

#define MAX_TREES 120 /**< Maximum number of scenery instances alive at once. */
#define TREE_SIZE  32 /**< Sprite width/height of one scenery object in pixels. */

/**
 * @brief One scenery sprite instance placed beside the track.
 */
typedef struct {
    int    screen_x;    /**< Horizontal pixel position on screen. */
    int    logical_row; /**< Logical track row this instance was spawned at. */
    double screen_y;    /**< Vertical pixel position, updated each scroll tick. */
} TreeInstance;

/**
 * @brief Collection of all active scenery instances and their shared scroll state.
 */
typedef struct {
    TreeInstance trees[MAX_TREES]; /**< Array of active scenery instances. */
    int          count;            /**< Number of currently active instances. */
    float        scroll_offset;    /**< Current sub-tile scroll offset in pixels. */
} Scenery;

/**
 * @brief Allocates and initialises a Scenery collection.
 * @return Pointer to the new Scenery, or NULL on allocation failure.
 */
Scenery* scenery_create(void);

/**
 * @brief Synchronises the scenery positions with the current track scroll.
 *
 * Spawns new instances at the bottom and removes those that scroll off the top.
 * @param s     Scenery collection to update.
 * @param track Current track (provides scroll_row and scroll_offset).
 */
Scenery* scenery_create(TrackTheme theme);
void     scenery_update(Scenery *s, const Track *track);

/**
 * @brief Frees a Scenery collection.
 * @param s Scenery to destroy.
 */
void     scenery_destroy(Scenery *s);

#endif /* __PROJ_SCENERY_H */
