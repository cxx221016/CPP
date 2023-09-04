#ifndef TASK_H
#define TASK_H
#include "list.h"

// representation of a task
typedef struct{
    AS_LIST_ITEM;
    char *name;
    //int tid;
    int no;
    int priority;
    int burst;
    int lastend;
} Task;

#endif