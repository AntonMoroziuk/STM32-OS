#ifndef TIM_H
#define TIM_H

#include <stdint.h>

typedef struct TIM1_s
{
    volatile uint32_t    CR1;   /* Control register 1,              Address offset 0x00 */
    volatile uint32_t    CR2;   /* Control register 2,              Address offset 0x04 */
    volatile uint32_t    SMCR;  /* Slave mode control register,     Address offset 0x08 */
    volatile uint32_t    DIER;  /* DMA/interrupt enable register,   Address offset 0x0c */
    volatile uint32_t    SR;    /* Status register,                 Address offset 0x10 */
    volatile uint32_t    EGR;   /* Event generation register,       Address offset 0x14 */
    volatile uint32_t    CCMR1; /* Capture/compare mode register 1, Address offset 0x18 */
    volatile uint32_t    CCMR2; /* Capture/compare mode register 2, Address offset 0x1c */
    volatile uint32_t    CCER;  /* Capture/compare enable register, Address offset 0x20 */
    volatile uint32_t    CNT;   /* Counter,                         Address offset 0x24 */
    volatile uint32_t    PSC;   /* Prescaler,                       Address offset 0x28 */
    volatile uint32_t    ARR;   /* Auto-reload register,            Address offset 0x2c */
    volatile uint32_t    RCR;   /* Repetition counter register,     Address offset 0x30 */
    volatile uint32_t    CCR1;  /* Capture/compare register 1,      Address offset 0x34 */
    volatile uint32_t    CCR2;  /* Capture/compare register 2,      Address offset 0x38 */
    volatile uint32_t    CCR3;  /* Capture/compare register 3,      Address offset 0x3c */
    volatile uint32_t    CCR4;  /* Capture/compare register 4,      Address offset 0x40 */
    volatile uint32_t    BDTR;  /* Break and dead-time register,    Address offset 0x44 */
    volatile uint32_t    DCR;   /* DMA control register,            Address offset 0x48 */
    volatile uint32_t    DMAR;  /* DMA address for full transfer,   Address offset 0x4c */
} TIM1_t;

#define TIM1 ((TIM1_t *)0x40012C00U)

void delay_miliseconds(uint32_t delay);
void delay_microseconds(uint32_t delay);

#endif
