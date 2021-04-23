#include <stdint.h>

#include "gpio.h"
#include "utils.h"

void    gpio_init(GPIO *GPIOx, GPIO_config *GPIO_init)
{
    GPIOx->MODER = set_bits_with_offset(GPIOx->MODER, GPIO_init->pin * 2U, 2, GPIO_init->mode);
    GPIOx->OSPEEDR = set_bits_with_offset(GPIOx->OSPEEDR, GPIO_init->pin * 2U, 2, GPIO_init->speed);
    GPIOx->PUPDR = set_bits_with_offset(GPIOx->PUPDR, GPIO_init->pin * 2U, 2, GPIO_init->pull);
}

void    gpio_set(GPIO_pin *gpio, uint8_t value)
{
    if (value)
        gpio->group->BSRR = 1 << gpio->pin;
    else
        gpio->group->BSRR = 1 << (gpio->pin + 16);
}

void    gpio_select_alternate_function(GPIO_pin *gpio, uint8_t function)
{
    const uint8_t offset = (gpio->pin % 8) * 4;

    if (gpio->pin <= 7)
        gpio->group->AFRL = set_bits_with_offset(gpio->group->AFRL, offset, 4, function);
    else
        gpio->group->AFRH = set_bits_with_offset(gpio->group->AFRH, offset, 4, function);
    gpio->group->MODER = set_bits_with_offset(gpio->group->MODER, gpio->pin * 2U, 2, GPIO_MODE_ALTERNATE_FUNC);
}
