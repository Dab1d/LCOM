#include <lcom/lcf.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <machine/int86.h>
#include "video_gr.h"

char     *video_mem      = NULL;
uint16_t  h_res          = 0;
uint16_t  v_res          = 0;
uint8_t   bits_per_pixel = 0;

void *(vg_init)(uint16_t mode) {
  vbe_mode_info_t mode_info;

  if (vbe_get_mode_info(mode, &mode_info) != 0)
    return NULL;

  if (mode_info.PhysBasePtr == 0)
    return NULL;

  h_res          = mode_info.XResolution;
  v_res          = mode_info.YResolution;
  bits_per_pixel = mode_info.BitsPerPixel;

  uint32_t fb_size = (uint32_t) mode_info.BytesPerScanLine * mode_info.YResolution;

  struct minix_mem_range range;
  range.mr_base  = mode_info.PhysBasePtr;
  range.mr_limit = mode_info.PhysBasePtr + fb_size;

  if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &range) != OK)
    return NULL;

  video_mem = vm_map_phys(SELF, (void *) (uintptr_t) mode_info.PhysBasePtr, fb_size);
  if (video_mem == MAP_FAILED)
    return NULL;

  reg86_t regs;
  memset(&regs, 0, sizeof(regs));
  regs.intno = 0x10;
  regs.ax    = 0x4F02;
  regs.bx    = mode | BIT(14);

  if (sys_int86(&regs) != OK)
    return NULL;

  if (regs.ax != 0x004F)
    return NULL;

  return video_mem;
}
