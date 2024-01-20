#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"

int hits = 0, misses = 0, evictions = 0;

struct line
{
    bool valid;
    int tag;
    int time;
};

typedef struct line line;

struct set
{
    line *lines;
    int e;
};

typedef struct set set;
struct cache
{
    int s;
    int e;
    int b;
    set *sets;
};
typedef struct cache cache;

struct operator
{
    char op;
    uintptr_t addr;
    int size;
};
typedef struct operator operator;

void helpinfos()
{
    puts("Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>");
    puts("Options:");
    puts("  -h     :  Optional help flag that prints usage info.");
    puts("  -v     :  Optional verbose flag that displays trace info.");
    puts("  -s <s> :  Number of set index bits.");
    puts("  -E <E> :  Number of lines per set.");
    puts("  -b <b> :  Number of block offset bits.");
    puts("  -t <tracefile> :  Name of the valgrindtrace to replay.");
    return;
}

void cacheinit(cache *c, int s, int e, int b)
{
    c->s = s;
    c->e = e;
    c->b = b;
    c->sets = (set *)malloc(sizeof(set) * (1 << s));
    for (int i = 0; i < (1 << s); ++i)
    {
        c->sets[i].e = e;
        c->sets[i].lines = (line *)malloc(sizeof(line) * e);
        for (int j = 0; j < e; ++j)
        {
            c->sets[i].lines[j].valid = false;
            c->sets[i].lines[j].tag = 0;
            c->sets[i].lines[j].time = 0;
        }
    }
}

operator opinit(FILE *fp)
{
    char tmp[128];
    operator tmpop = {0, 0, 0};
    if (fgets(tmp, 128, fp) != NULL)
    {
        sscanf(tmp, "\n%c %lx,%d", &tmpop.op, &tmpop.addr, &tmpop.size);
    }
    return tmpop;
}

int main(int argc, char *argv[])
{
    char *path = NULL;
    int s = 0, e = 0, b = 0;
    bool v = false;
    for (int i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            helpinfos();
            return 0;
        }
    }
    for (int i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], "-v") == 0)
        {
            v = true;
        }
    }
    for (int i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], "-s") == 0)
        {
            s = atoi(argv[i + 1]);
        }
    }
    for (int i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], "-E") == 0)
        {
            e = atoi(argv[i + 1]);
        }
    }
    for (int i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], "-b") == 0)
        {
            b = atoi(argv[i + 1]);
        }
    }
    for (int i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], "-t") == 0)
        {
            path = argv[i + 1];
        }
    }
    if (s == 0 || e == 0 || b == 0 || path == NULL)
    {
        puts("Missing required command line argument");
        helpinfos();
        return 0;
    }
    cache c;
    operator curop,op;
    cacheinit(&c, s, e, b);
    FILE *fp = fopen(path, "r");
    if (fp)
    {
        while (1)
        {
            curop = opinit(fp);
            if (!curop.op)
                break;
            if (curop.op != 73)
            {
                if (curop.op == 76 || curop.op == 83)
                {
                    op = curop;
                    LS(&c, &op, v, 1);
                }
                else if (curop.op == 77)
                {
                    op = curop;
                    M(&c, &op, v);
                }
            }
        }
        fclose(fp);
        cachefree(&c);
        printSummary(hits, misses, evictions);
        return 0;
    }
}