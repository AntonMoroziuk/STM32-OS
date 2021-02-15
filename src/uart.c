#include "uart.h"
#include "utils.h"
#include "gpio.h"

void    uart_configure(UART_config *config)
{
    // TODO: add all UART ports
    if (config->port == UART1)
    {
        gpio_select_alternate_function(GPIOA, GPIO_PIN_8, AF1);
        gpio_select_alternate_function(GPIOA, GPIO_PIN_9, AF1);
        gpio_select_alternate_function(GPIOA, GPIO_PIN_10, AF1);
    }

    switch (config->word_length)
    {
        case EIGHT_BITS:
            config->port->CR1 = set_bits_with_offset(config->port->CR1, M1_OFFSET, 1, 0);
            config->port->CR1 = set_bits_with_offset(config->port->CR1, M0_OFFSET, 1, 0);
            break ;
        case NINE_BITS:
            config->port->CR1 = set_bits_with_offset(config->port->CR1, M1_OFFSET, 1, 0);
            config->port->CR1 = set_bits_with_offset(config->port->CR1, M0_OFFSET, 1, 1);
            break ;
        case SEVEN_BITS:
            config->port->CR1 = set_bits_with_offset(config->port->CR1, M1_OFFSET, 1, 1);
            config->port->CR1 = set_bits_with_offset(config->port->CR1, M0_OFFSET, 1, 0);
            break ;
    }

    config->port->BRR = DEFAULT_BRR_VALUE;

    config->port->CR2 = set_bits_with_offset(config->port->CR2, STOP_OFFSET, 2, config->stop_bits);

    /* Enable UART */
    config->port->CR1 = set_bits_with_offset(config->port->CR1, UE_OFFSET, 1, 1);
}

void    uart_write(UART_t *uart, char buf[], size_t len)
{
    /* Start transmition with idle frame */
    uart->CR1 = set_bits_with_offset(uart->CR1, TE_OFFSET, 1, 1);

    for (size_t i = 0; i < len; i++)
    {
        uart->TDR = buf[i];

        /* Wait until data is transfered to the shift register */
        while (!(uart->ISR & (1 << TXE_OFFSET))) ;
    }
    /* Wait until data is sent */
    while (!(uart->ISR & (1 << TC_OFFSET))) ;
}

void    uart_read(UART_t *uart, char buf[], size_t len)
{
    /* Start transmition with idle frame */
    uart->CR1 = set_bits_with_offset(uart->CR1, RE_OFFSET, 1, 1);

    for (size_t i = 0; i < len; i++)
    {
        /* Wait until data is received */
        while (!(uart->ISR & (1 << RNXE_OFFSET))) ;

        buf[i] = uart->RDR;
    }
}
