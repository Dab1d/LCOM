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

int rtc_read_date(rtc_date *date) {
    while(is_updating());

    uint8_t day = rtc_read(RTC_REG_DAY);
    uint8_t month = rtc_read(RTC_REG_MONTH);
    uint8_t year = rtc_read(RTC_REG_YEAR);

    uint8_t regB = rtc_read(RTC_REG_B);

    if (!(regB & 0x04)) {
        day   = bcd_to_bin(day);
        month = bcd_to_bin(month);
        year  = bcd_to_bin(year);
    }

    date->day = day;
    date->month = month;
    date->year = year;

    return 0;
}