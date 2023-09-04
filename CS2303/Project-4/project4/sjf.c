#include "cpu.h"
#include "schedule.h"
#include "map.h"
#include<stdbool.h>
#include<stdio.h>

cpq* que;
bool flag=false;
int curtime=0;
double waitingtime=0;
double responsetime=0;
double turnaroundtime=0;


void push(Task* task)
{
    if(flag==false)
    {
        que=queue_init();
        flag=true;
    }
    cpush(que,task);
}

void schedule()
{
    double n=csize(que);
    while(csize(que)!=0)
    {
        waitingtime+=curtime;
        responsetime+=curtime;
        Task* p=ctop(que);cpop(que);
        exec(p,p->burst);
        curtime+=p->burst;
        turnaroundtime+=curtime;
    }
    printf("Average turnaround time is %.3lf\n",turnaroundtime/n);
    printf("Average response time is %.3lf\n",responsetime/n);
    printf("Average waiting time is %.3lf\n",waitingtime/n);
}