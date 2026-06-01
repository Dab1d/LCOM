#include <lcom/lcf.h>
#include "src/model/game/game.h"
//#include "mouse.h"
#include "video_gr.h"
#include "kbc.h" // caminho resolvido via -I../lab3 no Makefile; evita path absoluto hardcoded

int mouse_subscribe_int(uint8_t *bit_no);
int mouse_unsubscribe_int();
void mouse_ih(); //pq dá conflitos com o lab3

int proj_main_loop(int argc, char* argv[]) {
    // --- Subscrever interrupções ---
    uint8_t timer_bit, kbd_bit, mouse_bit;
    if (timer_set_frequency(0, 60) != 0)       return 1;
    if (timer_subscribe_int(&timer_bit) != 0)   return 1;
    if (kbc_subscribe_int(&kbd_bit) != 0)  return 1;
    if (mouse_subscribe_int(&mouse_bit) != 0)   return 1;

    uint32_t timer_irq_set    = BIT(timer_bit);
    uint32_t keyboard_irq_set = BIT(kbd_bit);
    uint32_t mouse_irq_set    = BIT(mouse_bit);

    game_init();

    int ipc_status;
    message msg;
    int r;

    while (game_get_state() != EXIT) {
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed: %d\n", r);
            continue;
        }

        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.m_notify.interrupts & timer_irq_set) {
                        timer_int_handler();
                        switch (game_get_state()) {
                            case MAIN_MENU:
                                // TODO: game_process_input() + game_render_menu()
                                break;
                            case GAMEPLAY:
                                game_update();
                                game_process_collisions();
                                if (game_is_over())
                                    game_set_state(GAME_OVER);
                                game_render();
                                break;
                            case PAUSE:
                                break;
                            case GAME_OVER:
                                // TODO: input restart/menu
                                break;
                            case EXIT:
                                break;
                        }
                    }
                    if (msg.m_notify.interrupts & keyboard_irq_set) {
                        kbc_ih();
                        game_process_input();
                    }
                    if (msg.m_notify.interrupts & mouse_irq_set)
                        mouse_ih();
                    break;
                default:
                    break;
            }
        }
    }

    timer_unsubscribe_int();
    kbc_unsubscribe_int();
    mouse_unsubscribe_int();
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
