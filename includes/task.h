#ifndef TASK_H
#define TASK_H

#include <stdint.h>
#include <stddef.h>

#define TASK_LIMIT 16

// task_add error codes
#define ERR_TASK_LIMIT  1
#define ERR_MALLOC_FAIL 2

int task_add(void (*task_code)(void), size_t stack_size);
void task_scheduler(void);

#endif
