#ifndef WRITER_H
#define WRITER_H

#include <stddef.h>

typedef struct  writer_s
{
    void (*write)(struct writer_s *self, const char buf[], size_t len);
    void *data;
} writer;

#endif
