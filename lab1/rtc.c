#include "rtc.h"
#include <minix/syslib.h>
#include <minix/sysutil.h>

#define TODO return -1

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71
#define RTC_REG_A 0x0A
#define RTC_REG_B 0x0B
#define RTC_REG_DAY 0x07
#define RTC_REG_MONTH 0x08
#define RTC_REG_YEAR 0x09
#define RTC_UIP_MSK (1 << 7)
#define RTC_DM_MSK (1 << 2)

static int bcd_to_bin(uint8_t bcd) { 
    return (bcd & 0x0F) + ((bcd >> 4) * 10);
}

static uint8_t rtc_read(uint8_t reg) {
    uint32_t value;

    sys_outb(RTC_ADDR_REG, reg);
    sys_inb(RTC_DATA_REG, &value);
    return (uint8_t)value;
}

static int is_updating() {
    uint32_t value;

    sys_outb(RTC_ADDR_REG, RTC_REG_A);
    sys_inb(RTC_DATA_REG, &value);

    return value & RTC_UIP_MSK;
}

int rtc_read_reg(uint8_t reg, uint32_t *value) {
    
    if (sys_outb(RTC_ADDR_REG, reg) != 0) {
        return 1; 
    }
    
    if (sys_inb(RTC_DATA_REG, value) != 0) {
        return 1; 
    }
    return 0; 
}

int rtc_read_date(rtc_date *date) {

    uint32_t regA, regB, day, month, year;
    int counter=0;

    // Esperar que o RTC não esteja a atualizar (UIP - Update In Progress)
    do {
        if (rtc_read_reg(RTC_REG_A, &regA) != OK) return 1;

        if (regA & RTC_UIP_MSK) {
            counter++;
            if (counter >= 50) {
                
                return 1;
            }
            tickdelay(micros_to_ticks(20000));
        }
    } while (regA & RTC_UIP_MSK);

    // Leitura dos dados (usando a auxiliar e verificando erros)
    if (rtc_read_reg(RTC_REG_DAY, &day) != 0) return 1;
    if (rtc_read_reg(RTC_REG_MONTH, &month) != 0) return 1;
    if (rtc_read_reg(RTC_REG_YEAR, &year) != 0) return 1;
    if (rtc_read_reg(RTC_REG_B, &regB) != 0) return 1;

    // Conversão de BCD para Binário, se necessário
    // Se o bit RTC_DM_MSK no Reg B for 0, os dados estão em BCD
    if (!(regB & RTC_DM_MSK)) {
        day = bcd_to_bin((uint8_t)day);
        month = bcd_to_bin((uint8_t)month);
        year = bcd_to_bin((uint8_t)year);
    }

    // Guardar na estrutura através das referências
    date->day = (uint8_t) day;
    date->month = (uint8_t) month;
    date->year = (uint8_t) year;

    return 0;

}