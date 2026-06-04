/**
 * @file resources.h
 * @brief Global sprite cache — loads and owns all game assets at startup.
 */

#ifndef __PROJ_RESOURCES_H
#define __PROJ_RESOURCES_H

#include "../sprite/sprite.h"

/**
 * @brief Container for every sprite used by the game.
 *
 * Owned exclusively by the resources module; all other modules hold
 * non-owning pointers obtained through the getter functions below.
 */
typedef struct {
    Sprite *car_sprites[2][4];        /**< [player-1][CarState] */
    Sprite *obstacle_sprite;          /**< Rock obstacle — city theme. */
    Sprite *boost_sprite;             /**< Boost pickup. */
    Sprite *tile_sprites[4];          /**< City road tiles, indexed by TileType. */
    Sprite *tile_sprites_desert[4];   /**< Desert road tiles, indexed by TileType. */
    Sprite *grass_sprite;             /**< City/forest lateral ground. */
    Sprite *sand_sprite;              /**< Desert lateral ground. */
    Sprite *tree_sprite;              /**< City/forest lateral scenery. */
    Sprite *cactus_sprite;            /**< Desert lateral scenery. */
    Sprite *divider_sprite;           /**< Lane divider line. */
    Sprite *obstacle_desert_sprite;   /**< Barrel — same damage effect as rock. */
    Sprite *haybale_sprite;           /**< Hay bale — same damage effect as rock. */
    Sprite *menu_title;               /**< Main menu title graphic. */
    Sprite *menu_start_btn;           /**< START button. */
    Sprite *menu_exit_btn;            /**< EXIT button. */
    Sprite *pause_panel;              /**< Pause overlay background panel. */
    Sprite *pause_resume_btn[2];      /**< [0]=normal  [1]=highlighted. */
    Sprite *pause_quit_btn[2];        /**< [0]=normal  [1]=highlighted. */
    Sprite *cursor_sprite;            /**< Mouse cursor. */
    Sprite *banana_sprite;            /**< Banana-peel obstacle. */
    Sprite *heart_sprite;             /**< Heart icon for life counter. */
    Sprite *digit_sprites[10];        /**< Digit glyphs 0–9 for the timer. */
    Sprite *colon_sprite;             /**< Colon ':' glyph for the timer. */
    Sprite *fence_sprite;             /**< Fence scenery element. */
    Sprite *oil_puddle_sprite;        /**< Oil puddle obstacle. */
    Sprite *sand_pebbles_sprite;      /**< Sand pebbles scenery element. */
    Sprite *mode_select_title;        /**< Mode-selection screen title. */
    Sprite *mode_race_card;           /**< RACE mode card graphic. */
    Sprite *mode_endurance_card;      /**< ENDURANCE mode card graphic. */
    Sprite *mode_race_label;          /**< RACE mode label. */
    Sprite *mode_endurance_label;     /**< ENDURANCE mode label. */
} Resources;

/**
 * @brief Loads all game sprites from their XPM sources into the global cache.
 * @return 0 on success, non-zero on the first allocation failure.
 */
int  resources_load(void);

/**
 * @brief Frees every sprite in the global resource cache.
 */
void resources_destroy(void);

/**
 * @brief Returns the sprite for a car in a given visual state.
 * @param player 0 for player 1, 1 for player 2.
 * @param state  CarState index (0–3).
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_car_sprite(int player, int state);

/**
 * @brief Returns the rock obstacle sprite for the city theme.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_obstacle_sprite(void);

/**
 * @brief Returns the boost pickup sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_boost_sprite(void);

/**
 * @brief Returns a city-theme road tile sprite.
 * @param type TileType index (0–3).
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_tile_sprite(int type);

/**
 * @brief Returns the city/forest lateral ground sprite.
 * @return Non-owning pointer to the grass sprite.
 */
Sprite* resources_get_grass_sprite(void);

/**
 * @brief Returns the city/forest lateral scenery sprite.
 * @return Non-owning pointer to the tree sprite.
 */
Sprite* resources_get_tree_sprite(void);

/**
 * @brief Returns the lateral ground sprite for the given theme.
 * @param theme TrackTheme value.
 * @return Grass sprite for city/forest; sand sprite for desert.
 */
Sprite* resources_get_ground_sprite(int theme);

/**
 * @brief Returns the lateral scenery sprite for the given theme.
 * @param theme TrackTheme value.
 * @return Tree sprite for city/forest; cactus sprite for desert.
 */
Sprite* resources_get_scenery_sprite(int theme);

/**
 * @brief Returns a road tile sprite for the given tile type and theme.
 * @param type  TileType index.
 * @param theme TrackTheme value.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_tile_sprite_themed(int type, int theme);

/**
 * @brief Returns the lane-divider sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_divider_sprite(void);

/**
 * @brief Returns the main menu title sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_menu_title(void);

/**
 * @brief Returns the START button sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_menu_start_btn(void);

/**
 * @brief Returns the EXIT button sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_menu_exit_btn(void);

/**
 * @brief Returns the pause overlay panel sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_pause_panel(void);

/**
 * @brief Returns the RESUME button sprite.
 * @param selected 1 if the button is currently highlighted, 0 otherwise.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_pause_resume_btn(int selected);

/**
 * @brief Returns the QUIT button sprite.
 * @param selected 1 if the button is currently highlighted, 0 otherwise.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_pause_quit_btn(int selected);

/**
 * @brief Returns the mouse cursor sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_cursor_sprite(void);

/**
 * @brief Returns the banana-peel obstacle sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_banana_sprite(void);

/**
 * @brief Returns the heart (life counter) sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_heart_sprite(void);

/**
 * @brief Returns the digit sprite for a numeric glyph.
 * @param digit Value in [0, 9].
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_digit_sprite(int digit);

/**
 * @brief Returns the colon ':' sprite for the timer display.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_colon_sprite(void);

/**
 * @brief Returns the obstacle sprite for a given track theme.
 * @param theme TrackTheme value.
 * @return Rock sprite for city/forest; barrel sprite for desert.
 */
Sprite* resources_get_obstacle_sprite_themed(int theme);

/**
 * @brief Returns the mode-selection screen title sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_fence_sprite(void);
Sprite* resources_get_oil_puddle_sprite(void);
Sprite* resources_get_sand_pebbles_sprite(void);
Sprite* resources_get_mode_select_title(void);

/**
 * @brief Returns the RACE mode card sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_mode_race_card(void);

/**
 * @brief Returns the ENDURANCE mode card sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_mode_endurance_card(void);

/**
 * @brief Returns the RACE mode label sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_mode_race_label(void);

/**
 * @brief Returns the ENDURANCE mode label sprite.
 * @return Non-owning pointer to the sprite.
 */
Sprite* resources_get_mode_endurance_label(void);

#endif /* __PROJ_RESOURCES_H */
