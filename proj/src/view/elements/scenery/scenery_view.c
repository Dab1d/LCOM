#include "scenery_view.h"
#include "../../view.h"
#include "../../../model/resources/resources.h"

#define STRIP_TILES 3

void scenery_view_draw(const Scenery *s, TrackTheme theme) {
    if (!s) return;
    Sprite *ground  = resources_get_ground_sprite(theme);
    Sprite *ground2 = (theme == TRACK_THEME_DESERT) ? resources_get_sand_pebbles_sprite() : NULL;
    Sprite *tree    = resources_get_scenery_sprite(theme);
    Sprite *fence   = (theme == TRACK_THEME_DESERT) ? resources_get_fence_sprite() : NULL;

    int tile     = TRACK_TILE_HEIGHT;
    int off      = (int)s->scroll_offset;
    int road_end = ROAD_OFFSET_X + 10 * CAR_LANE_WIDTH;

    for (int screen_row = 0; screen_row <= TRACK_VISIBLE_ROWS; screen_row++) {
        int y = (screen_row - 1) * tile + off;
        for (int col = 0; col < STRIP_TILES; col++) {
            Sprite *g = (ground2 && col == 1) ? ground2 : ground;
            if (g) {
                draw_sprite(g, col * tile, y);
                draw_sprite(g, road_end + col * tile, y);
            }
        }
        if (fence) {
            draw_sprite(fence, ROAD_OFFSET_X - tile, y);
            draw_sprite(fence, road_end, y);
        }
    }

    if (!tree) return;
    int screen_height = TRACK_VISIBLE_ROWS * tile;
    for (int i = 0; i < s->count; i++) {
        int y = (int)s->trees[i].screen_y;
        if (y + TREE_SIZE < 0 || y >= screen_height) continue;
        draw_sprite(tree, s->trees[i].screen_x, y);
    }
}
