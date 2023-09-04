#include "cpu.h"
#include "schedule.h"
#include "pmap.h"
#include "list.h"
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
        Task* p=ctop(que);cpop(que);
        list lst;
        list_init(&lst);
        list_push_back(&lst,p);
        while(csize(que)!=0&&ctop(que)->priority==p->priority)
        {
            list_push_back(&lst,ctop(que));
            cpop(que);
        }
        if(list_size(&lst)>1)
        {
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
        }

        else
        {
            responsetime+=curtime;
            waitingtime+=curtime;
            exec(p,p->burst);
            curtime+=p->burst;
            turnaroundtime+=curtime;
        }
    }
    printf("Average turnaround time is %.3lf\n",turnaroundtime/n);
    printf("Average response time is %.3lf\n",responsetime/n);
    printf("Average waiting time is %.3lf\n",waitingtime/n);
}