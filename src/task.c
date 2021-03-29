#include <stdint.h>

#include "task.h"
#include "asm.h"
#include "malloc.h"

// During context switch we push 8 registers to stack
#define CONTEXT_SIZE 8

static uint32_t *tasks[TASK_LIMIT];

void    task_add(void (*task_code)(void), size_t stack_size)
{
    int i = 0;

    while (tasks[i])
        i++;
    tasks[i] = (uint32_t*)malloc(stack_size);

    /*
     * During first context switch we will pop 8 registers
     * and pc register from stack, so we need space for them
     * */
    tasks[i] += stack_size - CONTEXT_SIZE;
    tasks[i][0] = (uint32_t)task_code;
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
