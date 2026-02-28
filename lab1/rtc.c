#include <minix/syslib.h>
#include <minix/drivers.h>
#include "rtc.h"

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71
#define RTC_REG_A    0x0A
#define RTC_REG_B    0x0B
#define RTC_REG_DAY  0x07
#define RTC_REG_MONTH 0x08
#define RTC_REG_YEAR 0x09
#define RTC_UIP_MSK  (1 << 7) 
#define RTC_DM_MSK   (1 << 2) 


static int bcd_to_bin(uint8_t bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

int rtc_read_date(rtc_date *date) {
    uint32_t regA = 0;
    uint32_t regB = 0;
    uint32_t day, month, year;

    do {
    
        sys_outb(RTC_ADDR_REG, RTC_REG_A);
        sys_inb(RTC_DATA_REG, &regA);

        if (regA & RTC_UIP_MSK) {
            tickdelay(micros_to_ticks(20000));
        }
    } while (regA & RTC_UIP_MSK);


    
    sys_outb(RTC_ADDR_REG, RTC_REG_DAY);
    sys_inb(RTC_DATA_REG, &day);

    sys_outb(RTC_ADDR_REG, RTC_REG_MONTH);
    sys_inb(RTC_DATA_REG, &month);

    sys_outb(RTC_ADDR_REG, RTC_REG_YEAR);
    sys_inb(RTC_DATA_REG, &year);


    sys_outb(RTC_ADDR_REG, RTC_REG_B);
    sys_inb(RTC_DATA_REG, &regB);

    
    if (!(regB & RTC_DM_MSK)) {
        day = bcd_to_bin((uint8_t)day);
        month = bcd_to_bin((uint8_t)month);
        year = bcd_to_bin((uint8_t)year);
    }

    date->day = (uint8_t) day;
    date->month = (uint8_t) month;
    date->year = (uint8_t) year;

    return 0;
}