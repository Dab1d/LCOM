#include <lcom/lcf.h>
#include <stdint.h>
#include <string.h>
#include "video_gr.h"
#include "kbc.h"


int main(int argc, char *argv[]) {
    lcf_set_language("EN-US");
    lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");
    lcf_log_output("/home/lcom/labs/lab5/output.txt");

    if (lcf_start(argc, argv))
        return 1;

    lcf_cleanup();
    return 0;
}

int (video_test_init)(uint16_t mode, uint8_t delay) {
    // Usa o vg_init que tu próprio escreveste! 
    // Ele já faz o sys_int86, o mapeamento de memória e preenche as globais.
    if (vg_init(mode) == NULL) {
        return 1;
    }

    // O LCF exige que esperes 'delay' segundos antes de sair
    tickdelay(micros_to_ticks(delay * 1000000));

    // Volta ao modo texto
    if (vg_exit() != 0) {
        return 1;
    }

    return 0;
}

int (video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                         uint16_t width, uint16_t height,
                         uint32_t color) {

    if (vg_init(mode) == NULL)
        return 1;

    if (vg_draw_rectangle(x, y, width, height, color) != 0)
        return 1;

    int ipc_status;
    message msg;

    uint8_t irq_set;

    if (kbc_subscribe_int(&irq_set) != 0)
        return 1;

   bool done = false;
    while (!done) {
        if (driver_receive(ANY, &msg, &ipc_status) != 0)
            continue;

        if (is_ipc_notify(ipc_status)) {
            if (msg.m_notify.interrupts & BIT(irq_set)) {
                kbc_ih();
                if (get_current_scancode() == ESC_BREAKCODE)
                    done = true;
            }
        }
    }

    if (kbc_unsubscribe_int() != 0)
        return 1;

    if (vg_exit() != 0)
        return 1;

    return 0;
}

int (video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {

    if (vg_init(0x105) == NULL) {
        printf("vg_init failed\n");
        return 1;
    }

    xpm_image_t img;
    uint8_t *pixmap = xpm_load(xpm, XPM_INDEXED, &img);
    if (pixmap == NULL) {
        printf("xpm_load failed\n");
        return 1;
    }

    if (vg_draw_pixmap(pixmap, img, x, y) != 0) {
        printf("vg_draw_pixmap failed\n");
        return 1;
    }

    int ipc_status;
    message msg;
    uint8_t bit_no;

    if (kbc_subscribe_int(&bit_no) != 0) {
        printf("kbc_subscribe_int failed\n");
        return 1;
    }

    uint32_t irq_set = BIT(bit_no);
    bool done = false;

    while (!done) {
        if (driver_receive(ANY, &msg, &ipc_status) != 0)
            continue;

        if (is_ipc_notify(ipc_status)) {
            if (msg.m_notify.interrupts & irq_set) {
                kbc_ih();
                if (get_current_scancode() == ESC_BREAKCODE)
                    done = true;
            }
        }
    }

    kbc_unsubscribe_int();
    vg_exit();

    return 0;
}
