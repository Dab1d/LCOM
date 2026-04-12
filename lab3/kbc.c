#include <lcom/lcf.h>
#include <stdint.h>
#include "kbc.h"

int hook_id=1;
bool kbc_error=0;
static uint8_t current_scancode = 0;
int (kbc_subscribe_int)(uint8_t *bit_no) {
   if (bit_no == NULL) return 1;

  *bit_no = hook_id;

  if (sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE|IRQ_EXCLUSIVE, &hook_id) != OK)
    return 1;

  return 0;

}
int kbc_unsubscribe_int() {
    if (sys_irqrmpolicy(&hook_id) != OK) return 1; // remover interrupções
    return 0;
}

void (kbc_ih)() {
    uint8_t status;
    kbc_error= false;

    // ler status register
    if (util_sys_inb(KBC_STATUS_REG, &status) != OK) {
        kbc_error= true;
        return;
    }

    // ler output buffer
    if (util_sys_inb(KBC_OUTBUF_REG, &current_scancode) != OK) {
        kbc_error = true;
        return;
    }

    // errors
    if (status & (KBC_PARITY | KBC_TIMEOUT)) {
        kbc_error = true;
    }
}
int kbc_read_outbuf(uint8_t *byte){

}