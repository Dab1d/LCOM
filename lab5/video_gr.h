#ifndef VIDEO_GR_H
#define VIDEO_GR_H

#include <lcom/lcf.h>
#include <stdint.h>

#ifdef vg_init
#undef vg_init
#endif

/* globals filled by vg_init() */
extern char     *video_mem;
extern uint16_t  h_res;
extern uint16_t  v_res;
extern uint8_t   bits_per_pixel;

#endif
