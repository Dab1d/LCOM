// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>
#include "video_gr.h"
#include "kbc.h"
// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
    // sets the language of LCF messages (can be either EN-US or PT-PT)
    lcf_set_language("EN-US");

    // enables to log function invocations that are being "wrapped" by LCF
    // [comment this out if you don't want/need it]
    lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

    // enables to save the output of printf function calls on a file
    // [comment this out if you don't want/need it]
    lcf_log_output("/home/lcom/labs/lab5/output.txt");

    // handles control over to LCF
    // [LCF handles command line arguments and invokes the right function]
    if (lcf_start(argc, argv))
        return 1;

    // LCF clean up tasks
    // [must be the last statement before return]
    lcf_cleanup();

    return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
     if (vg_init(mode) == NULL)
        return 1;

    tickdelay(micros_to_ticks((uint32_t) delay * 1000000));

    if (vg_exit() != 0)
        return 1;

    return 0;
}


int (video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                           uint16_t width, uint16_t height, uint32_t color) {
    if (vg_init(mode) == NULL)
        return 1;

    if (vg_draw_rectangle(x, y, width, height, color) != 0) {
        vg_exit();
        return 1;
    }

    uint8_t kbd_bit;
    if (kbc_subscribe_int(&kbd_bit) != 0) {
        vg_exit();
        return 1;
    }

    const uint32_t kbd_irq = BIT(kbd_bit);
    int ipc_status;
    message msg;
    bool keep_running = true;

    while (keep_running) {
        if (driver_receive(ANY, &msg, &ipc_status) != 0)
            continue;

        if (!is_ipc_notify(ipc_status))
            continue;

        if (msg.m_notify.interrupts & kbd_irq) {
            kbc_ih();
            if (get_current_scancode() == ESC_BREAKCODE)
                keep_running = false;
        }
    }

    if (kbc_unsubscribe_int() != 0) {
        vg_exit();
        return 1;
    }

    return vg_exit();
}

int (video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
    if (vg_init(0x105) == NULL)
        return 1;

    xpm_image_t img_info;
    uint8_t *sprite = xpm_load(xpm, XPM_INDEXED, &img_info);
    if (sprite == NULL) {
        vg_exit();
        return 1;
    }

    if (vg_draw_pixmap(sprite, img_info, x, y) != 0) {
        vg_exit();
        return 1;
    }

    uint8_t kbd_bit;
    if (kbc_subscribe_int(&kbd_bit) != 0) {
        vg_exit();
        return 1;
    }

    const uint32_t kbd_irq = BIT(kbd_bit);
    int ipc_status;
    message msg;
    bool keep_running = true;

    while (keep_running) {
        if (driver_receive(ANY, &msg, &ipc_status) != 0)
            continue;

        if (!is_ipc_notify(ipc_status))
            continue;

        if (msg.m_notify.interrupts & kbd_irq) {
            kbc_ih();
            if (get_current_scancode() == ESC_BREAKCODE)
                keep_running = false;
        }
    }

    if (kbc_unsubscribe_int() != 0) {
        vg_exit();
        return 1;
    }

    return vg_exit();
}
