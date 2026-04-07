#include <lcom/lcf.h>
#include <lcom/timer.h>
#include <stdint.h>
#include <lcom/utils.h>

#include "i8254.h"

int timecounter;
int hook_id=0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  if (freq == 0 || freq > TIMER_FREQ) return 1;
  uint8_t st;
  uint8_t c=TIMER_RB_CMD|TIMER_RB_COUNT_| TIMER_RB_SEL(timer);
  sys_outb(TIMER_CTRL,c);
  util_sys_inb(TIMER_0+timer,&st);
  uint8_t lsbofst= st & 0x0F;
  uint8_t sel;
  if (timer==0) sel=TIMER_SEL0;
  else if (timer==1) sel = TIMER_SEL1;
  else if (timer==2) sel = TIMER_SEL2;
  else return 1;
  uint8_t controlword= sel | (1<<5) | 1<<4 | lsbofst;
  sys_outb(TIMER_CTRL, controlword);
  uint16_t div = TIMER_FREQ / freq;
  uint8_t lsb = div & 0xFF;
  uint8_t msb = div >> 8;
  sys_outb(TIMER_0 + timer, lsb);
  sys_outb(TIMER_0 + timer, msb);

  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
   if (bit_no == NULL) return 1;

  *bit_no = hook_id;

  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != OK)
    return 1;

  return 0;

}

int (timer_unsubscribe_int)() {
   if (sys_irqrmpolicy(&hook_id) != OK)
    return 1;

  return 0;
}

void (timer_int_handler)() {
  timecounter++;
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

   else if (field == tsf_base) {
    conf.bcd = st & BIT(0);
  }

  
  return 0;
}
