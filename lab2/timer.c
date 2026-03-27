#include <lcom/lcf.h>
#include <lcom/timer.h>
#include "utils.c"
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
  uint8_t c=TIMER_RB_CMD|TIMER_RB_COUNT_| TIMER_RB_SEL(timer);
  sys_outb(TIMER_CTRL,c);
  util_sys_inb(TIMER_0+timer,st);
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  /* To be implemented by the students */
  union timer_status_field_val conf;
  if (field==tsf_all){
    conf.byte=st;
    timer_print_config(timer, field, conf);
  }
  else if (field==tsf_initial){
    uint8_t a = BIT(4);
    uint8_t b = BIT(5);
    if ((a&st) && !(b&st)){
      conf.in_mode=LSB_only;
    }
    else if (!(a&st) && (b&st)){
      conf.in_mode=MSB_only;
    }
    else if ((a&st) && (b&st)){
      conf.in_mode=MSB_after_LSB;
    }
    timer_print_config(timer, field, conf);
  }

  else if (field==tsf_mode){
    uint8_t mode = (st >> 1) & 0x07;

    if (mode == 6) mode = 2;
    if (mode == 7) mode = 3;

    conf.count_mode = mode;

    timer_print_config(timer, field, conf);

  }
  
  return 1;
}
