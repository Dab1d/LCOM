#ifndef VIDEO_GR_H
#define VIDEO_GR_H

#include <lcom/lcf.h>
#include <stdint.h>

#ifdef vg_init
#undef vg_init
#endif
#ifdef vg_draw_hline
#undef vg_draw_hline
#endif
#ifdef vg_draw_rectangle
#undef vg_draw_rectangle
#endif

/* globals filled by vg_init()*/
extern char     *video_mem;
extern uint16_t  h_res;
extern uint16_t  v_res;
extern uint8_t   bits_per_pixel;

int vg_draw_pixel(uint16_t x, uint16_t y, uint32_t color);

int vg_draw_hline(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int vg_draw_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);



#endif
