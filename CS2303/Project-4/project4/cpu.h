#ifndef CPU_H
#define CPU_H
#include "task.h"
#include <stdio.h>


#define QUANTUM 10

void exec(Task* curtask,int slice);

#endif
