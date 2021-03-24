#include "malloc.h"
#include "utils.h"

static block_header *g_malloc;

static void *split_block(block_header *block, size_t size)
{
    block_header  *temp;

    if (block->size <= size + 2 * HEADER_SIZE + ALIGN(1))
    {
        block->free = 0;
        block->used = size;
        return ((void*)block);
    }
    temp = (block_header *)(block->data + size);
    temp->size = block->size - size - HEADER_SIZE;
    temp->used = temp->size;
    temp->next = block->next;
    temp->prev = block;
    temp->free = 1;
    block->size = size;
    block->used = size;
    block->next = temp;
    block->free = 0;
    return ((void*)block->data);
}

static void  malloc_init(void)
{
    g_malloc = (block_header *)HEAP_START;
    g_malloc->prev = NULL;
    g_malloc->next = NULL;
    g_malloc->size = RAM_SIZE - HEADER_SIZE;
    g_malloc->free = 1;
}

void        *malloc(size_t size)
{
    block_header  *cur;

    size = ALIGN(size);
    if (!g_malloc)
        malloc_init();

    cur = g_malloc;
    while (cur)
    {
        if (cur->size >= size && cur->free)
            return (split_block(cur, size));
        cur = cur->next;
    }
    return (NULL);
}
