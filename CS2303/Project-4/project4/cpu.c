#include"cpu.h"
void exec(Task* task,int slice)
{
    printf("Running task = [%s] [%d] [%d] for %d units.\n",task->name, task->priority, task->burst, slice);
}