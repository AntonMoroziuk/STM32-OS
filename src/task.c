#include <stdint.h>

#include "task.h"
#include "asm.h"
#include "malloc.h"

// During context switch we push 8 registers to stack
#define CONTEXT_SIZE 8

static uint32_t *tasks[TASK_LIMIT];
static uint32_t *stacks[TASK_LIMIT];
static int      cur_task;

void task_delete()
{
    uint32_t *temp = tasks[cur_task];

    for (int i = cur_task; tasks[i]; i++)
    {
        tasks[i] = tasks[i + 1];
        stacks[i] = stacks[i + 1];
    }

    free(temp);
    exit();
}

void    task_add(void (*task_code)(void), size_t stack_size)
{
    int i = 0;

    while (tasks[i])
        i++;
    tasks[i] = (uint32_t*)malloc(stack_size);
    if (!tasks[i])
        return ;

    /*
     * During first context switch we will pop 8 registers
     * and pc register from stack, so we need space for them
     * */
    tasks[i][stack_size] = (uint32_t)task_code;
    stacks[i] = tasks[i] + stack_size - CONTEXT_SIZE;
}

void    task_scheduler(void)
{
    while(1)
    {
        if (!tasks[cur_task])
            cur_task = 0;

        // We ran out of tasks
        if (!tasks[cur_task])
        {
            while (1) ;
        }
        activate(stacks + cur_task);
        cur_task++;
    }
}
