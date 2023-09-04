#ifndef SCHEDULES_H
#define SCHEDULES_H
#include"task.h"
#define MINPRIORITY 1
#define MAXPRIORITY 10

void push(Task* task);

void schedule();

#endif