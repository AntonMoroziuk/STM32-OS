#include "malloc.h"

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
    ptr->used = 0;
    ptr = defragment_backward(ptr);
    defragment_forward(ptr);
}

void    free(void *ptr)
{
    block_header  *temp;

    temp = (block_header *)((char*)ptr - HEADER_SIZE);
    if (temp->free)
        return ;
    else
        defragment(temp);
}
