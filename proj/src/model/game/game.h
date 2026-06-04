/**
 * @file game.h
 * @brief Top-level game state: lifecycle, tick loop, and global state accessor.
 */

#ifndef __PROJ_GAME_H
#define __PROJ_GAME_H

#include <stdint.h>
#include "../car/car.h"
#include "../track/track.h"
#include "../obstacle/obstacle.h"
#include "../boost/boost.h"
#include "../scenery/scenery.h"

#define MAX_OBSTACLES 200 /**< Maximum number of obstacle objects alive at once. */
#define MAX_BOOSTS     50 /**< Maximum number of boost pickups alive at once. */

/**
 * @brief Top-level game screen / phase enumeration.
 */
typedef enum {
    MAIN_MENU,   /**< Main menu screen. */
    MODE_SELECT, /**< Game-mode selection screen. */
    GAMEPLAY,    /**< Active race. */
    PAUSE,       /**< Pause overlay. */
    GAME_OVER,   /**< Win/loss result screen. */
    EXIT         /**< Application shutdown requested. */
} GameState;

/**
 * @brief Aggregate game state: all dynamic objects and session metadata.
 */
typedef struct {
    GameState  state;           /**< Current screen/phase. */
    int        pause_selected;  /**< Pause cursor: 0=RESUME, 1=QUIT. */
    int        menu_selection;  /**< Main-menu cursor: 0=START, 1=EXIT. */
    int        mode_selection;  /**< Mode-select cursor: 0=RACE, 1=ENDURANCE. */
    int        winner;          /**< 0=none, 1=Player 1, 2=Player 2. */
    uint32_t   elapsed_ticks;   /**< Ticks elapsed during GAMEPLAY (60 Hz). */
    TrackTheme selected_theme;  /**< Biome chosen on the menu. */
    Track     *track;           /**< Active track (owns scroll speed). */
    Car       *car1;            /**< Player 1 car (owns lives and score). */
    Car       *car2;            /**< Player 2 car. */
    Scenery   *scenery;         /**< Lateral scenery instances. */
    Obstacle  *obstacles[MAX_OBSTACLES]; /**< Active obstacle pool. */
    int        obstacle_count;  /**< Number of active obstacles. */
    Boost     *boosts[MAX_BOOSTS];       /**< Active boost pool. */
    int        boost_count;     /**< Number of active boosts. */
} Game;

/**
 * @brief Allocates all sub-objects for a Game (track, cars, scenery).
 * @param game Game to populate.
 */
void game_create(Game *game);

/**
 * @brief Resets a Game to the start-of-race state without reallocating.
 * @param game Game to reset.
 */
void game_reset(Game *game);

/**
 * @brief Initialises the global game singleton and loads resources.
 */
void game_init(void);

/**
 * @brief Frees all resources owned by the global game singleton.
 */
void game_cleanup(void);

/**
 * @brief Advances the game by one tick (called at 60 Hz by the interrupt handler).
 *
 * Handles input, physics, collision detection, and state transitions.
 */
void game_tick(void);

/**
 * @brief Returns the current game phase.
 * @return Active GameState value.
 */
GameState game_get_state(void);

/**
 * @brief Transitions the game to a new phase.
 * @param new_state GameState to switch to.
 */
void game_set_state(GameState new_state);

/**
 * @brief Returns a read-only pointer to the global Game struct.
 * @return Pointer to the current Game; valid until game_cleanup() is called.
 */
const Game* game_get(void);

#endif /* __PROJ_GAME_H */
