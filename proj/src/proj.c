#include <lcom/lcf.h>
#include "model/game/game.h"
#include "view/view.h"
#include "controller/input/input.h"
#include "controller/palette/palette.h"
//#include "mouse.h"
#include "video_gr.h"
#include "kbc.h" // caminho resolvido via -I../lab3 no Makefile; evita path absoluto hardcoded

#define VIDEO_MODE 0x105 // 1024x768 8-bit indexed color

int mouse_subscribe_int(uint8_t *bit_no);

int mouse_unsubscribe_int();

void mouse_ih(); //pq dá conflitos com o lab3

int proj_main_loop(int argc, char *argv[]) {
    uint8_t timer_bit, kbd_bit, mouse_bit;
    if (timer_set_frequency(0, 60) != 0) return 1;
    if (timer_subscribe_int(&timer_bit) != 0) return 1;
    if (kbc_subscribe_int(&kbd_bit) != 0) return 1;
    if (mouse_subscribe_int(&mouse_bit) != 0) return 1;

    uint32_t timer_irq_set = BIT(timer_bit);
    uint32_t keyboard_irq_set = BIT(kbd_bit);
    uint32_t mouse_irq_set = BIT(mouse_bit);

    if (vg_init(VIDEO_MODE) == NULL) return 1;
    palette_load();
    view_init_buffers();
    game_init();

    int ipc_status;
    message msg;
    int r;

    while (game_get_state() != EXIT) {
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed: %d\n", r);
            continue;
        }
        if (!is_ipc_notify(ipc_status)) continue;

        switch (msg.m_source) {
            case HARDWARE:
                if (msg.m_notify.interrupts & timer_irq_set) {
                    timer_int_handler();
                    game_tick();
                }
                if (msg.m_notify.interrupts & keyboard_irq_set) {
                    kbc_ih();
                    input_update();
                }
                if (msg.m_notify.interrupts & mouse_irq_set)
                    mouse_ih();
                break;
        }
    }

    timer_unsubscribe_int();
    kbc_unsubscribe_int();
    mouse_unsubscribe_int();
    vg_exit();
    return 0;
}

int main(int argc, char *argv[]) {
    lcf_set_language("EN-US");
    lcf_trace_calls("/home/lcom/labs/proj/trace.txt");
    lcf_log_output("/home/lcom/labs/proj/output.txt");
    if (lcf_start(argc, argv)) return 1;
    lcf_cleanup();
    return 0;
}
