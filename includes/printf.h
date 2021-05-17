#ifndef PRINTF_H
#define PRINTF_H

#include "writer.h"

#include <stddef.h>

// printf initialises and uses UART2 as default output stream
// however, it does not enable corresponding RCC
void printf(const char *format, ...);
void fprintf(const writer *wrt, const char *format, ...);

#endif
