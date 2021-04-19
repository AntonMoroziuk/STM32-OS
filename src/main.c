#include <stdint.h>

#include "gpio.h"
#include "utils.h"
#include "rcc.h"
#include "uart.h"
#include "malloc.h"
#include "asm.h"
#include "task.h"
#include "lcd.h"

void test_lcd(void)
{
    lcd_init();
    char buf[] = "Hello world!";
    for (int i = 0; buf[i]; i++)
        lcd_write(buf[i]);
}

void recursive(int step)
{
    char buf1[] = "enter  \r\n";
    char buf2[] = "exit  \r\n";
    char buf[] = "yield\r\n";

    buf1[6] = step + '0';
    buf2[5] = step + '0';
    uart_write(UART2, buf1, 9);
    if (step)
    {
        recursive(step - 1);
    }
    else
    {
        uart_write(UART2, buf, 7);
        yield();
    }
    uart_write(UART2, buf2, 8);
}

void test2(void)
{
    recursive(2);
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
    rcc_gpio_set(B, 1);
    rcc_gpio_set(C, 1);
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

    task_add(&test_lcd, 1024);

    task_scheduler();

    return (0);
}
