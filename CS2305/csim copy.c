//#include "cachelab.h"
#include"stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"

typedef struct
{
    bool valid;
    int tag;
    int time;
}line;

typedef struct
{
    line* lines;
    int e;
}set;

typedef struct
{
    int s;
    int e;
    int b;
    set* sets;
}cache;

typedef struct 
{
    char op;
    unsigned long addr;
    int size;
}operator;

int hits=0,misses=0,evictions=0;
int time=0;

void helpinfos()
{
    printf("Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\n");
    printf("Options:\n");
    printf("  -h     :  Optional help flag that prints usage info.\n");
    printf("  -v     :  Optional verbose flag that displays trace info.\n");
    printf("  -s <s> :  Number of set index bits.\n");
    printf("  -E <E> :  Number of lines per set.\n");
    printf("  -b <b> :  Number of block offset bits.\n");
    printf("  -t <tracefile> :  Name of the valgrindtrace to replay.\n");
}

void cacheinit(cache* c,int s,int e,int b)
{
    c->s = s;
    c->e = e;
    c->b = b;
    c->sets = (set*)malloc(sizeof(set)*(1<<s));
    for(int i=0;i<(1<<s);++i)
    {
        c->sets[i].e = e;
        c->sets[i].lines = (line*)malloc(sizeof(line)*e);
        for(int j=0;j<e;++j)
        {
            c->sets[i].lines[j].valid = false;
            c->sets[i].lines[j].tag = 0;
            c->sets[i].lines[j].time = 0;
        }
    }
}

void cachefree(cache* c)
{
    for(int i=0;i<c->s;++i)
    {
        free(c->sets[i].lines);
    }
    free(c->sets);
}

operator opinit(FILE* fp)
{
    char tmp[128];
    operator tmpop={0,0,0};
    if(fgets(tmp,128,fp)!=NULL)
    {
        sscanf(tmp,"\n%c %p,%d",&tmpop.op,&tmpop.addr,&tmpop.size);
    }
    return tmpop;
}

static inline unsigned long getset(unsigned long addr,int s,int b)
{
    return (addr>>b)&((1<<s)-1);
    //return (addr>>b)%((1<<s));
}

static inline unsigned long gettag(unsigned long addr,int s,int b)
{
    return addr>>(s+b);
}

line* matchline(set s,int tag)
{
    for(int i=0;i<s.e;++i)
    {
        if(s.lines[i].valid&&s.lines[i].tag==tag)
        {
            return s.lines+i;
        }
    }
    return NULL;
}

line* getemptyline(set s)
{
    //printf("s.e:%d\n",s.e);
    for(int i=0;i<s.e;++i)
    {
        if(!s.lines[i].valid)
        {
            return s.lines+i;
        }
    }
    return NULL;
}

line* getlru(set s)
{
    line* lru = s.lines;
    for(int i=0;i<s.e;++i)
    {
        if(s.lines[i].time<lru->time)
        {
            lru = s.lines+i;
        }
    }
    return lru;
}

void LS(cache* c,operator op,bool v,bool flag)
{
    unsigned long setindex = getset(op.addr,c->s,c->b);
    unsigned long tag = gettag(op.addr,c->s,c->b);
    //printf("setindex %ld,tag %ld ",setindex,tag);
    set* s = c->sets+setindex;
    line* l = matchline(*s,tag);
    if(v&&flag)
    {
        printf("%c %p,%d ",op.op,op.addr,op.size);
    }
    if(l!=NULL)
    {
        ++hits;
        if(v)
        {
            printf("hit ");
        }
    }
    else 
    {
        ++misses;
        if(v)
        {
            printf("miss ");
        }
        l = getemptyline(*s);
        if(l==NULL)
        {
            ++evictions;
            if(v)
            {
                printf("eviction ");
            }
            l = getlru(*s);
        }
        else 
        {
            l->valid=true;
        }
        l->tag = tag;
    }
    l->time = time++;
    if(v&&flag)
    {
        printf("\n");
    }
}

void M(cache* c,operator op,bool v)
{
    if(v) 
    {
        printf("%c %p,%d ",op.op,op.addr,op.size);
    }
    op.op='L';
    LS(c,op,v,false);
    op.op='S';
    LS(c,op,v,false);
    if(v)
    {
        printf("\n");
    }
}

void printSummary(int hits,int misses,int evictions)
{
    printf("hits:%d misses:%d evictions:%d\n",hits,misses,evictions);
}


int main(int argc, char **argv)
{
    char* path=NULL;
    bool v=false;
    int s = 0, e = 0, b = 0;
    for (int i=0; i< argc;++i)
    {
        if(strcmp(argv[i],"-h")==0)
        {
            helpinfos();
            return 0;
        }
    }
    for (int i=0; i< argc;++i)
    {
        if(strcmp(argv[i],"-v")==0)
        {
            v=true;
        }
    }
    for (int i=0; i< argc;++i)
    {
        if(strcmp(argv[i],"-s")==0)
        {
            s = atoi(argv[i+1]);
        }
    }
    for (int i=0; i< argc;++i)
    {
        if(strcmp(argv[i],"-E")==0)
        {
            e = atoi(argv[i+1]);
        }
    }
    for (int i=0; i< argc;++i)
    {
        if(strcmp(argv[i],"-b")==0)
        {
            b = atoi(argv[i+1]);
        }
    }
    for (int i=0; i< argc;++i)
    {
        if(strcmp(argv[i],"-t")==0)
        {
            path = argv[i+1];
        }
    }
    if(s==0||e==0||b==0||path==NULL)
    {
        printf("error: missing required command line argument\n");
        helpinfos();
        return 0;
    }
    cache c;
    cacheinit(&c,s,e,b);
    FILE* fp = fopen(path,"r");
    if(fp==NULL)
    {
        printf("error: trace file open failed\n");
        return 0;
    }
    operator curop;
    while((curop=opinit(fp)).op!=0)
    {
        if(curop.op=='I')
        {
            continue;
        }
        else if(curop.op=='L'||curop.op=='S')
        {
            //printf("L %p,%d",curop.addr,curop.size);
            //printf("getop");
            LS(&c,curop,v,true);
        }
        else if(curop.op=='M')
        {
            //printf("M %p,%d",curop.addr,curop.size);
            M(&c,curop,v);
        }
    }
    fclose(fp);
    cachefree(&c);
    printSummary(hits,misses,evictions);


    return 0;
}
