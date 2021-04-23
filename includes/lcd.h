#ifndef LCD_H
#define LCD_H

#include "gpio.h"
#include "printf.h"

#include <stdint.h>

typedef struct  LCD_handler_s
{
    GPIO_pin    *rs_pin; // LOW: command.  HIGH: character.
    GPIO_pin    *enable_pin; // activated by a HIGH pulse.
    GPIO_pin    *data_pins[4];

    uint8_t     displayfunction;
    uint8_t     displaycontrol;
    uint8_t     displaymode;

    uint8_t     numlines;
    uint8_t     row_offsets[4];
}               LCD_handler;

// Call this function before anything esle
void    lcd_init(LCD_handler *hanlder);

void    lcd_write(LCD_handler *hanlder, char value);

// Clear display, set cursor position to zero
void    lcd_clear(LCD_handler *hanlder);

// Set cursor position to zero
void    lcd_home(LCD_handler *hanlder);

void    lcd_set_cursor(LCD_handler *hanlder, uint8_t col, uint8_t row);

// Turn the display on/off (quickly)
void    lcd_display_off(LCD_handler *hanlder);
void    lcd_display_on(LCD_handler *hanlder);

// Turns the underline cursor on/off
void    lcd_cursor_off(LCD_handler *hanlder);
void    lcd_cursor_on(LCD_handler *hanlder);

// Turn on and off the blinking cursor
void    lcd_blink_off(LCD_handler *hanlder);
void    lcd_blink_on(LCD_handler *hanlder);

// These commands scroll the display without changing the RAM
void    lcd_scroll_display_left(LCD_handler *hanlder);
void    lcd_scroll_display_right(LCD_handler *hanlder);

// This is for text that flows Left to Right
void    lcd_left_to_right(LCD_handler *hanlder);

// This is for text that flows Right to Left
void    lcd_right_to_left(LCD_handler *hanlder);

// This will 'right justify' text from the cursor
void    lcd_autoscroll_on(LCD_handler *hanlder);

// This will 'left justify' text from the cursor
void    lcd_autoscroll_off(LCD_handler *hanlder);

// Allows us to fill the first 8 CGRAM locations with custom characters
void    lcd_create_char(LCD_handler *hanlder, uint8_t location, uint8_t charmap[]);

writer *lcd_writer(LCD_handler *handler);

#endif
