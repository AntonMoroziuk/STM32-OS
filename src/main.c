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

void dummy(void)
{

}

void test3(void)
{
    char buf[] = "0\r\n";

    for (int i = 0; i < 10; i++)
    {
        buf[0] = i + '0';
        uart_write(UART2, buf, 3);
        yield();
    }
}

void test1(void)
{
    char buf[] = "Hello world!\r\n";

    uart_write(UART2, buf, 14);
    task_add(&test1, 256);
}

void bye_world(void)
{
    char buf[] = "Bye!\r\n";

    uart_write(UART2, buf, 6);
    yield();

    char buf1[] = "Kek!\r\n";

    uart_write(UART2, buf1, 6);
    yield();

    char buf2[] = "Wtf!\r\n";

    uart_write(UART2, buf2, 6);
    yield();
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

    task_add(&dummy, 256);
    task_add(&dummy, 256);
    task_add(&test3, 256);
    task_scheduler();

    return (0);
}
