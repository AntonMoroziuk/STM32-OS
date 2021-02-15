#include <stdint.h>

#include "gpio.h"
#include "utils.h"
#include "rcc.h"
#include "uart.h"

int main()
{
    rcc_gpio_set(A, 1);

    GPIO_config PA5_config = {
        .pin = GPIO_PIN_5,
        .mode = GPIO_MODE_OUTPUT,
        .pull = GPIO_NO_PUPD,
        .speed = GPIO_SPEED_LOW 
    };

    gpio_init(GPIOA, &PA5_config);
    gpio_set(GPIOA, (uint8_t)5, (uint8_t)1);

    UART_config uart_config = {
        .word_length = EIGHT_BITS,
        .baud_rate = DEFAULT_BRR_VALUE,
        .stop_bits = ONE_BIT,
        .port = UART1
    };
    uart_configure(&uart_config);

    char buf[] = "Hello, world!\n";

    uart_write(UART1, buf, sizeof(buf));

    while (1) {}

    return (0);
}
