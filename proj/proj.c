#include <lcom/lcf.h>
#include "src/model/game/game.h"



int proj_main_loop(int argc, char* argv[]) {
    uint8_t bit_no;
    if (timer_set_frequency(0, 60) != 0) return 1;
    if (timer_subscribe_int(&bit_no) != 0) return 1;
    uint32_t irq_set = BIT(bit_no);

    game_init();

    int ipc_status;
    message msg;
    int r;

    while (game_get_state() != EXIT) {//como frequencia esta a 60 recebemos 60 interrupts por segundo (60hz)
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed: %d\n", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.m_notify.interrupts & irq_set) {
                        timer_int_handler(); //aumentamos o counter aqui caso seja preciso contar tempo para mais algo 
                        switch (game_get_state()) {
                            case MAIN_MENU:
                                if (input_menu_start_pressed())
                                    game_set_state(GAMEPLAY);
                                break;
                            case GAMEPLAY:
                                draw_clear(0x333333);  // limpa o ecrã
                                draw_car(car1);   // jogador 1
                                draw_car(car2);    // jogador 2
                                draw_obstacle(obs);     //desenha os obstaculos
                                if (game_check_collision())
                                    game_set_state(GAME_OVER);
                                break;
                            case PAUSE:
                                break;
                            case GAME_OVER:
                                if (input_gameover_restart_pressed())
                                    game_set_state(GAMEPLAY);
                                else if (input_gameover_menu_pressed())
                                    game_set_state(MAIN_MENU);
                                break;
                            case EXIT:
                                break;
                        }
                    }
                    //keyboard - player 1
                    if (msg.m_notify.interrupts & keyboard_irq_set) {
                        keyboard_int_handler(); // atualiza estado interno do teclado
                    }
                    //mouse - player 2
                    if (msg.m_notify.interrupts & mouse_irq_set) {
                        mouse_int_handler(); // atualiza estado interno do rato
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if (timer_unsubscribe_int() != 0) return 1;
    return 0;
}

int main(int argc, char *argv[]) {
    // sets the language of LCF messages (can be either EN-US or PT-PT)
    lcf_set_language("EN-US");

    // enables to log function invocations that are being "wrapped" by LCF
    // [comment this out if you don't want/need it]
    lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

    // enables to save the output of printf function calls on a file
    // [comment this out if you don't want/need it]
    lcf_log_output("/home/lcom/labs/proj/output.txt");

    // handles control over to LCF
    // [LCF handles command line arguments and invokes the right function]
    if (lcf_start(argc, argv))
        return 1;

    // LCF clean up tasks
    // [must be the last statement before return]
    lcf_cleanup();

    return 0;
}

