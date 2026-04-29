#include <lcom/lcf.h>
#include "video_gr.h"
#include "kbc.h"
#include <stdint.h>

int video_test_rectangle(uint16_t mode, uint16_t x, uint16_t y,
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

    while (get_current_scancode() != 0x81) {

        if (driver_receive(ANY, &msg, &ipc_status) != 0)
            continue;

        if (is_ipc_notify(ipc_status)) {
            if (msg.m_notify.interrupts & irq_set) {
                kbc_ih();
            }
        }
    }

    if (kbc_unsubscribe_int() != 0)
        return 1;

    if (vg_exit() != 0)
        return 1;

    return 0;
}