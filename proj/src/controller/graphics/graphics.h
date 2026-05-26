#ifndef __PROJ_GRAPHICS_H
#define __PROJ_GRAPHICS_H

#include <stdint.h>

/* VBE mode 0x115: 1024x768, 24-bit direct colour */
#define GRAPHICS_MODE   0x115
#define SCREEN_WIDTH    1024
#define SCREEN_HEIGHT   768

/* ---- Common colour constants (24-bit RGB) ---- */
#define COLOR_BLACK     0x000000u
#define COLOR_WHITE     0xFFFFFFu
#define COLOR_RED       0xDD2222u
#define COLOR_GREEN     0x22CC66u
#define COLOR_BLUE      0x2255EEu
#define COLOR_YELLOW    0xFFCC00u
#define COLOR_ORANGE    0xFF6600u
#define COLOR_GRAY      0x555555u
#define COLOR_DARKGRAY  0x1A1A1Au
#define COLOR_ROAD      0x2B2B2Bu
#define COLOR_LINE      0xF0E040u

/* ---- Lifecycle ---- */
int graphics_init(void);   /* enter VBE mode */
int graphics_exit(void);   /* return to text mode */

#endif /* __PROJ_GRAPHICS_H */
