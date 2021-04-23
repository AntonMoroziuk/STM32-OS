#ifndef PRINTF_H
#define PRINTF_H

#include <stddef.h>

typedef struct  writer_s
{
    void (*write)(struct writer_s *self, const char buf[], size_t len);
    void *data;
}               writer;

void printf(writer *wrt, const char *format, ...);

#endif
