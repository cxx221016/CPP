#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXINPUT 20
#define RQ 1
#define RL 2
#define C 3
#define STAT 4
#define INITPAIR(name,f,s) pair name; name.first=f;name.second=s

typedef struct 
{
    int first;
    int second;
}pair;

struct Node
{
    char* val;
    struct Node* next;
};

typedef struct Node Node;


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

int fitpage(int size)
{
    int res=size%4096;
    int res2=size/4096;
    if(res) res2++;
    return res2*4096;
}



int hash(char* name)
{
    int seed=MAXINPUT;
    for(int i=0;name[i];++i)
    {
        seed+=((int)name[i])*(i+1);
    }
    return seed;
}

pair* mp;
Node* head;
int blocknum=0;
int memorysize;


void insert(char* name)
{
    if(!head)
    {
        head=(Node*) malloc(sizeof(Node));
        head->val=strdup(name);
        head->next=NULL;
    }
    else
    {
        Node* tmp=(Node*)malloc(sizeof(Node));
        tmp->val=strdup(name);
        tmp->next=head->next;
        head->next=tmp;
    }
    blocknum++;
}

void erase(char* name)
{
    if(!head) return;

    Node *temp=head;
    Node *prev;
    while (temp)
    {
        if(strcmp(temp->val,name)==0)
        {
            if(temp==head)
                head=temp->next;
            else
                prev->next=temp->next;
            blocknum--;
            return ;
        }
            
        prev=temp;
        temp=temp->next;
    }
    blocknum--;
    return ;
}



int preinput(char* input);

int request(char* input);
int release(char* input);
void compact();
void status();

int firstfit(int size);
int worstfit(int size);
int bestfit(int size);

int main(int argc ,char* argv[])
{
    mp=(pair*)malloc (sizeof(pair)*1000000);
    //memorysize=(int*)malloc(sizeof(int));
    blocknum=0;
    memorysize=atoi(argv[1]);
    fprintf(stdout,"cxxallocator>");
    char* input=(char*) malloc(sizeof(char)*MAXINPUT);
    while(fgets(input,MAXINPUT-1,stdin))
    {
        int cmd=preinput(input);
        switch (cmd)
        {
            case RQ:
                request(input);
                break;
            case RL:
                release(input);
                break;
            case C:
                compact();
                break;
            case STAT:
                status();
                break;
            default: 
                return 0;
                
        }
        fprintf(stdout,"cxxallocator>");
    }
}

int preinput(char* input)
{
    if(input[0]=='C')
        return C;
    else if(input[0]=='S')
        return STAT;
    else if(input[1]=='Q')
        return RQ;
    else if(input[1]=='L')
        return RL; 
}

int request(char* input)
{
    //fprintf(stdout,"RQ\n");
    char* cmd=strsep(&input," ");
    char* name=strsep(&input," ");
    int size=atoi(strsep(&input," "));
    char* fits=strsep(&input," ");
    size=fitpage(size);
    int curidx=0;
    switch (fits[0])
    {
        case 'F':
            curidx=firstfit(size);
            break;
        case 'W':
            curidx=worstfit(size);
            break;
        case 'B':
            curidx=bestfit(size);
            break;
    }
    INITPAIR(pr,curidx,curidx+size-1);
    mp[hash(name)]=pr;
    insert(name);
}

int release(char* input)
{
    char* cmd=strsep(&input," ");
    char* name=strsep(&input,"\n");
    erase(name);
}

void compact()
{
    Node* cur=head;
    int curidx=0;
    while(cur)
    {
        int hh=hash(cur->val);
        int len=mp[hh].second-mp[hh].first+1;
        mp[hh].first=curidx;
        mp[hh].second=curidx+len-1;
        curidx+=len;
        cur=cur->next;
    }
}

void sort(int a[],int size)
{
    for(int j=size-1;j>0;--j)
    {
        for(int i=0;i<j;++i)
        {
            if(a[i]>a[i+1])
            {
                int tmp=a[i];
                a[i]=a[i+1];
                a[i+1]=tmp;
            }
        }
    }
}

void status()
{
    if(!head) 
    {
        fprintf(stdout,"%d to %d has not been used\n",0,memorysize);
        return ;
    }
    Node* cur=head;
    int array[blocknum*2];
    char* tostring[20000];
    int i=0;
    while(cur)
    {
        int hh=hash(cur->val);
        array[i++]=mp[hh].first;
        array[i++]=mp[hh].second;
        tostring[array[i-2]+array[i-1]]=strdup(cur->val);
        cur=cur->next;
    }
    sort(array,2*blocknum);
    if(array[0]!=0) fprintf(stdout,"%d to %d has not been used\n",0,array[0]-1);
    for(int i=1;i<2*blocknum;++i)
    {
        if(i&1) fprintf(stdout,"%d to %d has been used by %s\n",array[i-1],array[i],tostring[array[i-1]+array[i]]);
        else if(array[i-1]+1!=array[i]) fprintf(stdout,"%d to %d has not been used\n",array[i-1]+1,array[i]-1);
    }
    if(array[2*blocknum-1]!=memorysize) fprintf(stdout,"%d to %d has not been used\n",array[2*blocknum-1]+1,memorysize);
}


int firstfit(int size)
{
    if(!head)
    {
        return 0;
    }
    Node* cur=head;
    int array[blocknum*2];
    int i=0;
    while(cur)
    {
        int hh=hash(cur->val);
        array[i++]=mp[hh].first;
        array[i++]=mp[hh].second;
        cur=cur->next;
    }
    sort(array,2*blocknum);
    if(array[0]!=0) 
    {
        int cursize=array[0];
        if(cursize>=size) return 0;
    }
    for(int i=2;i<2*blocknum;i+=2)
    {
        int cursize=array[i]-array[i-1]-1;
        if(cursize>=size) return array[i-1]+1;
    }
    if(array[2*blocknum-1]!=memorysize)
    {
        int cursize=memorysize-array[2*blocknum-1];
        if(cursize>=size) return array[2*blocknum-1]+1;
    }
    return -1;
    
}
int worstfit(int size)
{
    if(!head) return 0;
    Node* cur=head;
    int array[blocknum*2];
    int i=0;
    while(cur)
    {
        int hh=hash(cur->val);
        array[i++]=mp[hh].first;
        array[i++]=mp[hh].second;
        cur=cur->next;
    }
    sort(array,2*blocknum);
    int res=-1;
    int lastsize=-1;
    if(array[0]!=0) 
    {
        int cursize=array[0];
        if(cursize>=size&&cursize>lastsize)
        {
            res=0;
            lastsize=cursize;
        }
    }
    for(int i=2;i<2*blocknum;i+=2)
    {
        int cursize=array[i]-array[i-1]-1;
        if(cursize>=size&&cursize>lastsize)
        {
            res=array[i-1]+1;
            lastsize=cursize;
        }
    }
    if(array[2*blocknum-1]!=memorysize)
    {
        int cursize=memorysize-array[2*blocknum-1];
        if(cursize>=size&&cursize>lastsize)
        {
            res=array[2*blocknum-1]+1;
            lastsize=cursize;
        }
    }
    return res;
}
int bestfit(int size)
{
    if(!head) return 0;
    Node* cur=head;
    int array[blocknum*2];
    int i=0;
    while(cur)
    {
        int hh=hash(cur->val);
        array[i++]=mp[hh].first;
        array[i++]=mp[hh].second;
        cur=cur->next;
    }
    sort(array,2*blocknum);
    int res=-1;
    int lastsize=0x3f3f3f3f;
    if(array[0]!=0) 
    {
        int cursize=array[0];
        if(cursize>=size&&cursize<lastsize)
        {
            res=0;
            lastsize=cursize;
        }
    }
    for(int i=2;i<2*blocknum;i+=2)
    {
        int cursize=array[i]-array[i-1]-1;
        if(cursize>=size&&cursize<lastsize)
        {
            res=array[i-1]+1;
            lastsize=cursize;
        }
    }
    if(array[2*blocknum-1]!=memorysize)
    {
        int cursize=memorysize-array[2*blocknum-1];
        if(cursize>=size&&cursize<lastsize)
        {
            res=array[2*blocknum-1]+1;
            lastsize=cursize;
        }
    }
    return res;
}