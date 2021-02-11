#include <stdint.h>

#include "gpio.h"
#include "utils.h"

void    gpio_init(GPIO *GPIOx, GPIO_config *GPIO_init)
{
    GPIOx->MODER = set_bits_with_offset(GPIOx->MODER, GPIO_init->pin * 2U, 2, GPIO_init->mode);
    GPIOx->OSPEEDR = set_bits_with_offset(GPIOx->OSPEEDR, GPIO_init->pin * 2U, 2, GPIO_init->speed);
    GPIOx->PUPDR = set_bits_with_offset(GPIOx->PUPDR, GPIO_init->pin * 2U, 2, GPIO_init->pull);
}

void    gpio_set(GPIO *GPIOx, uint8_t pin, uint8_t value)
{
    if (value)
        GPIOx->BSRR = 1 << pin;
    else
        GPIOx->BSRR = 1 << (pin + 16);
}
