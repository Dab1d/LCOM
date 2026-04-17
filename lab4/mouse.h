#ifndef MOUSE_H
#define MOUSE_H

#include <lcom/lcf.h>
#include <stdint.h>

#define KBC_CMD_PORT   0x64
#define KBC_DATA_PORT  0x60
#define KBC_WRITE_MOUSE 0xD4

#define MOUSE_DISABLE_DR  0xF5   
#define MOUSE_ENABLE_DR   0xF4   

#define KBC_OBF    BIT(0)   
#define KBC_IBF    BIT(1)   
#define KBC_AUX    BIT(5)   
#define KBC_PAR_ERR BIT(7)  
#define KBC_TO_ERR  BIT(6)  

#define MOUSE_IRQ  12

void (mouse_ih)();
int (mouse_subscribe_int)(uint8_t *bit_no);
int (mouse_unsubscribe_int)();
int (mouse_write_command)(uint8_t cmd);
int (mouse_disable_data_reporting)();
int (mouse_test_packet)(uint32_t cnt);
int (mouse_test_async)(uint8_t idle_time);

#endif /* MOUSE_H */

