#include "track_view.h"
#include "../../model/resources/resources.h"
#include "../view.h"
#include "../../model/car/car.h"

void track_view_draw(const Track *track) {
    if (!track) return;

    for (int screen_row = 0; screen_row <= TRACK_VISIBLE_ROWS; screen_row++) {
        int y = screen_row * TRACK_TILE_HEIGHT + (int)track->scroll_offset;

        for (int lane = 0; lane < TRACK_LANES; lane++) {
            int logical_row = track->scroll_row + 2 * CAR_SCREEN_ROW - screen_row;
            TileType type   = track_get_tile(track, logical_row, lane);

            Sprite *sp = resources_get_tile_sprite(type);
            if (!sp) continue;
            draw_sprite(sp, ROAD_OFFSET_X + lane * CAR_LANE_WIDTH, y);
        }
    }
}
