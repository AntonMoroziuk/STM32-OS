#ifndef PRINTF_H
#define PRINTF_H

#include "writer.h"

#include <stddef.h>

void printf(writer *wrt, const char *format, ...);

#endif
