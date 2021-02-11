#include <stdint.h>

#include "rcc.h"
#include "utils.h"

void    rcc_io_set(IO_PORT io_port, uint8_t enable)
{
    RCC->AHBENR = set_bits_with_offset(RCC->AHBENR, io_port, 1, enable ? 1 : 0);
}
