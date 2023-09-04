#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"
#include "schedule.h"

char* strsep(char** stringp, const char* delim)
{
  char* start = *stringp;
  char* p;

  p = (start != NULL) ? strpbrk(start, delim) : NULL;

  if (p == NULL)
  {
    *stringp = NULL;
  }
  else
  {
    *p = '\0';
    *stringp = p + 1;
  }

  return start;
}

static int no=0;

int main(int argc,char* argv[])
{
    FILE* fin;
    char* temp;
    char task[100];
    char* name;
    int priority,burst;
    fin=fopen(argv[1],"r");
    while(fgets(task,100,fin)!=NULL)
    {
        temp=strdup(task);
        name=strsep(&temp,",");
        priority=atoi(strsep(&temp,","));
        burst=atoi(strsep(&temp,","));

        //printf("%s %d %d\n",name,priority,burst);
        Task* task=(Task*)malloc(sizeof(Task));
        task->name=strdup(name);
        task->priority=priority;
        task->burst=burst;
        task->lastend=0;
        task->no=no++;
        push(task);
        free(temp);
    }
    fclose(fin);

    schedule();
    return 0;
}