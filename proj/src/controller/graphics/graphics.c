#include <lcom/lcf.h>
#include "graphics.h"
#include "video_gr.h"   /* found via -I../lab5 in the Makefile */

int graphics_init(void) {
    if (vg_init(GRAPHICS_MODE) == NULL) {
        printf("graphics_init: vg_init failed for mode 0x%x\n", GRAPHICS_MODE);
        return 1;
    }
    return 0;
}

int graphics_exit(void) {
    return vg_exit();
}
