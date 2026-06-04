#include "hud_view.h"
#include "../../view.h"
#include "../../../model/resources/resources.h"

#define HEART_SIZE 48
#define HEART_GAP   6
#define HUD_Y       8
#define SCREEN_W 1024

void hud_view_draw(const Car *car1, const Car *car2) {
    Sprite *heart = resources_get_heart_sprite();
    if (!heart) return;

    int lives1 = car1 ? car1->lives : 0;
    for (int i = 0; i < lives1; i++)
        draw_sprite_scaled(heart, HUD_Y + i * (HEART_SIZE + HEART_GAP), HUD_Y, HEART_SIZE, HEART_SIZE);

    int lives2 = car2 ? car2->lives : 0;
    for (int i = 0; i < lives2; i++)
        draw_sprite_scaled(heart, SCREEN_W - HUD_Y - (i + 1) * (HEART_SIZE + HEART_GAP), HUD_Y, HEART_SIZE, HEART_SIZE);
}
