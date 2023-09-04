#include "cpu.h"
#include "schedule.h"
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
    list_item* tmp=NULL;
    list_for_each(&lst,tmp)
    {
        waitingtime+=curtime;
        responsetime+=curtime;
        Task* p=(Task*)tmp;
        exec(p,p->burst);
        curtime+=p->burst;
        turnaroundtime+=curtime;
    }
    printf("Average turnaround time is %.3lf\n",turnaroundtime/n);
    printf("Average response time is %.3lf\n",responsetime/n);
    printf("Average waiting time is %.3lf\n",waitingtime/n);
}