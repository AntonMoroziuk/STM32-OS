#include <stdint.h>

#include "gpio.h"
#include "utils.h"
#include "rcc.h"
#include "uart.h"
#include "malloc.h"
#include "asm.h"
#include "task.h"

void hello_world(void)
{
    char buf[] = "Hello world!\r\n";

    while (1)
    {
        uart_write(UART2, buf, 14);
        yield();
    }
}

void bye_world(void)
{
    char buf[] = "Bye!\r\n";

    while (1)
    {
        uart_write(UART2, buf, 6);
        yield();
    }
}

int main()
{
    rcc_init_clocks();
    rcc_gpio_set(A, 1);
    rcc_uart_set(UART_PORT_2, 1);

    GPIO_config PA5_config = {
        .pin = GPIO_PIN_5,
        .mode = GPIO_MODE_OUTPUT,
        .pull = GPIO_NO_PUPD,
        .speed = GPIO_SPEED_LOW,
    };

    gpio_init(GPIOA, &PA5_config);
    gpio_set(GPIOA, (uint8_t)5, (uint8_t)1);

    UART_config uart_config = {
        .word_length = EIGHT_BITS,
        .baud_rate = DEFAULT_BRR_VALUE,
        .stop_bits = ONE_BIT,
    };
    uart_configure(UART2, &uart_config);

    task_add(&hello_world, 256);
    task_add(&bye_world, 256);
    task_scheduler();

    return (0);
}
