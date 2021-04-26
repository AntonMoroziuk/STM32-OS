#include <stdint.h>

#include "task.h"
#include "asm.h"
#include "malloc.h"

// During context switch we push 8 registers to stack
#define CONTEXT_SIZE 8

static uint32_t *tasks[TASK_LIMIT];
static uint32_t *stacks[TASK_LIMIT];
static int      cur_task;

void task_delete(void)
{
    uint32_t *temp = tasks[cur_task];

    for (int i = cur_task; tasks[i] && i < TASK_LIMIT - 1; i++)
    {
        tasks[i] = tasks[i + 1];
        stacks[i] = stacks[i + 1];
    }
    tasks[TASK_LIMIT - 1] = NULL;
    stacks[TASK_LIMIT - 1] = NULL;
    free(temp);
    exit();
}

int task_add(void (*task_code)(void), size_t stack_size)
{
    int i = 0;

    while (tasks[i] && i < TASK_LIMIT)
        i++;

    if (i == TASK_LIMIT)
        return (ERR_TASK_LIMIT);

    tasks[i] = (uint32_t*)malloc(stack_size);
    if (!tasks[i])
        return (ERR_MALLOC_FAIL);

    /*
     * During first context switch we will pop 8 registers
     * and pc register from stack, so we need space for them
     * */
    tasks[i][stack_size] = (uint32_t)task_code;
    stacks[i] = tasks[i] + stack_size - CONTEXT_SIZE;
    return (0);
}

void task_scheduler(void)
{
    while(1)
    {
        cur_task = 0;
        while (tasks[cur_task] && cur_task < TASK_LIMIT)
        {
            activate(stacks + cur_task);
            cur_task++;
        }
    }
}
