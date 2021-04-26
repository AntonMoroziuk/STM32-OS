#include <stdint.h>

#include "rcc.h"
#include "utils.h"

/* CR register bit offsets */
#define HSION_OFFSET    (0)
#define HSITRIM_OFFSET  (3)

/* CFGR register bit offsets */
#define HPRE_OFFSET     (4)
#define PPRE_OFFSET     (8)

/* CFGR3 register bit offsets */
#define USART2SW_OFFSET (16)

void rcc_init_clocks(void)
{
    /* Lower HSI frequency */
    RCC->CR = set_bits_with_offset(RCC->CR, HSITRIM_OFFSET, 5, 10);

    /* Enable HSI oscillator */
    RCC->CR = set_bits_with_offset(RCC->CR, HSION_OFFSET, 1, 1);

    /* Set PCLK and HCLK prescaler values */
    RCC->CFGR = set_bits_with_offset(RCC->CFGR, PPRE_OFFSET, 3, 7);
    RCC->CFGR = set_bits_with_offset(RCC->CFGR, HPRE_OFFSET, 4, 0);

    /* Set PCLK as USART2 clock */
    RCC->CFGR3 = set_bits_with_offset(RCC->CFGR3, 16, 2, 0);
}

void rcc_gpio_set(IO_PORT io_port, uint8_t enable)
{
    RCC->AHBENR = set_bits_with_offset(RCC->AHBENR, io_port, 1, enable ? 1 : 0);
}

void rcc_uart_set(UART_PORT uart_port, uint8_t enable)
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
