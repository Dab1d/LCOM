#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if (timer > 2) return 1;

    // read-back command: bit7=1, bit6=1, bit5=0 (latch status),
    // bits 3-1 selecionam o timer
    uint8_t cmd = TIMER_RB_CMD          // 0xC0
                | TIMER_RB_COUNT_       // não latch count (bit5=1 -> desativar)
                | TIMER_RB_SEL(timer);  // seleciona o timer
    if (sys_outb(TIMER_CTRL, cmd) != 0) return 1;
    // lê o status byte da porta do timr selecionado
    uint8_t port;
    if      (timer == 0) port = TIMER_0;
    else if (timer == 1) port = TIMER_1;
    else                 port = TIMER_2;

    return util_sys_inb(port, st);
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
