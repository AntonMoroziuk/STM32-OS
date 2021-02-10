#include <stdint.h>

#include "gpio.h"

int main()
{
    volatile uint32_t *RCC_AHBENR = (uint32_t *)0x40021014;

    *RCC_AHBENR |= (1 << 17);

    GPIO_config PA5_config;

    PA5_config.pin = GPIO_PIN_5;
    PA5_config.mode = GPIO_MODE_OUTPUT;
    PA5_config.pull = GPIO_NO_PUPD;
    PA5_config.speed = GPIO_SPEED_LOW;

    gpio_init(GPIOA, &PA5_config);
    gpio_set(GPIOA, (uint8_t)5, (uint8_t)1);

    while (1) {}

    return (0);
}
