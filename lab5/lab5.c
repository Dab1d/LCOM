#include <lcom/lcf.h>
#include <stdint.h>
#include "video_gr.h"
#include "kbc.h"
#undef video_test_rectangle
#undef video_test_init

int main(int argc, char *argv[]) {
    lcf_set_language("EN-US");
    lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");
    lcf_log_output("/home/lcom/labs/lab5/output.txt");

    if (lcf_start(argc, argv))
        return 1;

    lcf_cleanup();
    return 0;
}

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
            if (msg.m_notify.interrupts & BIT(irq_set)) {
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
