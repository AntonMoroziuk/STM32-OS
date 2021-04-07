#ifndef TASK_H
#define TASK_H

#include <stdint.h>
#include <stddef.h>

#define TASK_LIMIT 16

void    task_add(void (*task_code)(void), size_t stack_size);
void    task_scheduler(void);

#endif
