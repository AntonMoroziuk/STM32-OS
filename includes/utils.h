#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <string.h>

static inline uint32_t set_bits_with_offset(uint32_t field, unsigned int offset,
                                    unsigned int width, uint32_t value)
{
    uint32_t temp;

    temp = field & ~(((1 << width) - 1) << offset);
    temp |= value << offset;

    return (temp);
}

void *memset(void *s, int c, size_t n);

size_t strlen(const char *s);

#endif
