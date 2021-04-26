#include "printf.h"
#include "uart.h"
#include "lcd.h"
#include "writer.h"
#include "utils.h"

#include <stdarg.h>
#include <stdint.h>

static void putchar(writer *stream, char c)
{
    stream->write(stream, &c, 1);
}

static void putstr(writer *stream, char *str)
{
    stream->write(stream, str, strlen(str));
}

static void putnbr(writer *stream, int n)
{
    if (n < 0)
    {
        putchar(stream, '-');
        putnbr(stream, -(n / 10));
        putchar(stream, -(n % 10) + '0');
    }
    else
    {
        if (n > 9)
        {
            putnbr(stream, n / 10);
            putchar(stream, n % 10 + '0');
        }
        else
            putchar(stream, n + '0');
    }
}

static void puthex(writer *stream, uint32_t n)
{
    if (n > 15)
    {
        puthex(stream, n / 16);
        puthex(stream, n % 16);
    }
    else
    {
        if (n > 9)
            putchar(stream, n - 10 + 'a');
        else
            putchar(stream, n + '0');
    }
}

typedef enum STATE_e
{
    DEFAULT,
    FOUND_PERCENT,
} STATE;

void printf(writer *stream, const char *format, ...)
{
    STATE state = DEFAULT;
    va_list args;

    va_start(args, format);

    // Based on finite automata, 0 - default state, 1 - found percent
    for (int i = 0; format[i]; i++)
    {
        if (state == DEFAULT && format[i] != '%')
            putchar(stream, format[i]);
        else if (state == FOUND_PERCENT)
        {
            switch (format[i])
            {
                case '%':
                    putchar(stream, '%');
                    state = DEFAULT;
                    break ;
                case 'd':
                    putnbr(stream, (int)va_arg(args, int));
                    state = DEFAULT;
                    break ;
                case 'c':
                    putchar(stream, (char)va_arg(args, int));
                    state = DEFAULT;
                    break ;
                case 's':
                    putstr(stream, va_arg(args, char *));
                    state = DEFAULT;
                    break ;
                case 'p':
                    putstr(stream, "0x");
                    puthex(stream, (uint32_t)va_arg(args, void *));
                    state = DEFAULT;
                    break ;
                default:
                    // We get here only in case of bad usage, just ignoring
                    state = DEFAULT;
            }
        }
        else
            state = FOUND_PERCENT;
    }
    va_end(args);
}
