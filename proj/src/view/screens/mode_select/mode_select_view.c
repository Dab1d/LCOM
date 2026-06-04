#include "mode_select_view.h"
#include "../../view.h"
#include "../../../model/resources/resources.h"
#include "../../../controller/input/input.h"
#include "../../../controller/palette/palette.h"

#define SCREEN_W       1024
#define CARD_W          200
#define CARD_H          200
#define CARD_GAP         80
#define CARDS_TOTAL_W   (CARD_W + CARD_GAP + CARD_W)
#define RACE_CARD_X     ((SCREEN_W - CARDS_TOTAL_W) / 2)
#define ENDUR_CARD_X    (RACE_CARD_X + CARD_W + CARD_GAP)
#define CARDS_Y         280
#define LABEL_Y         (CARDS_Y + CARD_H + 16)
#define TITLE_Y          80
#define BORDER_T          4

#define MODE_RACE       0
#define MODE_ENDURANCE  1

static void draw_card_highlight(int x, int y) {
    draw_rect(x - BORDER_T, y - BORDER_T, CARD_W + 2 * BORDER_T, BORDER_T, PAL_BTN_YLW);
    draw_rect(x - BORDER_T, y + CARD_H,   CARD_W + 2 * BORDER_T, BORDER_T, PAL_BTN_YLW);
    draw_rect(x - BORDER_T, y,            BORDER_T,               CARD_H,   PAL_BTN_YLW);
    draw_rect(x + CARD_W,   y,            BORDER_T,               CARD_H,   PAL_BTN_YLW);
}

void mode_select_view_draw(int selection) {
    Sprite *title      = resources_get_mode_select_title();
    Sprite *race       = resources_get_mode_race_card();
    Sprite *endur      = resources_get_mode_endurance_card();
    Sprite *race_lbl   = resources_get_mode_race_label();
    Sprite *endur_lbl  = resources_get_mode_endurance_label();

    if (title) {
        int tw = title->width  * 3 / 2;
        int th = title->height * 3 / 2;
        draw_sprite_scaled(title, (SCREEN_W - tw) / 2, TITLE_Y, tw, th);
    }

    if (race)  draw_sprite(race,  RACE_CARD_X,  CARDS_Y);
    if (endur) draw_sprite(endur, ENDUR_CARD_X, CARDS_Y);

    if (race_lbl)
        draw_sprite(race_lbl,
                    RACE_CARD_X  + (CARD_W - race_lbl->width)  / 2, LABEL_Y);
    if (endur_lbl)
        draw_sprite(endur_lbl,
                    ENDUR_CARD_X + (CARD_W - endur_lbl->width) / 2, LABEL_Y);

    if (selection == MODE_RACE)
        draw_card_highlight(RACE_CARD_X, CARDS_Y);
    else
        draw_card_highlight(ENDUR_CARD_X, CARDS_Y);

    draw_sprite(resources_get_cursor_sprite(), input_cursor_x(), input_cursor_y());
}
