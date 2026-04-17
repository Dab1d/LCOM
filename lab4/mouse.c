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

/* ---- kbc_wait_input ----
 * Waits until KBC input buffer is empty (safe to write).
 */
static int kbc_wait_input() {
    uint8_t status;
    int tries = 10;
    while (tries--) {
        if (util_sys_inb(KBC_CMD_PORT, &status) != 0) return 1;
        if (!(status & KBC_IBF)) return 0;   // input buffer empty, safe to write
        tickdelay(micros_to_ticks(20000));    // wait 20ms
    }
    return 1; // timed out
}

/* ---- write_to_mouse ----
 * Sends one command byte to the mouse.
 * Handles retries on 0xFE (resend) responses.
 */
int (write_to_mouse)(uint8_t cmd) {
    uint8_t ack;
    int retries = 5;

    while (retries--) {
        // Step 1: tell KBC to forward next byte to mouse
        if (kbc_wait_input() != 0) return 1;
        if (sys_outb(KBC_CMD_PORT, KBC_WRITE_MOUSE) != 0) return 1;

        // Step 2: write the actual command
        if (kbc_wait_input() != 0) return 1;
        if (sys_outb(KBC_DATA_PORT, cmd) != 0) return 1;

        // Step 3: read acknowledgment
        // Wait a bit for mouse to respond
        tickdelay(micros_to_ticks(20000));

        uint8_t status;
        int tries = 10;
        bool got_ack = false;
        while (tries--) {
            if (util_sys_inb(KBC_CMD_PORT, &status) != 0) continue;
            if (status & KBC_OBF) {
                util_sys_inb(KBC_DATA_PORT, &ack);
                got_ack = true;
                break;
            }
            tickdelay(micros_to_ticks(20000));
        }

        if (!got_ack) return 1;
        if (ack == 0xFA) return 0;       // success
        if (ack == 0xFE || ack == 0xFC)  // error: retry whole command
            continue;
    }
    return 1; // failed after retries
}

/* ---- mouse_disable_data_reporting ----
 * Sends 0xF5 to mouse to disable data reporting.
 */
int (mouse_disable_data_reporting)() {
    return write_to_mouse(MOUSE_DISABLE_DR);
}


/* ---- parse_packet ----
 * Takes 3 raw bytes and fills a struct packet.
 */
static void parse_packet(uint8_t bytes[3], struct packet *pp) {
    pp->bytes[0] = bytes[0];
    pp->bytes[1] = bytes[1];
    pp->bytes[2] = bytes[2];

    // Button states
    pp->lb = bytes[0] & BIT(0);           // left button
    pp->rb = bytes[0] & BIT(1);           // right button
    pp->mb = bytes[0] & BIT(2);           // middle button

    // X and Y movement (two's complement with sign bit from byte 1)
    pp->delta_x = bytes[1];
    pp->delta_y = bytes[2];

    if (bytes[0] & BIT(4))                // X sign bit
        pp->delta_x |= 0xFF00;            // sign extend to 16 bits

    if (bytes[0] & BIT(5))                // Y sign bit
        pp->delta_y |= 0xFF00;

    // Overflow flags
    pp->x_ov = bytes[0] & BIT(6);
    pp->y_ov = bytes[0] & BIT(7);
}

/* ---- mouse_test_packet ----
 esta funçao vinha no lab4.c mas implementei-a antes aqui*/
int (mouse_test_packet)(uint32_t cnt) {
    uint8_t mouse_mask;

    // 1. Subscribe mouse interrupts
    if (mouse_subscribe_int(&mouse_mask) != 0) return 1;

    // 2. Enable data reporting (provided by LCF)
    if (mouse_enable_data_reporting() != 0) {
        mouse_unsubscribe_int();
        return 1;
    }

    // 3. Event loop
    int ipc_status;
    message msg;
    uint32_t packets_read = 0;

    uint8_t packet_bytes[3];  // assembles one packet
    int byte_index = 0;       // which byte we're waiting for (0, 1, 2)

    while (packets_read < cnt) {
        if (driver_receive(ANY, &msg, &ipc_status) != 0) continue;

        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.m_notify.interrupts & mouse_mask) {
                        byte_ready = false;
                        mouse_ih();

                        if (byte_error || !byte_ready) break;

                        // Sync: byte 0 must have bit 3 set
                        if (byte_index == 0 && !(byte_received & BIT(3))) {
                            break; // discard, wait for valid first byte
                        }

                        packet_bytes[byte_index++] = byte_received;

                        if (byte_index == 3) {
                            // Full packet received
                            struct packet pp;
                            parse_packet(packet_bytes, &pp);
                            mouse_print_packet(&pp);
                            packets_read++;
                            byte_index = 0;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }

    // 4. Cleanup
    mouse_disable_data_reporting();
    mouse_unsubscribe_int();

    return 0;
}

