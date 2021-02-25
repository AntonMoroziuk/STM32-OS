#include "uart.h"
#include "utils.h"
#include "gpio.h"

/* CR1 register bit offsets */
#define UE_OFFSET       (0)
#define RE_OFFSET       (2)
#define TE_OFFSET       (3)
#define M0_OFFSET       (12)
#define M1_OFFSET       (28)

/* CR2 register bit offsets */
#define STOP_OFFSET     (12)

/* ISR register bit offsets */
#define RNXE_OFFSET     (5)
#define TC_OFFSET       (6)
#define TXE_OFFSET      (7)

void    uart_configure(UART_t *uart, UART_config *config)
{
    // TODO: add all UART ports
    if (uart == UART1)
    {
        gpio_select_alternate_function(GPIOA, GPIO_PIN_8, AF1);
        gpio_select_alternate_function(GPIOA, GPIO_PIN_9, AF1);
        gpio_select_alternate_function(GPIOA, GPIO_PIN_10, AF1);
    }
    else if (uart == UART2)
    {
        gpio_select_alternate_function(GPIOA, GPIO_PIN_2, AF1);
        gpio_select_alternate_function(GPIOA, GPIO_PIN_3, AF1);
        gpio_select_alternate_function(GPIOA, GPIO_PIN_4, AF1);
    }

    /* Disable UART */
    uart->CR1 = set_bits_with_offset(uart->CR1, UE_OFFSET, 1, 0);

    switch (config->word_length)
    {
        case EIGHT_BITS:
            uart->CR1 = set_bits_with_offset(uart->CR1, M1_OFFSET, 1, 0);
            uart->CR1 = set_bits_with_offset(uart->CR1, M0_OFFSET, 1, 0);
            break ;
        case NINE_BITS:
            uart->CR1 = set_bits_with_offset(uart->CR1, M1_OFFSET, 1, 0);
            uart->CR1 = set_bits_with_offset(uart->CR1, M0_OFFSET, 1, 1);
            break ;
        case SEVEN_BITS:
            uart->CR1 = set_bits_with_offset(uart->CR1, M1_OFFSET, 1, 1);
            uart->CR1 = set_bits_with_offset(uart->CR1, M0_OFFSET, 1, 0);
            break ;
    }

    uart->BRR = DEFAULT_BRR_VALUE;

    uart->CR2 = set_bits_with_offset(uart->CR2, STOP_OFFSET, 2, config->stop_bits);

    /* Enable both receive and transmit */
    uart->CR1 = set_bits_with_offset(uart->CR1, RE_OFFSET, 1, 1);
    uart->CR1 = set_bits_with_offset(uart->CR1, TE_OFFSET, 1, 1);

    /* Enable UART */
    uart->CR1 = set_bits_with_offset(uart->CR1, UE_OFFSET, 1, 1);
}

void    uart_write(UART_t *uart, const char buf[], size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        /* Wait until data is transfered to the shift register */
        while (!(uart->ISR & (1 << TXE_OFFSET))) ;

        uart->TDR = buf[i];
    }
    /* Wait until data is sent */
    while (!(uart->ISR & (1 << TC_OFFSET))) ;
}

void    uart_read(UART_t *uart, char buf[], size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        /* Wait until data is received */
        while (!(uart->ISR & (1 << RNXE_OFFSET))) ;

        buf[i] = uart->RDR;
    }
}
