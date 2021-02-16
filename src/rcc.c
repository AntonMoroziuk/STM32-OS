#include <stdint.h>

#include "rcc.h"
#include "utils.h"

void    rcc_gpio_set(IO_PORT io_port, uint8_t enable)
{
    RCC->AHBENR = set_bits_with_offset(RCC->AHBENR, io_port, 1, enable ? 1 : 0);
}

void    rcc_uart_set(UART_PORT uart_port, uint8_t enable)
{
    switch (uart_port)
    {
        case UART_PORT_1:
        case UART_PORT_6:
        case UART_PORT_7:
        case UART_PORT_8:
            RCC->APB2ENR = set_bits_with_offset(RCC->APB2ENR, uart_port, 1, enable ? 1 : 0);
            break ;
        case UART_PORT_2:
        case UART_PORT_3:
        case UART_PORT_4:
        case UART_PORT_5:
            RCC->APB1ENR = set_bits_with_offset(RCC->APB1ENR, uart_port, 1, enable ? 1 : 0);
            break ;
    }
}