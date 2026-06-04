#include "scenery_view.h"
#include "../../view.h"
#include "../../../model/resources/resources.h"

#define STRIP_TILES 3

void scenery_view_draw(const Scenery *s) {
    if (!s) return;
    Sprite *grass = resources_get_grass_sprite();
    Sprite *tree  = resources_get_tree_sprite();

    int tile     = TRACK_TILE_HEIGHT;
    int off      = (int)s->scroll_offset;
    int road_end = ROAD_OFFSET_X + 10 * CAR_LANE_WIDTH;

    for (int screen_row = 0; screen_row <= TRACK_VISIBLE_ROWS; screen_row++) {
        int y = screen_row * tile - off;
        for (int col = 0; col < STRIP_TILES; col++) {
            if (grass) {
                draw_sprite(grass, col * tile, y);
                draw_sprite(grass, road_end + col * tile, y);
            }
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
