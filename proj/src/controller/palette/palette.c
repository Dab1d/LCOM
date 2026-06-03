#include "palette.h"
#include <lcom/lcf.h>

/* ── GAME_PALETTE[256][3]: valores RGB para cada índice 0-255 ──── *
 *
 * Regras de unicidade: cada cor usada em ficheiros XPM deve aparecer
 * APENAS UMA VEZ na tabela para que xpm_load(XPM_INDEXED) faça o
 * match correto. As entradas sem uso ficam a preto.
 *
 * Blocos reservados:
 *   0-7   base        8-23  pista       24-39 cenário
 *  40-55  carro 1    56-71  carro 2     72-87  carro 3
 *  88-103 carro 4   104-119 boost      120-135 óleo
 * 136-191 HUD/UI    192-254 (livres)    255 transparente
 */
const uint8_t GAME_PALETTE[256][3] = {
    /* ── Bloco 0: Base ── */
    /* 0  PAL_BLACK          */ {0x00, 0x00, 0x00},
    /* 1  PAL_WHITE          */ {0xFF, 0xFF, 0xFF},
    /* 2  PAL_GREY_LIGHT     */ {0xCC, 0xCC, 0xCC},
    /* 3  PAL_GREY_MID       */ {0x99, 0x99, 0x99},
    /* 4  PAL_GREY_DARK      */ {0x66, 0x66, 0x66},
    /* 5  PAL_GREY_VERY_DARK */ {0x33, 0x33, 0x33},
    /* 6  PAL_OFF_WHITE      */ {0xF0, 0xF0, 0xF0},
    /* 7  PAL_CREAM          */ {0xFF, 0xFA, 0xCD},

    /* ── Bloco 1: Pista ── */
    /* 8  PAL_ASPHALT_DARK   */ {0x2A, 0x2A, 0x2A},
    /* 9  PAL_ASPHALT_MID    */ {0x38, 0x38, 0x38},
    /* 10 PAL_ASPHALT_BASE   */ {0x44, 0x44, 0x44},
    /* 11 PAL_ASPHALT_LIGHT  */ {0x55, 0x55, 0x55},
    /* 12 PAL_LANE_MARK      */ {0xFF, 0xFF, 0x00},
    /* 13 PAL_CENTRE_LINE    */ {0xF8, 0xF8, 0xF8},
    /* 14 PAL_KERB_WHITE     */ {0xF0, 0xF0, 0xF0},
    /* 15 PAL_KERB_RED       */ {0xFF, 0x22, 0x22},
    /* 16 PAL_FINISH_DARK    */ {0x28, 0x28, 0x28},
    /* 17 PAL_FINISH_LIGHT   */ {0xEE, 0xEE, 0xEE},
    /* 18 PAL_ROAD_EDGE      */ {0x19, 0x19, 0x19},
    /* 19 PAL_TYRE_MARK      */ {0x1B, 0x1B, 0x1B},
    /* 20 (livre)            */ {0x00, 0x00, 0x00},
    /* 21 (livre)            */ {0x00, 0x00, 0x00},
    /* 22 (livre)            */ {0x00, 0x00, 0x00},
    /* 23 (livre)            */ {0x00, 0x00, 0x00},

    /* ── Bloco 2: Cenário ── */
    /* 24 PAL_GRASS_BASE     */ {0x3A, 0x7D, 0x44},
    /* 25 PAL_GRASS_DARK     */ {0x2A, 0x60, 0x30},
    /* 26 PAL_GRASS_LIGHT    */ {0x4A, 0x9A, 0x55},
    /* 27 PAL_GRASS_DRY      */ {0x8B, 0x73, 0x55},
    /* 28 PAL_TREE_DARK      */ {0x1A, 0x5C, 0x1A},
    /* 29 PAL_TREE_MID       */ {0x2E, 0x7D, 0x32},
    /* 30 PAL_TREE_LIGHT     */ {0x4C, 0xAF, 0x50},
    /* 31 PAL_TREE_TRUNK     */ {0x5D, 0x40, 0x37},
    /* 32 PAL_SKY_BLUE       */ {0x87, 0xCE, 0xEB},
    /* 33 PAL_SKY_LIGHT      */ {0xB0, 0xE0, 0xE6},
    /* 34 PAL_FENCE_GREY     */ {0x7A, 0x7A, 0x7A},
    /* 35 PAL_FENCE_DARK     */ {0x4A, 0x4A, 0x4A},
    /* 36 (livre)            */ {0x00, 0x00, 0x00},
    /* 37 (livre)            */ {0x00, 0x00, 0x00},
    /* 38 (livre)            */ {0x00, 0x00, 0x00},
    /* 39 (livre)            */ {0x00, 0x00, 0x00},

    /* ── Bloco 3: Carro 1 – cores extraídas de car_blue.xpm ── */
    /* 40 PAL_CAR1_NORMAL    */ {0x1A, 0x52, 0x76},
    /* 41 PAL_CAR1_HILITE    */ {0x24, 0x71, 0xA3},
    /* 42 PAL_CAR1_SHADOW    */ {0x15, 0x43, 0x60},
    /* 43 PAL_CAR1_WINDOW    */ {0x85, 0xC1, 0xE9},
    /* 44 PAL_CAR1_WHEEL     */ {0x1A, 0x1A, 0x1A},
    /* 45 PAL_CAR1_RIM       */ {0xF9, 0xE7, 0x9F},
    /* 46 PAL_CAR1_DETAIL    */ {0x22, 0x22, 0x22},
    /* 47 PAL_CAR1_HEADLT    */ {0xFE, 0xF9, 0xE7},
    /* 48 PAL_CAR1_TAILLT    */ {0xD6, 0xEA, 0xF8},
    /* 49 PAL_CAR1_DAMAGED   */ {0x2C, 0x7F, 0xB0},
    /* 50 PAL_CAR1_DMG_DRK   */ {0x1A, 0x3E, 0x58},
    /* 51 PAL_CAR1_BURNING   */ {0x12, 0x30, 0x48},
    /* 52 PAL_CAR1_FLAME     */ {0xFF, 0x88, 0x00},
    /* 53 PAL_CAR1_SMOKE     */ {0x77, 0x77, 0x77},
    /* 54 PAL_CAR1_EXPLODED  */ {0x50, 0x50, 0x50},
    /* 55 PAL_CAR1_EXP_DRK   */ {0x30, 0x30, 0x30},

    /* ── Bloco 4: Carro 2 – cores extraídas de car_red.xpm ── */
    /* 56 PAL_CAR2_NORMAL    */ {0xC0, 0x39, 0x2B},
    /* 57 PAL_CAR2_HILITE    */ {0xE7, 0x4C, 0x3C},
    /* 58 PAL_CAR2_SHADOW    */ {0xA9, 0x32, 0x26},
    /* 59 PAL_CAR2_WINDOW    */ {0x92, 0x2B, 0x21},
    /* 60 PAL_CAR2_DAMAGED   */ {0xD4, 0x5F, 0x3A},
    /* 61 PAL_CAR2_DMG_DRK   */ {0x8A, 0x28, 0x20},
    /* 62 PAL_CAR2_BURNING   */ {0x6E, 0x20, 0x18},
    /* 63 PAL_CAR2_FLAME     */ {0xFF, 0x66, 0x00},
    /* 64 PAL_CAR2_SMOKE     */ {0x68, 0x68, 0x68},
    /* 65 PAL_CAR2_EXPLODED  */ {0x48, 0x48, 0x48},
    /* 66 PAL_CAR2_EXP_DRK   */ {0x28, 0x28, 0x28},
    /* 67 (livre)            */ {0x00, 0x00, 0x00},
    /* 68 (livre)            */ {0x00, 0x00, 0x00},
    /* 69 (livre)            */ {0x00, 0x00, 0x00},
    /* 70 (livre)            */ {0x00, 0x00, 0x00},
    /* 71 (livre)            */ {0x00, 0x00, 0x00},

    /* ── Bloco 5: Carro 3 – Amarelo ── */
    /* 72 PAL_CAR3_NORMAL    */ {0xFF, 0xDD, 0x00},
    /* 73 PAL_CAR3_HILITE    */ {0xFF, 0xEE, 0x66},
    /* 74 PAL_CAR3_SHADOW    */ {0xCC, 0xAA, 0x00},
    /* 75 PAL_CAR3_WINDOW    */ {0xFF, 0xFF, 0xAA},
    /* 76 PAL_CAR3_DAMAGED   */ {0xFF, 0xAA, 0x00},
    /* 77-87 (livres)        */
    {0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},

    /* ── Bloco 6: Carro 4 – Verde ── */
    /* 88 PAL_CAR4_NORMAL    */ {0x00, 0xCC, 0x44},
    /* 89 PAL_CAR4_HILITE    */ {0x44, 0xEE, 0x66},
    /* 90 PAL_CAR4_SHADOW    */ {0x00, 0x99, 0x33},
    /* 91 PAL_CAR4_WINDOW    */ {0xAA, 0xFF, 0xCC},
    /* 92 PAL_CAR4_DAMAGED   */ {0xFF, 0xAA, 0x00},
    /* 93-103 (livres)       */
    {0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},

    /* ── Bloco 7: Boost ── */
    /* 104 PAL_BOOST_BASE    */ {0x60, 0x60, 0xDD},
    /* 105 PAL_BOOST_GLOW    */ {0xAA, 0xAA, 0xFF},
    /* 106 PAL_BOOST_DARK    */ {0x40, 0x40, 0xBB},
    /* 107 PAL_BOOST_OUTLINE */ {0xDD, 0xDD, 0xFF},
    /* 108 PAL_BOOST_STAR    */ {0xFF, 0xFF, 0x44},
    /* 109 PAL_BOOST_STAR2   */ {0xFF, 0xCC, 0x00},
    /* 110 PAL_BOOST_LIGHT   */ {0xCC, 0xCC, 0xFF},
    /* 111-119 (livres)      */
    {0},{0},{0},{0},{0},{0},{0},{0},{0},

    /* ── Bloco 8: Óleo ── */
    /* 120 PAL_OIL_BASE      */ {0x1A, 0x1A, 0x2E},
    /* 121 PAL_OIL_SHEEN1    */ {0x22, 0x33, 0xAA},
    /* 122 PAL_OIL_SHEEN2    */ {0x33, 0x44, 0xBB},
    /* 123 PAL_OIL_SHEEN3    */ {0x44, 0x55, 0xCC},
    /* 124 PAL_OIL_EDGE      */ {0x11, 0x11, 0x22},
    /* 125 PAL_OIL_REFLECT   */ {0x66, 0x77, 0xDD},
    /* 126 PAL_OIL_DARK      */ {0x0A, 0x0A, 0x1E},
    /* 127-135 (livres)      */
    {0},{0},{0},{0},{0},{0},{0},{0},{0},

    /* ── Bloco 9: HUD/UI ── */
    /* 136 PAL_HUD_BG        */ {0x00, 0x00, 0x33},
    /* 137 PAL_HUD_BORDER    */ {0x44, 0x44, 0xAA},
    /* 138 PAL_HUD_TEXT      */ {0xF4, 0xF4, 0xF4},
    /* 139 PAL_HUD_YELLOW    */ {0xFF, 0xD7, 0x00},
    /* 140 PAL_HUD_RED       */ {0xFF, 0x22, 0x00},
    /* 141 PAL_HUD_GREEN     */ {0x00, 0xCC, 0x48},
    /* 142 PAL_HEALTH_FULL   */ {0x00, 0xEE, 0x00},
    /* 143 PAL_HEALTH_MID    */ {0xFF, 0xA5, 0x00},
    /* 144 PAL_HEALTH_LOW    */ {0xEE, 0x00, 0x00},
    /* 145 PAL_P1_INDICATOR  */ {0x00, 0x50, 0xF8},
    /* 146 PAL_P2_INDICATOR  */ {0xF8, 0x20, 0x00},
    /* 147-254 (livres)      */
    {0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},
    {0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},
    {0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},
    {0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},
    {0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},
    {0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},
    {0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},

    /* 255 PAL_TRANSPARENT   */ {0xFF, 0x00, 0xFF},
};

void palette_load(void) {
    for (int i = 0; i < 256; i++) {
        sys_outb(0x3C8, (uint32_t)i);
        sys_outb(0x3C9, (uint32_t)(GAME_PALETTE[i][0] >> 2));
        sys_outb(0x3C9, (uint32_t)(GAME_PALETTE[i][1] >> 2));
        sys_outb(0x3C9, (uint32_t)(GAME_PALETTE[i][2] >> 2));
    }
}
