#ifndef LCD_H
#define LCD_H

#include <stdint.h>

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

#define DELAY {for (int i = 0; i < 10000; i++) ;}

// Call this function before anything esle
void    lcd_init(void);

void    lcd_write(char value);

// Clear display, set cursor position to zero
void    lcd_clear(void);

// Set cursor position to zero
void    lcd_home(void);

void    lcd_set_cursor(uint8_t col, uint8_t row);

// Turn the display on/off (quickly)
void    lcd_display_off(void);
void    lcd_display_on(void);

// Turns the underline cursor on/off
void    lcd_cursor_off(void);
void    lcd_cursor_on(void);

// Turn on and off the blinking cursor
void    lcd_blink_off(void);
void    lcd_blink_on(void);

// These commands scroll the display without changing the RAM
void    lcd_scroll_display_left(void);
void    lcd_scroll_display_right(void);

// This is for text that flows Left to Right
void    lcd_left_to_right(void);

// This is for text that flows Right to Left
void    lcd_right_to_left(void);

// This will 'right justify' text from the cursor
void    lcd_autoscroll_on(void);

// This will 'left justify' text from the cursor
void    lcd_autoscroll_off(void);

// Allows us to fill the first 8 CGRAM locations with custom characters
void    lcd_create_char(uint8_t location, uint8_t charmap[]);

void    lcd_command(uint8_t value);

#endif
