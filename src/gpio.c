#include <stdint.h>

#include "gpio.h"
#include "utils.h"

void    gpio_init(GPIO *GPIOx, GPIO_config *GPIO_init)
{
    GPIOx->MODER = set_bits_with_offset(GPIOx->MODER, GPIO_init->pin * 2U, 2, GPIO_init->mode);
    GPIOx->OSPEEDR = set_bits_with_offset(GPIOx->OSPEEDR, GPIO_init->pin * 2U, 2, GPIO_init->speed);
    GPIOx->PUPDR = set_bits_with_offset(GPIOx->PUPDR, GPIO_init->pin * 2U, 2, GPIO_init->pull);
}

void    gpio_set(GPIO_pin gpio, uint8_t value)
{
    if (value)
        gpio.port->BSRR = 1 << gpio.pin;
    else
        gpio.port->BSRR = 1 << (gpio.pin + 16);
}

int gpio_read(GPIO_pin gpio)
{
    return ((gpio.port->IDR & (1 << gpio.pin)) > 0);
}

void    gpio_select_alternate_function(GPIO_pin gpio, uint8_t function)
{
    const uint8_t offset = (gpio.pin % 8) * 4;

    if (gpio.pin <= 7)
        gpio.port->AFRL = set_bits_with_offset(gpio.port->AFRL, offset, 4, function);
    else
        gpio.port->AFRH = set_bits_with_offset(gpio.port->AFRH, offset, 4, function);
    gpio.port->MODER = set_bits_with_offset(gpio.port->MODER, gpio.pin * 2U, 2, GPIO_MODE_ALTERNATE_FUNC);
}
