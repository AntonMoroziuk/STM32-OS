#include <stdint.h>

#include "task.h"
#include "asm.h"
#include "malloc.h"

static unsigned int *tasks[TASK_LIMIT];

void    task_add(void (*task_code)(void), uint16_t stack_size)
{
    int i = 0;

    while (tasks[i])
        i++;
    tasks[i] = (unsigned int*)malloc(sizeof(unsigned int) * stack_size);

    tasks[i] += stack_size - 8;
    tasks[i][0] = (unsigned int)task_code;
}

void    task_scheduler(void)
{
    int i = 0;

    while(1)
    {
        if (!tasks[i])
            i = 0;
        activate(tasks[i]);
        i++;
    }
}
