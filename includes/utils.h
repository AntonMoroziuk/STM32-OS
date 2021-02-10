#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <string.h>

uint32_t set_bits_with_offset(uint32_t field, unsigned int offset,
                                    unsigned int width, uint32_t value);

void   *memset(void *s, int c, size_t n);

#endif