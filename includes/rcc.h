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
    volatile uint32_t    AHB2ENR;   /* AHB peripheral clock enable register 2,  Address offset 0x18 */
    volatile uint32_t    AHB1ENR;   /* AHB peripheral clock enable register 1,  Address offset 0x1c */
    volatile uint32_t    BDCR;      /* RTC domain control register,             Address offset 0x20 */
    volatile uint32_t    CSR;       /*  Control/status register,                Address offset 0x24 */
    volatile uint32_t    AHBRSTR;   /* AHB peripheral reset register,           Address offset 0x28 */
    volatile uint32_t    CFGR2;     /* Clock configuration register 2,          Address offset 0x2c */
    volatile uint32_t    CFGR3;     /* Clock configuration register 3,          Address offset 0x30 */
    volatile uint32_t    CR2;       /* Clock control register 2,                Address offset 0x34 */
}              RCC_t; 

/* RCC memory offset */
#define RCC_BASE        (0x40021000U)

/* RCC object */
#define RCC             ((RCC_t *)RCC_BASE)

typedef enum    IO_PORT_e
{
    A = 17,
    B,
    C,
    D,
    E,
    F
}               IO_PORT;

void    rcc_gpio_set(IO_PORT io_port, uint8_t enable);

#endif
