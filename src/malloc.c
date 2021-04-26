#include "malloc.h"
#include "utils.h"

static block_header *g_malloc;

static void *split_block(block_header *block, size_t size)
{
    block_header  *temp;

    if (block->size <= size + 2 * HEADER_SIZE + ALIGN(1))
    {
        block->free = 0;
        return ((void*)block->data);
    }
    temp = (block_header *)(block->data + size);
    temp->size = block->size - size - HEADER_SIZE;
    temp->next = block->next;
    temp->prev = block;
    temp->free = 1;
    block->size = size;
    block->next = temp;
    block->free = 0;
    return ((void*)block->data);
}

static void malloc_init(void)
{
    g_malloc = (block_header *)HEAP_START;
    g_malloc->prev = NULL;
    g_malloc->next = NULL;
    g_malloc->size = HEAP_SIZE - HEADER_SIZE;
    g_malloc->free = 1;
}

static void defragment_forward(block_header *ptr)
{
    block_header  *cur;

    cur = ptr->next;
    while (cur)
        if (cur->free)
        {
            ptr->size += HEADER_SIZE + cur->size;
            ptr->next = cur->next;
            cur = cur->next;
        }
        else
            return ;
}

static void *defragment_backward(block_header *ptr)
{
    block_header  *cur;
    block_header  *tmp;

    cur = ptr->prev;
    tmp = ptr;
    while (cur)
        if (cur->free)
        {
            cur->size += HEADER_SIZE + tmp->size;
            cur->next = tmp->next;
            tmp = cur;
            cur = cur->prev;
        }
        else
            return (cur->next);
    return (tmp);
}

static void defragment(block_header *ptr)
{
    ptr->free = 1;
    ptr = defragment_backward(ptr);
    defragment_forward(ptr);
}

void *malloc(size_t size)
{
    size = ALIGN(size);
    if (!g_malloc)
        malloc_init();

    for (block_header *cur = g_malloc; cur; cur = cur->next)
        if (cur->size >= size && cur->free)
            return (split_block(cur, size));
    return (NULL);
}

void free(void *ptr)
{
    block_header  *temp;

    temp = (block_header *)((char*)ptr - HEADER_SIZE);
    if (temp->free)
        return ;
    else
        defragment(temp);
}
