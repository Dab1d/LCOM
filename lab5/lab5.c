#include <lcom/lcf.h>
#include <stdint.h>
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

int (video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {

    //entrar em modo gráfico
    if (vg_init(0x105) == NULL)
        return 1;

    // carregar imagem
    xpm_image_t img;
    uint8_t *pixmap = xpm_load(xpm, XPM_INDEXED, &img);

    if (pixmap == NULL)
        return 1;

    if (vg_draw_pixmap(pixmap, img, x, y) != 0)
        return 1;

    //esperar ESC (igual ao rectangle)
    int ipc_status;
    message msg;
    uint8_t bit_no;

    if (kbc_subscribe_int(&bit_no) != 0)
        return 1;

    uint32_t irq_set = BIT(bit_no);
    
    while (get_current_scancode() != 0x81) {

        if (driver_receive(ANY, &msg, &ipc_status) != 0)
            continue;

        if (is_ipc_notify(ipc_status)) {
            if (msg.m_notify.interrupts & irq_set) {
                kbc_ih();
            }
        }
    }

    kbc_unsubscribe_int();
    vg_exit();

    return 0;
}
