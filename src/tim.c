#include "tim.h"
#include "utils.h"

#include <stdint.h>

/*
 * PSC register values to get 1 timer tick per 1 micro-/milisecond
 * provided clock frequency  is 8MHz
*/
#define MICROSECONDS_PRESCALER (8 - 1)
#define MILISECONDS_PRESCALER (8000 - 1)

// TIM1 EGR offsets
#define TIM1_UPDATE_GENERATION_OFFSET 0

// TIM1 CR1 offsets
#define TIM1_COUNTER_ENABLE_OFFSET 0
#define TIM1_OPM_OFFSET 3
#define TIM1_ARPE_OFFSET 7

static void delay_with_prescaler(uint32_t prescaler, uint32_t delay)
{
    TIM1->CNT = 0;
    TIM1->PSC = prescaler;
    TIM1->ARR = delay;

    // reset counter and generate an update of registers
    TIM1->EGR |= (1 << TIM1_UPDATE_GENERATION_OFFSET);

    // auto pre-load register - update after counter overflow
    TIM1->CR1 |= (1 << TIM1_ARPE_OFFSET);

    // set counter to stop after an update event and enable counter
    TIM1->CR1 |= (1 << TIM1_OPM_OFFSET) | (1 << TIM1_COUNTER_ENABLE_OFFSET);
    while(TIM1->CR1 & (1 << 0)) ;
}

void delay_miliseconds(uint32_t delay)
{
    delay_with_prescaler(MILISECONDS_PRESCALER, delay);
}

void delay_microseconds(uint32_t delay)
{
    delay_with_prescaler(MICROSECONDS_PRESCALER, delay);
}
