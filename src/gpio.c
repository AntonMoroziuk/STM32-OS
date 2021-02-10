#include <stdint.h>

#include "gpio.h"

#define SET_BITS_MASK   0x3U

// function to set bits
static void    set_bits_with_offset(volatile uint32_t *target, uint32_t offset, uint32_t value)
{
    uint32_t temp;

    temp = *target & ~(SET_BITS_MASK << offset);
    temp |= value << offset;

    *target = temp;
}

void    gpio_init(GPIO *GPIOx, GPIO_config *GPIO_init)
{
    set_bits_with_offset(&(GPIOx->MODER), GPIO_init->pin * 2U, GPIO_init->mode);
    set_bits_with_offset(&(GPIOx->OSPEEDR), GPIO_init->pin * 2U, GPIO_init->speed);
    set_bits_with_offset(&(GPIOx->PUPDR), GPIO_init->pin * 2U, GPIO_init->pull);
}

void    gpio_set(GPIO *GPIOx, uint8_t pin, uint8_t value)
{
    if (value)
        GPIOx->BSRR = 1 << pin;
    else
        GPIOx->BSRR = 1 << (pin + 16);
}
