#include "printf.h"
#include "uart.h"
#include "lcd.h"

#include <stdarg.h>
#include <stdint.h>

static void putchar(writer *stream, char c)
{
    stream->write(stream, &c, 1);
}

static void putstr(writer *stream, char *str)
{
    for (int i = 0; str[i]; i++)
        putchar(stream, str[i]);
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

void     printf(writer *stream, const char *format, ...)
{
    int state = 0;
    va_list args;

    va_start(args, format);

    // Based on finite automata, 0 - default state, 1 - found percent
    for (int i = 0; format[i]; i++)
    {
        if (!state && format[i] != '%')
            putchar(stream, format[i]);
        else if (state == 1)
        {
            switch (format[i])
            {
                case '%':
                    putchar(stream, '%');
                    state = 0;
                    break ;
                case 'd':
                    putnbr(stream, (int)va_arg(args, int));
                    state = 0;
                    break ;
                case 'c':
                    putchar(stream, (char)va_arg(args, int));
                    state = 0;
                    break ;
                case 's':
                    putstr(stream, va_arg(args, char *));
                    state = 0;
                    break ;
                case 'p':
                    putstr(stream, "0x");
                    puthex(stream, (uint32_t)va_arg(args, void *));
                    state = 0;
                    break ;
                default:
                    // We get here only in case of bad usage, just ignoring
                    state = 0;
            }
        }
        else
            state = 1;
    }
    va_end(args);
}
