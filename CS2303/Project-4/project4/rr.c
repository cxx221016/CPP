#include "cpu.h"
#include "schedule.h"
#include "list.h"
#include<stdbool.h>
#include<stdio.h>

list lst;
bool flag=false;
int curtime=0;
double waitingtime=0;
double responsetime=0;
double turnaroundtime=0;


void push(Task* task)
{
    if(flag==false)
    {
        list_init(&lst);
        flag=true;
    }
    list_push_back(&lst,task);
}

void schedule()
{
    double n=list_size(&lst);
    list_item* tmp;
    while(list_size(&lst)!=0)
    {
        tmp=(&lst)->head;
        Task* p=(Task*) tmp;
        if(p->burst>QUANTUM)
        {
            if(p->lastend==0) responsetime+=curtime;
            waitingtime+=curtime-p->lastend;
            exec(p,QUANTUM);
            curtime+=QUANTUM;
            p->lastend=curtime;
            list_remove_first(&lst);
            p->burst-=QUANTUM;
            list_push_back(&lst,p);
        }
        else
        {
            if(p->lastend==0) responsetime+=curtime;
            waitingtime+=curtime-p->lastend;
            exec(p,p->burst);
            curtime+=p->burst;
            p->lastend=curtime;
            turnaroundtime+=curtime;
            list_remove_first(&lst);
        }
    }
    printf("Average turnaround time is %.3lf\n",turnaroundtime/n);
    printf("Average response time is %.3lf\n",responsetime/n);
    printf("Average waiting time is %.3lf\n",waitingtime/n);
}