#include "video_gr.h"
#include <lcom/lcf.h>
#include <stdint.h>


static char *video_mem;
static vbe_mode_info_t vmi;
static unsigned bytes_per_pixel;

int video_test_init(uint16_t mode, uint8_t delay) {

    struct reg86 r;

    memset(&r, 0, sizeof(r));

    r.intno = 0x10;
    r.ax = 0x4F02;          //VBE set mode
    r.bx = mode | BIT(14);  //enable linear framebuffer

    if (sys_int86(&r) != OK) {
        printf("Error: sys_int86 failed\n");
        return 1;
    }

    tickdelay(micros_to_ticks(delay * 1000000));

    if (vg_exit() != OK) {
        printf("Error: vg_exit failed\n");
        return 1;
    }
    return 0;
}

int vg_draw_pixel(uint16_t x, uint16_t y, uint32_t color) {

    /* verifica boundaries para evitar crashes */
    if (x >= vmi.XResolution || y >= vmi.YResolution) {
        return 1;
    }

    /*calcular vram offset */
    unsigned int offset = (y * vmi.XResolution + x) * bytes_per_pixel;

    /* colocar a cor no pixel */
    memcpy(&video_mem[offset], &color, bytes_per_pixel);

    return 0;
}

int vg_draw_hline(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {

    for (uint16_t i = 0; i < len; i++) {

        if (vg_draw_pixel(x + i, y, color) != 0) {
            return 1;
        }
    }

    return 0;
}
