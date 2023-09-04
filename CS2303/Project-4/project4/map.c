#include "map.h"
#include<queue>
#include<vector>

using namespace std;

struct cmp
{
    bool operator ()(const Task* t1,const Task* t2)
    {
       return t1->burst>t2->burst;
    }
};

#ifdef __cplusplus
extern "C"
{
#endif 


struct cpq
{
    priority_queue<Task*,vector<Task*>,cmp> que;
};

cpq* queue_init()
{
    return new cpq;
}
void cpush(cpq* pr,Task* task)
{
    pr->que.push(task);
}
void cpop(cpq* pr)
{
    pr->que.pop();
}


Task* ctop(cpq* pr)
{
    return pr->que.top();
}

int csize(cpq* pr)
{
    return pr->que.size();
}


#ifdef __cplusplus
}
#endif

