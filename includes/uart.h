#ifndef UART_H
#define UART_H

#include <unistd.h>

typedef struct  UART_s
{
    volatile uint32_t    CR1;   /* Control register 1,                  Address offset 0x00 */
    volatile uint32_t    CR2;   /* Control register 2,                  Address offset 0x04 */
    volatile uint32_t    CR3;   /* Control register 3,                  Address offset 0x08 */
    volatile uint32_t    BRR;   /* Baud rate register,                  Address offset 0x0c */
    volatile uint32_t    GTPR;  /* Guard time and prescaler register,   Address offset 0x10 */
    volatile uint32_t    RTOR;  /* Receiver timeout register,           Address offset 0x14 */
    volatile uint32_t    RQR;   /* Request register,                    Address offset 0x18 */
    volatile uint32_t    ISR;   /* Interrupt and status register,       Address offset 0x1c */
    volatile uint32_t    ICR;   /* Interrupt flag clear register,       Address offset 0x20 */
    volatile uint32_t    RDR;   /* Receive data register,               Address offset 0x24 */
    volatile uint32_t    TDR;   /* Transmit data register,              Address offset 0x28 */
}               UART_t;

typedef enum    WORD_LENGTH_e
{
    EIGHT_BITS,
    NINE_BITS,
    SEVEN_BITS
}               WORD_LENGTH;

typedef enum    STOP_BITS_e
{
    ONE_BIT,
    HALF_BIT,
    TWO_BITS,
    ONE_AND_HALF_BIT
}               STOP_BITS;

#define DEFAULT_BRR_VALUE 0x34U

typedef struct  UART_config_s
{
    WORD_LENGTH word_length;
    uint32_t    baud_rate;
    STOP_BITS   stop_bits;
}               UART_config;

/* UART objects */
#define UART1            ((UART_t *)0x40013800U)
#define UART2            ((UART_t *)0x40004400U)
#define UART3            ((UART_t *)0x40004800U)
#define UART4            ((UART_t *)0x40004C00U)
#define UART5            ((UART_t *)0x40005000U)
#define UART6            ((UART_t *)0x40011400U)
#define UART7            ((UART_t *)0x40011800U)
#define UART8            ((UART_t *)0x40011C00U)

/* Note that configure function does not enable RCC */
void    uart_configure(UART_t *uart, UART_config *config);
void    uart_write(UART_t *uart, const char buf[], size_t len);
void    uart_read(UART_t *uart, char buf[], size_t len);

#endif
