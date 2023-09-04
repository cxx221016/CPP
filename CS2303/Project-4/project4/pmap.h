#ifndef MAP_H
#define MAP_H
#include"task.h"

#ifdef __cplusplus
extern "C"
{
#endif 

struct cpq;
typedef  cpq  cpq;

cpq* queue_init();
void cpush(cpq* pr,Task* task);
void cpop(cpq* pr);
Task* ctop(cpq* pr);
int csize(cpq* pr);


#ifdef __cplusplus
}
#endif

#endif