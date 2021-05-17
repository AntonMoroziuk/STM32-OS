#ifndef RCC_H
#define RCC_H

typedef struct RCC_s
{
    volatile uint32_t    CR;        /* Clock control register,                  Address offset 0x00 */
    volatile uint32_t    CFGR;      /* Clock configuration register,            Address offset 0x04 */
    volatile uint32_t    CIR;       /* Clock interrupt register,                Address offset 0x08 */
    volatile uint32_t    APB2RSTR;  /* APB peripheral reset register 2,         Address offset 0x0c */
    volatile uint32_t    APB1RSTR;  /* APB peripheral reset register 1,         Address offset 0x10 */
    volatile uint32_t    AHBENR;    /* AHB peripheral clock enable register,    Address offset 0x14 */
    volatile uint32_t    APB2ENR;   /* APB peripheral clock enable register 2,  Address offset 0x18 */
    volatile uint32_t    APB1ENR;   /* APB peripheral clock enable register 1,  Address offset 0x1c */
    volatile uint32_t    BDCR;      /* RTC domain control register,             Address offset 0x20 */
    volatile uint32_t    CSR;       /* Control/status register,                 Address offset 0x24 */
    volatile uint32_t    AHBRSTR;   /* AHB peripheral reset register,           Address offset 0x28 */
    volatile uint32_t    CFGR2;     /* Clock configuration register 2,          Address offset 0x2c */
    volatile uint32_t    CFGR3;     /* Clock configuration register 3,          Address offset 0x30 */
    volatile uint32_t    CR2;       /* Clock control register 2,                Address offset 0x34 */
} RCC_t;

/* RCC object */
#define RCC ((RCC_t *)0x40021000U)

typedef enum IO_PORT_e
{
    A = 17,
    B,
    C,
    D,
    E,
    F,
} IO_PORT;

typedef enum UART_PORT_e
{
    UART_PORT_1 = 14,
    UART_PORT_2 = 17,
    UART_PORT_3 = 18,
    UART_PORT_4 = 19,
    UART_PORT_5 = 20,
    UART_PORT_6 = 5,
    UART_PORT_7 = 6,
    UART_PORT_8 = 7,
} UART_PORT;

typedef enum RCC_TIM_e
{
    RCC_TIM1 = 11,
    RCC_TIM2 = 0,
    RCC_TIM3 = 1,
    RCC_TIM6 = 4,
    RCC_TIM7 = 5,
    RCC_TIM14 = 8,
    RCC_TIM15 = 16,
    RCC_TIM16 = 17,
    RCC_TIM17 = 18,
} RCC_TIM;

void rcc_init_clocks(void);
void rcc_gpio_set(IO_PORT io_port, uint8_t enable);
void rcc_uart_set(UART_PORT uart_port, uint8_t enable);
void rcc_tim_set(RCC_TIM tim, uint8_t enable);

#endif
