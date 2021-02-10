#include <stdint.h>
#include <string.h>

uint32_t set_bits_with_offset(uint32_t field, unsigned int offset,
                                    unsigned int width, uint32_t value)
{
    uint32_t temp;

    temp = field & ~((1 << width) - 1);
    temp |= value << offset;

    return (temp);
}

void   *memset(void *s, int c, size_t n)
{
    for (size_t i = 0; i < n; i++)
        ((unsigned char*)s)[i] = (unsigned char)c;
    return (s);
}