#include <lcom/lcf.h>
#include <stdio.h>
#include <string.h>
#include "video_gr.h"

static uint8_t *video_mem = NULL;
static vbe_mode_info_t vmi;
static uint8_t bytes_per_pixel;

int vg_set_mode(uint16_t mode) {
    // Ask the BIOS to enter the VBE graphics mode using linear framebuffer.
    reg86_t reg;
    memset(&reg, 0, sizeof(reg));
    reg.intno = 0x10;
    reg.ax = 0x4F02;
    reg.bx = mode | BIT(14);
    if (sys_int86(&reg) != OK) return 1;
    if (reg.ax != 0x004F) return 1;
    return 0;
}

void *(vg_init)(uint16_t mode) {
    // Save the mode information first, because the drawing functions need it.
    if (vbe_get_mode_info(mode, &vmi) != 0) {
        printf("vg_init: failed to get mode info.\n");
        return NULL;
    }

    bytes_per_pixel = (vmi.BitsPerPixel + 7) / 8;
    unsigned int vram_size = (unsigned int)vmi.YResolution * vmi.BytesPerScanLine;
    phys_bytes vram_base = (phys_bytes)vmi.PhysBasePtr;

    // Allow this process to access the physical VRAM range.
    struct minix_mem_range mr;
    mr.mr_base = vram_base;
    mr.mr_limit = vram_base + vram_size;
    if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr) != OK) {
        printf("vg_init: failed to add VRAM memory permission.\n");
        return NULL;
    }

    // Map the physical video memory so the program can write pixels directly.
    video_mem = vm_map_phys(SELF, (void *)vram_base, vram_size);
    if (video_mem == MAP_FAILED || video_mem == NULL) {
        printf("vg_init: failed to map VRAM.\n");
        return NULL;
    }

    if (vg_set_mode(mode) != 0) {
        printf("vg_init: failed to set graphics mode.\n");
        return NULL;
    }

    return video_mem;
}

int vg_draw_pixel(uint16_t x, uint16_t y, uint32_t color) {
    // Do not draw outside the screen limits.
    if (x >= vmi.XResolution || y >= vmi.YResolution) return 1;

    // Position of the pixel inside the linear framebuffer.
    uint8_t *pixel = video_mem + (uint32_t)y * vmi.BytesPerScanLine + (uint32_t)x * bytes_per_pixel;
    memcpy(pixel, &color, bytes_per_pixel);
    return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
    for (uint16_t i = 0; i < len; i++) {
        if (vg_draw_pixel(x + i, y, color) != 0) return 1;
    }
    return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    // A rectangle is drawn as several horizontal lines.
    for (uint16_t row = 0; row < height; row++) {
        if (vg_draw_hline(x, y + row, width, color) != 0) return 1;
    }
    return 0;
}

int vg_draw_pixmap(xpm_image_t *img, uint16_t x, uint16_t y) {
    if (img == NULL || img->bytes == NULL) return 1;

    // The XPM image stores the pixels in a byte array.
    uint8_t img_bpp = img->size / ((uint32_t)img->width * img->height);
    for (uint16_t row = 0; row < img->height; row++) {
        for (uint16_t col = 0; col < img->width; col++) {
            uint32_t color = 0;
            memcpy(&color, img->bytes + ((uint32_t)row * img->width + col) * img_bpp, img_bpp);
            if (vg_draw_pixel(x + col, y + row, color) != 0) return 1;
        }
    }
    return 0;
}
