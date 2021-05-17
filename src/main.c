#include <stdint.h>

#include "gpio.h"
#include "utils.h"
#include "rcc.h"
#include "uart.h"
#include "malloc.h"
#include "asm.h"
#include "task.h"
#include "lcd.h"
#include "printf.h"

void test_lcd(void)
{
    LCD_config lcd_config = {
        .enable_pin = {GPIOC, GPIO_PIN_7},
        .rs_pin = {GPIOA, GPIO_PIN_9},
        .data_pins[0] = {GPIOB, GPIO_PIN_5},
        .data_pins[1] = {GPIOB, GPIO_PIN_4},
        .data_pins[2] = {GPIOB, GPIO_PIN_10},
        .data_pins[3] = {GPIOA, GPIO_PIN_8},
    };
    LCD_handler *lcd_handler = lcd_init(&lcd_config);
    if (!lcd_handler)
        return ;

    writer *stream = lcd_writer(lcd_handler);
    if (!stream)
        goto writer_init_fail;

    fprintf(stream, "Hello world!");
    printf("Hello world!");

    lcd_delete_writer(stream);
writer_init_fail:
    lcd_deinit(lcd_handler);
}

int main()
{
    rcc_init_clocks();
    rcc_gpio_set(A, 1);
    rcc_gpio_set(B, 1);
    rcc_gpio_set(C, 1);
    rcc_uart_set(UART_PORT_2, 1);
    rcc_tim_set(RCC_TIM1, 1);

    GPIO_config PA5_config = {
        .pin = GPIO_PIN_5,
        .mode = GPIO_MODE_OUTPUT,
        .pull = GPIO_NO_PUPD,
        .speed = GPIO_SPEED_LOW,
    };

    gpio_init(GPIOA, &PA5_config);

    // Enable LED
    gpio_set((GPIO_pin){GPIOA, GPIO_PIN_5}, (uint8_t)1);

    task_add(&test_lcd, 1024);

    task_scheduler();

    return (0);
}
