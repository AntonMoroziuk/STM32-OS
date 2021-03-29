#ifndef MALLOC_H
#define MALLOC_H

#include <stdint.h>
#include <unistd.h>

extern uint32_t _estack;

#define HEAP_START ((void*)&_estack)

// Round up malloced size to be multiple of 32 bits
#define ALIGN(x) (((((x) - 1) >> 2) << 2) + 4)

#define HEADER_SIZE (sizeof(struct block_header_s))

#define RAM_END     (0x20008000U)

#define HEAP_SIZE  (RAM_END - (size_t)HEAP_START)

typedef struct  block_header_s
{
    size_t                  size;
    struct block_header_s   *next;
    struct block_header_s   *prev;
    int                     free;
    uint8_t                 data[];

}               block_header;

void            *malloc(size_t size);
void            free(void *ptr);

#endif
