#ifndef MALLOC_H
#define MALLOC_H

#include <stdint.h>
#include <unistd.h>

extern uint32_t _ebss;

#define HEAP_START ((void*)&_ebss);

#define ALIGN(x) (((((x) - 1) >> 2) << 2) + 4)

#define HEADER_SIZE (sizeof(size_t) * 2 + sizeof(int) + sizeof(void*) * 2)

#define RAM_SIZE 32000

typedef struct  block_header_s
{
    size_t                  size;
    size_t                  used;
    struct block_header_s   *next;
    struct block_header_s   *prev;
    int                     free;
    char                    data[1];

}               block_header;

void            *malloc(size_t size);
void            free(void *ptr);

#endif
