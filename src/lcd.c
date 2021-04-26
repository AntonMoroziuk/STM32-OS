#include "lcd.h"
#include "gpio.h"
#include "writer.h"
#include "malloc.h"

#include <string.h>
#include <stdint.h>

// init commands
#define LCD_4BIT_INIT          0x2
#define LCD_8BIT_1LINE_5x8DOTS 0x3

// commands
#define LCD_CLEARDISPLAY    0x01
#define LCD_RETURNHOME      0x02
#define LCD_ENTRYMODESET    0x04
#define LCD_DISPLAYCONTROL  0x08
#define LCD_CURSORSHIFT     0x10
#define LCD_FUNCTIONSET     0x20
#define LCD_SETCGRAMADDR    0x40
#define LCD_SETDDRAMADDR    0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT          0x00
#define LCD_ENTRYLEFT           0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON   0x04
#define LCD_DISPLAYOFF  0x00
#define LCD_CURSORON    0x02
#define LCD_CURSOROFF   0x00
#define LCD_BLINKON     0x01
#define LCD_BLINKOFF    0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE  0x00
#define LCD_MOVERIGHT   0x04
#define LCD_MOVELEFT    0x00

// flags for function set
#define LCD_8BITMODE    0x10
#define LCD_4BITMODE    0x00
#define LCD_2LINE       0x08
#define LCD_1LINE       0x00
#define LCD_5x10DOTS    0x04
#define LCD_5x8DOTS     0x00

typedef struct LCD_handler_s
{
    GPIO_pin    rs_pin; // LOW: command.  HIGH: character.
    GPIO_pin    enable_pin; // activated by a HIGH pulse.
    GPIO_pin    data_pins[4];

    uint8_t     displayfunction;
    uint8_t     displaycontrol;
    uint8_t     displaymode;

    uint8_t     numlines;
    uint8_t     row_offsets[4];
} LCD_handler;

static inline void delay(void)
{
    for (volatile int i = 0; i < 10000; i++) ;
}

static void pulse_enable(LCD_handler *handler)
{
    gpio_set(handler->enable_pin, 0);
    delay();
    gpio_set(handler->enable_pin, 1);
    delay();
    gpio_set(handler->enable_pin, 0);
    delay();
}

static void write4bits(LCD_handler *handler, uint8_t value)
{
    gpio_set(handler->data_pins[0], (value >> 0) & 0x1);
    gpio_set(handler->data_pins[1], (value >> 1) & 0x1);
    gpio_set(handler->data_pins[2], (value >> 2) & 0x1);
    gpio_set(handler->data_pins[3], (value >> 3) & 0x1);

    pulse_enable(handler);
}

static void lcd_command(LCD_handler *handler, uint8_t value)
{
    gpio_set(handler->rs_pin, 0);
    write4bits(handler, value >> 4);
    write4bits(handler, value);
}

void lcd_clear(LCD_handler *handler)
{
    lcd_command(handler, LCD_CLEARDISPLAY);
    delay();
}

void lcd_home(LCD_handler *handler)
{
    lcd_command(handler, LCD_RETURNHOME);
    delay();
}

void lcd_set_cursor(LCD_handler *handler, uint8_t col, uint8_t row)
{
    const size_t max_lines = sizeof(handler->row_offsets) / sizeof(*handler->row_offsets);
    if (row >= max_lines)
        row = max_lines - 1;    // we count rows starting w/ 0
    if (row >= handler->numlines)
        row = handler->numlines - 1;    // we count rows starting w/ 0

    lcd_command(handler, LCD_SETDDRAMADDR | (col + handler->row_offsets[row]));
}

void lcd_display_off(LCD_handler *handler)
{
    handler->displaycontrol &= ~LCD_DISPLAYON;
    lcd_command(handler, LCD_DISPLAYCONTROL | handler->displaycontrol);
}

void lcd_display_on(LCD_handler *handler)
{
    handler->displaycontrol |= LCD_DISPLAYON;
    lcd_command(handler, LCD_DISPLAYCONTROL | handler->displaycontrol);
}

void lcd_cursor_off(LCD_handler *handler)
{
    handler->displaycontrol &= ~LCD_CURSORON;
    lcd_command(handler, LCD_DISPLAYCONTROL | handler->displaycontrol);
}

void lcd_cursor_on(LCD_handler *handler)
{
    handler->displaycontrol |= LCD_CURSORON;
    lcd_command(handler, LCD_DISPLAYCONTROL | handler->displaycontrol);
}

void lcd_blink_off(LCD_handler *handler)
{
    handler->displaycontrol &= ~LCD_BLINKON;
    lcd_command(handler, LCD_DISPLAYCONTROL | handler->displaycontrol);
}

void lcd_blink_on(LCD_handler *handler)
{
    handler->displaycontrol |= LCD_BLINKON;
    lcd_command(handler, LCD_DISPLAYCONTROL | handler->displaycontrol);
}

void lcd_scroll_display_left(LCD_handler *handler)
{
    lcd_command(handler, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void lcd_scroll_display_right(LCD_handler *handler)
{
    lcd_command(handler, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void lcd_left_to_right(LCD_handler *handler)
{
    handler->displaymode |= LCD_ENTRYLEFT;
    lcd_command(handler, LCD_ENTRYMODESET | handler->displaymode);
}

void lcd_right_to_left(LCD_handler *handler)
{
    handler->displaymode &= ~LCD_ENTRYLEFT;
    lcd_command(handler, LCD_ENTRYMODESET | handler->displaymode);
}

void lcd_autoscroll_on(LCD_handler *handler)
{
    handler->displaymode |= LCD_ENTRYSHIFTINCREMENT;
    lcd_command(handler, LCD_ENTRYMODESET | handler->displaymode);
}

void lcd_autoscroll_off(LCD_handler *handler)
{
    handler->displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
    lcd_command(handler, LCD_ENTRYMODESET | handler->displaymode);
}

void lcd_create_char(LCD_handler *handler, uint8_t location, uint8_t charmap[])
{
    location &= 0x7; // we only have 8 locations 0-7
    lcd_command(handler, LCD_SETCGRAMADDR | (location << 3));
    for (int i = 0; i < 8; i++)
        lcd_write(handler, charmap[i]);
}

void lcd_write(LCD_handler *handler, char value)
{
    gpio_set(handler->rs_pin, 1);
    write4bits(handler, value >> 4);
    write4bits(handler, value);
}

void writer_lcd_write(writer *self, const char buf[], size_t len)
{
    for (size_t i = 0; i < len; i++)
        lcd_write((LCD_handler *)self->data, buf[i]);
}

writer *lcd_writer(LCD_handler *handler)
{
    writer *res = (writer*)malloc(sizeof(writer));
    if (!res)
        return (NULL);

    res->write = &writer_lcd_write;
    res->data = handler;
    return (res);
}

void lcd_delete_writer(writer *to_delete)
{
    free(to_delete);
}

void lcd_deinit(LCD_handler *handler)
{
    gpio_set(handler->rs_pin, 0);
    gpio_set(handler->enable_pin, 0);
    gpio_set(handler->data_pins[0], 0);
    gpio_set(handler->data_pins[1], 0);
    gpio_set(handler->data_pins[2], 0);
    gpio_set(handler->data_pins[3], 0);

    free(handler);
}

LCD_handler *lcd_init(LCD_config *config)
{
    LCD_handler *handler = (LCD_handler*)malloc(sizeof(LCD_handler));

    if (!handler)
        return (NULL);
    handler->enable_pin = config->enable_pin;
    handler->rs_pin = config->rs_pin;
    handler->data_pins[0] = config->data_pins[0];
    handler->data_pins[1] = config->data_pins[1];
    handler->data_pins[2] = config->data_pins[2];
    handler->data_pins[3] = config->data_pins[3];
    handler->numlines = 1;
    handler->row_offsets[0] = 0;
    handler->row_offsets[1] = 64;
    handler->row_offsets[2] = 16;
    handler->row_offsets[3] = 64 + 16;
    handler->displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

    GPIO_config rs_pin = {
        .pin = handler->rs_pin.pin,
        .mode = GPIO_MODE_OUTPUT,
        .pull = GPIO_NO_PUPD,
        .speed = GPIO_SPEED_LOW,
    };
    gpio_init(handler->rs_pin.port, &rs_pin);

    GPIO_config enable_pin = {
        .pin = handler->enable_pin.pin,
        .mode = GPIO_MODE_OUTPUT,
        .pull = GPIO_NO_PUPD,
        .speed = GPIO_SPEED_LOW,
    };
    gpio_init(handler->enable_pin.port, &enable_pin);

    GPIO_config data_pins_0 = {
        .pin = handler->data_pins[0].pin,
        .mode = GPIO_MODE_OUTPUT,
        .pull = GPIO_NO_PUPD,
        .speed = GPIO_SPEED_LOW,
    };
    gpio_init(handler->data_pins[0].port, &data_pins_0);

    GPIO_config data_pins_1 = {
        .pin = handler->data_pins[1].pin,
        .mode = GPIO_MODE_OUTPUT,
        .pull = GPIO_NO_PUPD,
        .speed = GPIO_SPEED_LOW,
    };
    gpio_init(handler->data_pins[1].port, &data_pins_1);

    GPIO_config data_pins_2 = {
        .pin = handler->data_pins[2].pin,
        .mode = GPIO_MODE_OUTPUT,
        .pull = GPIO_NO_PUPD,
        .speed = GPIO_SPEED_LOW,
    };
    gpio_init(handler->data_pins[2].port, &data_pins_2);

    GPIO_config data_pins_3 = {
        .pin = handler->data_pins[3].pin,
        .mode = GPIO_MODE_OUTPUT,
        .pull = GPIO_NO_PUPD,
        .speed = GPIO_SPEED_LOW,
    };
    gpio_init(handler->data_pins[3].port, &data_pins_3);

    delay();

    gpio_set(handler->rs_pin, 0);
    gpio_set(handler->enable_pin, 0);

    // Set inital configuration, repeat 3 times, as described in the datasheet
    write4bits(handler, LCD_8BIT_1LINE_5x8DOTS);
    delay();

    // second try
    write4bits(handler, LCD_8BIT_1LINE_5x8DOTS);
    delay();

    // third go!
    write4bits(handler, LCD_8BIT_1LINE_5x8DOTS);
    delay();

    // finally, set to 4-bit interface
    write4bits(handler, LCD_4BIT_INIT);

    // finally, set number of lines, font size, etc.
    lcd_command(handler, LCD_FUNCTIONSET | handler->displayfunction);

    // turn the display on with no cursor or blinking default
    handler->displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    lcd_display_on(handler);

    // clear it off
    lcd_clear(handler);

    // Initialize to default text direction (for romance languages)
    handler->displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    // set the entry mode
    lcd_command(handler, LCD_ENTRYMODESET | handler->displaymode);

    return (handler);
}
