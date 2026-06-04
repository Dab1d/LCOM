#ifndef __PROJ_PALETTE_H
#define __PROJ_PALETTE_H

#include <stdint.h>

/* ── Bloco 0: Base (0-7) ───────────────────────────────────────── */
#define PAL_BLACK          0
#define PAL_WHITE          1
#define PAL_GREY_LIGHT     2
#define PAL_GREY_MID       3
#define PAL_GREY_DARK      4
#define PAL_GREY_VERY_DARK 5
#define PAL_OFF_WHITE      6
#define PAL_CREAM          7

/* ── Bloco 1: Pista (8-23) ─────────────────────────────────────── */
#define PAL_ASPHALT_DARK   8
#define PAL_ASPHALT_MID    9
#define PAL_ASPHALT_BASE  10
#define PAL_ASPHALT_LIGHT 11
#define PAL_LANE_MARK     12
#define PAL_CENTRE_LINE   13
#define PAL_KERB_WHITE    14
#define PAL_KERB_RED      15
#define PAL_FINISH_DARK   16
#define PAL_FINISH_LIGHT  17
#define PAL_ROAD_EDGE     18
#define PAL_TYRE_MARK     19

/* ── Bloco 2: Cenário (24-39) ──────────────────────────────────── */
#define PAL_GRASS_BASE    24
#define PAL_GRASS_DARK    25
#define PAL_GRASS_LIGHT   26
#define PAL_GRASS_DRY     27
#define PAL_TREE_DARK     28
#define PAL_TREE_MID      29
#define PAL_TREE_LIGHT    30
#define PAL_TREE_TRUNK    31
#define PAL_SKY_BLUE      32
#define PAL_SKY_LIGHT     33
#define PAL_FENCE_GREY    34
#define PAL_FENCE_DARK    35

/* ── Bloco 3: Carro 1 – Azul (40-55) ──────────────────────────── */
#define PAL_CAR1_NORMAL   40
#define PAL_CAR1_HILITE   41
#define PAL_CAR1_SHADOW   42
#define PAL_CAR1_WINDOW   43
#define PAL_CAR1_WHEEL    44
#define PAL_CAR1_RIM      45
#define PAL_CAR1_DETAIL   46
#define PAL_CAR1_HEADLT   47
#define PAL_CAR1_TAILLT   48
#define PAL_CAR1_DAMAGED  49
#define PAL_CAR1_DMG_DRK  50
#define PAL_CAR1_BURNING  51
#define PAL_CAR1_FLAME    52
#define PAL_CAR1_SMOKE    53
#define PAL_CAR1_EXPLODED 54
#define PAL_CAR1_EXP_DRK  55

/* ── Bloco 4: Carro 2 – Vermelho (56-71) ──────────────────────── */
#define PAL_CAR2_NORMAL   56
#define PAL_CAR2_HILITE   57
#define PAL_CAR2_SHADOW   58
#define PAL_CAR2_WINDOW   59
#define PAL_CAR2_DAMAGED  60
#define PAL_CAR2_DMG_DRK  61
#define PAL_CAR2_BURNING  62
#define PAL_CAR2_FLAME    63
#define PAL_CAR2_SMOKE    64
#define PAL_CAR2_EXPLODED 65
#define PAL_CAR2_EXP_DRK  66

/* ── Bloco 5: Carro 3 – Amarelo (72-87) ───────────────────────── */
#define PAL_CAR3_NORMAL   72
#define PAL_CAR3_HILITE   73
#define PAL_CAR3_SHADOW   74
#define PAL_CAR3_WINDOW   75
#define PAL_CAR3_DAMAGED  76

/* ── Bloco 6: Carro 4 – Verde (88-103) ────────────────────────── */
#define PAL_CAR4_NORMAL   88
#define PAL_CAR4_HILITE   89
#define PAL_CAR4_SHADOW   90
#define PAL_CAR4_WINDOW   91
#define PAL_CAR4_DAMAGED  92

/* ── Bloco 7: Boost (104-119) ──────────────────────────────────── */
#define PAL_BOOST_BASE   104
#define PAL_BOOST_GLOW   105
#define PAL_BOOST_DARK   106
#define PAL_BOOST_OUTLINE 107
#define PAL_BOOST_STAR   108
#define PAL_BOOST_STAR2  109
#define PAL_BOOST_LIGHT  110

/* ── Bloco 8: Casca de banana (120-126) ─────────────────────────── */
#define PAL_BANANA_YELLOW 120   /* corpo principal */
#define PAL_BANANA_DARK   121   /* sombra / borda  */
#define PAL_BANANA_LIGHT  122   /* realce claro    */
#define PAL_BANANA_BROWN  123   /* manchas / dobra */
#define PAL_BANANA_STEM   124   /* ponta do caule  */
#define PAL_BANANA_TIP    125   /* ponta da banana */
#define PAL_BANANA_INNER  126   /* interior creme  */

/* ── Bloco 9: UI / HUD (136-191) ───────────────────────────────── */
#define PAL_HUD_BG       136
#define PAL_HUD_BORDER   137
#define PAL_HUD_TEXT     138
#define PAL_HUD_YELLOW   139
#define PAL_HUD_RED      140
#define PAL_HUD_GREEN    141
#define PAL_HEALTH_FULL  142
#define PAL_HEALTH_MID   143
#define PAL_HEALTH_LOW   144
#define PAL_P1_INDICATOR 145
#define PAL_P2_INDICATOR 146

/* ── Bloco 9 cont.: Menu / Botões (147-158) ────────────────────── */
#define PAL_MENU_DARK      147
#define PAL_BTN_RED        148
#define PAL_BTN_RED_DRK    149
#define PAL_BTN_RED_LGT    150
#define PAL_BTN_YLW        151
#define PAL_BTN_YLW_LGT    152
#define PAL_BTN_YLW_DRK    153
#define PAL_TTL_BLUE       154
#define PAL_TTL_NEAR_BLACK 155
#define PAL_TTL_BLUE_LGT   156
#define PAL_TTL_PINK       157
#define PAL_TTL_GREY       158

/* ── Transparente (255) ─────────────────────────────────────────── */
#define PAL_TRANSPARENT  255

/* ── Tabela de 256 cores RGB ────────────────────────────────────── */
extern const uint8_t GAME_PALETTE[256][3];

void    palette_load(void);
uint8_t palette_find_index(uint8_t r, uint8_t g, uint8_t b);

#endif /* __PROJ_PALETTE_H */
