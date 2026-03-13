#include "bitwise.h"
#include <stdarg.h>

uint8_t clear(uint8_t msk, int pos) {
    if (pos < 0 || pos > 7) return msk;
    return msk & ~(1 << pos);
}

uint8_t set(uint8_t msk, int pos) {
    if (pos < 0 || pos > 7) return msk;
    return msk | (1 << pos);
}

bool is_set(uint8_t msk, int pos) {
    if (pos < 0 || pos > 7) return false;
    return (msk & (1 << pos)) != 0;
}

uint8_t lsb(uint16_t wide_msk) {
    return (uint8_t)(wide_msk & 0xFF);
}

uint8_t msb(uint16_t wide_msk) {
    return (uint8_t)((wide_msk >> 8) & 0xFF);
}

uint8_t mask(int pos, ...) {
    uint8_t res = 0;
    if (pos == MSK_END) return 0;

    va_list ap;
    va_start(ap, pos);
    int current_pos = pos;
    while (current_pos != MSK_END) {
        if (current_pos >= 0 && current_pos <= 7) {
            res |= (1 << current_pos);
        }
        current_pos = va_arg(ap, int);
    }
    va_end(ap);
    return res;
}