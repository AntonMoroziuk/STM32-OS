#ifndef LCD_H
#define LCD_H

#include "gpio.h"
#include "writer.h"

#include <stdint.h>

typedef struct LCD_handler_s LCD_handler;

typedef struct LCD_config_s
{
    GPIO_pin    rs_pin;
    GPIO_pin    enable_pin;
    GPIO_pin    data_pins[4];
} LCD_config;

// Call this function before anything esle
LCD_handler *lcd_init(LCD_config *config);

void lcd_deinit(LCD_handler *handler);

void lcd_write(LCD_handler *handler, char value);

// Clear display, set cursor position to zero
void lcd_clear(LCD_handler *handler);

// Set cursor position to zero
void lcd_home(LCD_handler *handler);

void lcd_set_cursor(LCD_handler *handler, uint8_t col, uint8_t row);

// Turn the display on/off (quickly)
void lcd_display_off(LCD_handler *handler);
void lcd_display_on(LCD_handler *handler);

// Turns the underline cursor on/off
void lcd_cursor_off(LCD_handler *handler);
void lcd_cursor_on(LCD_handler *handler);

// Turn on and off the blinking cursor
void lcd_blink_off(LCD_handler *handler);
void lcd_blink_on(LCD_handler *handler);

// These commands scroll the display without changing the RAM
void lcd_scroll_display_left(LCD_handler *handler);
void lcd_scroll_display_right(LCD_handler *handler);

// This is for text that flows Left to Right
void lcd_left_to_right(LCD_handler *handler);

// This is for text that flows Right to Left
void lcd_right_to_left(LCD_handler *handler);

// This will 'right justify' text from the cursor
void lcd_autoscroll_on(LCD_handler *handler);

// This will 'left justify' text from the cursor
void lcd_autoscroll_off(LCD_handler *handler);

// Allows us to fill the first 8 CGRAM locations with custom characters
void lcd_create_char(LCD_handler *handler, uint8_t location, uint8_t charmap[]);

writer *lcd_writer(LCD_handler *handler);
void lcd_delete_writer(writer *to_delete);

#endif
