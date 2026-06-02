#ifndef RTC_H
#define RTC_H

#include <stdint.h>

// Endereços dos registos do RTC
#define RTC_ADDR_REG  0x70   // porta onde se escreve o nº do registo a ler
#define RTC_DATA_REG  0x71   // porta onde se lê o valor do registo

#define RTC_REG_A     0x0A   // registo de estado A (contém o flag UIP)
#define RTC_REG_B     0x0B   // registo de estado B (contém o modo BCD/binário)

#define RTC_REG_SEC   0x00
#define RTC_REG_MIN   0x02
#define RTC_REG_HOUR  0x04
#define RTC_REG_DAY   0x07
#define RTC_REG_MONTH 0x08
#define RTC_REG_YEAR  0x09

#define RTC_UIP_MSK   (1 << 7)  // Update In Progress — se estiver a 1, não ler
#define RTC_DM_MSK    (1 << 2)  // Data Mode — 0 = BCD, 1 = binário

typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} rtc_time;

typedef struct {
    uint8_t day;
    uint8_t month;
    uint8_t year;
} rtc_date;

// Lê a data atual do RTC (dia, mês, ano)
int rtc_read_date(rtc_date *date);

// Lê a hora atual do RTC (hora, minutos, segundos)
int rtc_read_time(rtc_time *time);

#endif /* RTC_H */
