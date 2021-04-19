#include "lcd.h"
#include "gpio.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct  LCD_handler_s
{
    uint8_t rs_pin; // LOW: command.  HIGH: character.
    uint8_t rw_pin; // LOW: write to LCD.  HIGH: read from LCD.
    uint8_t enable_pin; // activated by a HIGH pulse.
    uint8_t data_pins[8];

    uint8_t displayfunction;
    uint8_t displaycontrol;
    uint8_t displaymode;

    uint8_t initialized;

    uint8_t numlines;
    uint8_t row_offsets[4];
}               LCD_handler;

static LCD_handler handler;

static void    pulse_enable(void)
{
    gpio_set(GPIOC, handler.enable_pin, 0);
    DELAY
    gpio_set(GPIOC, handler.enable_pin, 1);
    DELAY
    gpio_set(GPIOC, handler.enable_pin, 0);
    DELAY
}

static void    write4bits(uint8_t value)
{
    gpio_set(GPIOB, handler.data_pins[0], (value >> 0) & 0x1);
    gpio_set(GPIOB, handler.data_pins[1], (value >> 1) & 0x1);
    gpio_set(GPIOB, handler.data_pins[2], (value >> 2) & 0x1);
    gpio_set(GPIOA, handler.data_pins[3], (value >> 3) & 0x1);

    pulse_enable();
}

void    lcd_clear(void)
{
    lcd_command(LCD_CLEARDISPLAY);
    DELAY
}

void    lcd_home(void)
{
    lcd_command(LCD_RETURNHOME);
    DELAY
}

void    lcd_set_cursor(uint8_t col, uint8_t row)
{
    const size_t max_lines = sizeof(handler.row_offsets) / sizeof(*handler.row_offsets);
    if (row >= max_lines)
        row = max_lines - 1;    // we count rows starting w/ 0
    if (row >= handler.numlines)
        row = handler.numlines - 1;    // we count rows starting w/ 0

    lcd_command(LCD_SETDDRAMADDR | (col + handler.row_offsets[row]));
}

void    lcd_display_off(void)
{
    handler.displaycontrol &= ~LCD_DISPLAYON;
    lcd_command(LCD_DISPLAYCONTROL | handler.displaycontrol);
}

void    lcd_display_on(void)
{
    handler.displaycontrol |= LCD_DISPLAYON;
    lcd_command(LCD_DISPLAYCONTROL | handler.displaycontrol);
}

void    lcd_cursor_off(void)
{
    handler.displaycontrol &= ~LCD_CURSORON;
    lcd_command(LCD_DISPLAYCONTROL | handler.displaycontrol);
}

void    lcd_cursor_on(void)
{
    handler.displaycontrol |= LCD_CURSORON;
    lcd_command(LCD_DISPLAYCONTROL | handler.displaycontrol);
}

void    lcd_blink_off(void)
{
    handler.displaycontrol &= ~LCD_BLINKON;
    lcd_command(LCD_DISPLAYCONTROL | handler.displaycontrol);
}

void    lcd_blink_on(void)
{
    handler.displaycontrol |= LCD_BLINKON;
    lcd_command(LCD_DISPLAYCONTROL | handler.displaycontrol);
}

void    lcd_scroll_display_left(void)
{
    lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void    lcd_scroll_display_right(void)
{
    lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void    lcd_left_to_right(void)
{
    handler.displaymode |= LCD_ENTRYLEFT;
    lcd_command(LCD_ENTRYMODESET | handler.displaymode);
}

void    lcd_right_to_left(void)
{
    handler.displaymode &= ~LCD_ENTRYLEFT;
    lcd_command(LCD_ENTRYMODESET | handler.displaymode);
}

void    lcd_autoscroll_on(void)
{
    handler.displaymode |= LCD_ENTRYSHIFTINCREMENT;
    lcd_command(LCD_ENTRYMODESET | handler.displaymode);
}

void    lcd_autoscroll_off(void)
{
    handler.displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
    lcd_command(LCD_ENTRYMODESET | handler.displaymode);
}

void    lcd_create_char(uint8_t location, uint8_t charmap[])
{
    location &= 0x7; // we only have 8 locations 0-7
    lcd_command(LCD_SETCGRAMADDR | (location << 3));
    for (int i = 0; i < 8; i++)
        lcd_write(charmap[i]);
}

void    lcd_command(uint8_t value)
{
    gpio_set(GPIOA, handler.rs_pin, 0);
    write4bits(value >> 4);
    write4bits(value);
}

void    lcd_write(char value)
{
    gpio_set(GPIOA, handler.rs_pin, 1);
    write4bits(value >> 4);
    write4bits(value);
}

void    lcd_init(void)
{
    handler.rs_pin = 9;
    handler.enable_pin = 7;
    handler.data_pins[0] = 5;
    handler.data_pins[1] = 4;
    handler.data_pins[2] = 10;
    handler.data_pins[3] = 8;
    handler.numlines = 1;
    handler.row_offsets[0] = 0;
    handler.row_offsets[1] = 64;
    handler.row_offsets[2] = 16;
    handler.row_offsets[3] = 64 + 16;
    handler.displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

    GPIO_config gpio_config = {
        .pin = handler.rs_pin,
        .mode = GPIO_MODE_OUTPUT,
        .pull = GPIO_NO_PUPD,
        .speed = GPIO_SPEED_LOW,
    };
    gpio_init(GPIOA, &gpio_config);
    gpio_config.pin = handler.enable_pin;
    gpio_init(GPIOC, &gpio_config);
    gpio_config.pin = handler.data_pins[0];
    gpio_init(GPIOB, &gpio_config);
    gpio_config.pin = handler.data_pins[1];
    gpio_init(GPIOB, &gpio_config);
    gpio_config.pin = handler.data_pins[2];
    gpio_init(GPIOB, &gpio_config);
    gpio_config.pin = handler.data_pins[3];
    gpio_init(GPIOA, &gpio_config);

    DELAY

    gpio_set(GPIOA, handler.rs_pin, 0);
    gpio_set(GPIOC, handler.enable_pin, 0);

    write4bits(0x03);
    DELAY

    // second try
    write4bits(0x03);
    DELAY

    // third go!
    write4bits(0x03);
    DELAY

    // finally, set to 4-bit interface
    write4bits(0x02);

    // finally, set # lines, font size, etc.
    lcd_command(LCD_FUNCTIONSET | handler.displayfunction);

    // turn the display on with no cursor or blinking default
    handler.displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    lcd_display_on();

    // clear it off
    lcd_clear();

    // Initialize to default text direction (for romance languages)
    handler.displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    // set the entry mode
    lcd_command(LCD_ENTRYMODESET | handler.displaymode);
}
