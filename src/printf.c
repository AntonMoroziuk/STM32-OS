#include "printf.h"
#include "uart.h"
#include "lcd.h"
#include "writer.h"
#include "utils.h"

#include <stdarg.h>
#include <stdint.h>

static void putchar(const writer *stream, const char c)
{
    stream->write(stream, &c, 1);
}

static void putstr(const writer *stream, const char *str)
{
    stream->write(stream, str, strlen(str));
}

static void putnbr(const writer *stream, const int n)
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

static void puthex(const writer *stream, const uint32_t n)
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
    STATE_DEFAULT,
    STATE_FOUND_PERCENT,
} STATE;

void fprintf(const writer *stream, const char *format, ...)
{
    STATE state = STATE_DEFAULT;
    va_list args;

    va_start(args, format);

    for (int i = 0; format[i]; i++)
    {
        if (state == STATE_DEFAULT)
        {
            if (format[i] == '%')
                state = STATE_FOUND_PERCENT;
            else
                putchar(stream, format[i]);
        }
        else
        {
            switch (format[i])
            {
                case '%':
                    putchar(stream, '%');
                    state = STATE_DEFAULT;
                    break ;
                case 'd':
                    putnbr(stream, (int)va_arg(args, int));
                    state = STATE_DEFAULT;
                    break ;
                case 'c':
                    putchar(stream, (char)va_arg(args, int));
                    state = STATE_DEFAULT;
                    break ;
                case 's':
                    putstr(stream, va_arg(args, char *));
                    state = STATE_DEFAULT;
                    break ;
                case 'p':
                    putstr(stream, "0x");
                    puthex(stream, (uint32_t)va_arg(args, void *));
                    state = STATE_DEFAULT;
                    break ;
                default:
                    // We get here only in case of bad usage, just ignoring
                    state = STATE_DEFAULT;
            }
        }
    }
    va_end(args);
}

void printf(const char *format, ...)
{
    STATE state = STATE_DEFAULT;
    va_list args;
    static writer* stream;

    if (!stream)
    {
        UART_config uart_config = {
            .word_length = EIGHT_BITS,
            .baud_rate = DEFAULT_BRR_VALUE,
            .stop_bits = ONE_BIT,
        };
        uart_configure(UART2, &uart_config);

        stream = uart_writer(UART2);

        if (!stream)
            return ;
    }

    va_start(args, format);

    for (int i = 0; format[i]; i++)
    {
        if (state == STATE_DEFAULT)
        {
            if (format[i] == '%')
                state = STATE_FOUND_PERCENT;
            else
                putchar(stream, format[i]);
        }
        else
        {
            switch (format[i])
            {
                case '%':
                    putchar(stream, '%');
                    state = STATE_DEFAULT;
                    break ;
                case 'd':
                    putnbr(stream, (int)va_arg(args, int));
                    state = STATE_DEFAULT;
                    break ;
                case 'c':
                    putchar(stream, (char)va_arg(args, int));
                    state = STATE_DEFAULT;
                    break ;
                case 's':
                    putstr(stream, va_arg(args, char *));
                    state = STATE_DEFAULT;
                    break ;
                case 'p':
                    putstr(stream, "0x");
                    puthex(stream, (uint32_t)va_arg(args, void *));
                    state = STATE_DEFAULT;
                    break ;
                default:
                    // We get here only in case of bad usage, just ignoring
                    state = STATE_DEFAULT;
            }
        }
    }
    va_end(args);
}
