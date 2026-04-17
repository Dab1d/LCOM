#include <lcom/lcf.h>
#include "mouse.h"
#include <stdint.h>

static int mouse_hook_id = 2;        // hook id for subscribing
static uint8_t byte_received;        // byte read by mouse_ih
static bool byte_ready = false;      // flag: new byte available
static int byte_error = 0;           // flag: error reading byte

/* ---- mouse_ih ----
 * Interrupt handler: reads ONE byte from KBC output buffer.
 * Called every time mouse sends a byte (every interrupt).
 */
void (mouse_ih)() {
    uint8_t status;

    // Read KBC status register
    if (util_sys_inb(KBC_CMD_PORT, &status) != 0) {
        byte_error = 1;
        return;
    }

    // Check output buffer is full, no errors, and data is from mouse
    if (!(status & KBC_OBF)) {
        byte_error = 1;
        return;
    }
    if ((status & KBC_PAR_ERR) || (status & KBC_TO_ERR)) {
        byte_error = 1;
        // Still read the byte to clear the buffer
        util_sys_inb(KBC_DATA_PORT, &byte_received);
        return;
    }

    // Read the byte
    if (util_sys_inb(KBC_DATA_PORT, &byte_received) != 0) {
        byte_error = 1;
        return;
    }

    byte_error = 0;
    byte_ready = true;
}

/* ---- mouse_subscribe_int ----
 * Subscribes mouse interrupts in exclusive mode.
 * bit_no: output, the bit mask to identify mouse interrupts.
 */
int (mouse_subscribe_int)(uint8_t *bit_no) {
    if (bit_no == NULL) return 1;
    *bit_no = BIT(mouse_hook_id);
    return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
}

/* ---- mouse_unsubscribe_int ----
 * Unsubscribes mouse interrupts.
 */
int (mouse_unsubscribe_int)() {
    return sys_irqrmpolicy(&mouse_hook_id);
}

