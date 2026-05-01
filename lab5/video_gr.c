#include <lcom/lcf.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <machine/int86.h>

#include "video_gr.h"

char *video_mem = NULL;
uint16_t h_res = 0;
uint16_t v_res = 0;
uint8_t bits_per_pixel = 0;

void *(vg_init)(uint16_t mode) {
  vbe_mode_info_t info;

  if (vbe_get_mode_info(mode, &info) != 0) {
    return NULL;
  }

  if (info.PhysBasePtr == 0) {
    return NULL;
  }

  h_res = info.XResolution;
  v_res = info.YResolution;
  bits_per_pixel = info.BitsPerPixel;

  uint32_t vram_size = (uint32_t) info.BytesPerScanLine * info.YResolution;

  struct minix_mem_range mr;
  mr.mr_base = info.PhysBasePtr;
  mr.mr_limit = mr.mr_base + vram_size;

  if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr) != OK) {
    return NULL;
  }

  video_mem = vm_map_phys(SELF, (void *) (uintptr_t) info.PhysBasePtr, vram_size);
  if (video_mem == MAP_FAILED) {
    return NULL;
  }

  reg86_t r;
  memset(&r, 0, sizeof(r));
  r.intno = 0x10;
  r.ax = 0x4F02;
  r.bx = mode | BIT(14);

  if (sys_int86(&r) != OK) {
    return NULL;
  }

  if (r.ax != 0x004F) {
    return NULL;
  }

  return video_mem;
}

int vg_draw_pixel(uint16_t x, uint16_t y, uint32_t color) {
  if (video_mem == NULL || (void *) video_mem == MAP_FAILED) {
    return 1;
  }
  if (x >= h_res || y >= v_res) {
    return 1;
  }

  unsigned bpp = (unsigned) ((bits_per_pixel + 7) / 8);
  uint8_t *px = (uint8_t *) video_mem + ((uint32_t) y * h_res + x) * bpp;

  for (unsigned b = 0; b < bpp; b++, px++) {
    *px = (uint8_t) ((color >> (8 * b)) & 0xFF);
  }

  return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (uint16_t i = 0; i < len; i++) {
    if (vg_draw_pixel(x + i, y, color) != 0) {
      return 1;
    }
  }
  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y,
                        uint16_t width, uint16_t height,
                        uint32_t color) {
  for (uint16_t i = 0; i < height; i++) {
    if (vg_draw_hline(x, y + i, width, color) != 0) {
      return 1;
    }
  }
  return 0;
}

int vg_draw_pixmap(uint8_t *pixmap, xpm_image_t img, uint16_t x, uint16_t y) {
    if (pixmap == NULL || video_mem == NULL) return 1;

    for (uint16_t row = 0; row < img.height; row++) {
        for (uint16_t col = 0; col < img.width; col++) {
            uint32_t color = pixmap[row * img.width + col];
            if (vg_draw_pixel(x + col, y + row, color) != 0)
                return 1;
        }
    }
    return 0;
}

