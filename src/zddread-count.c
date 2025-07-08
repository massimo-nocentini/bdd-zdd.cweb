#define memsize 40000000
#define varsize 8192
#define bdds 1
#define bufsize 100

#define ten_to_18th 1000000000000000000

/*1:*/
#line 28 "zddread.w"

#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int v;
    int lo;
    int hi;
    int mark;
} node;
int present[varsize];
#line 9 "zddread-count.ch"
node *mem[bdds];
typedef struct
{
    long long c2, c1;
} dlong;
dlong dlong0 = {0, 0};
dlong dlong1 = {0, 1};
dlong count[memsize];
#line 39 "zddread.w"
int root[bdds];
FILE *infile;
char buf[bufsize];
unsigned int i1, i2, i3, i4;
int memmax;
/*2:*/
#line 28 "zddread-count.ch"

dlong dadd(dlong x, dlong y)
{
    dlong z;
    z.c1 = x.c1 + y.c1;
    if (z.c1 > ten_to_18th)
        z.c1 -= ten_to_18th, z.c2 = x.c2 + y.c2 + 1;
    else
        z.c2 = x.c2 + y.c2;
    if (z.c2 > ten_to_18th)
    {
        fprintf(stderr, "Possible integer overflow!\n");
        printf("Possible integer overflow!\n");
        exit(-666);
    }
    return z;
}
void print_dlong(FILE *f, dlong x)
{
    if (x.c2)
        fprintf(f, "%lld%018lld", x.c2, x.c1);
    else
        printf("%lld", x.c1);
}

/*:2*/ /*3:*/
#line 48 "zddread-count.ch"

void countsols(int p)
{
    register int q;
    dlong c = dlong0;
    q = mem[0][p].lo;
    if (q)
    {
        if (mem[0][q].mark == 0)
            countsols(q);
        c = count[q];
    }
    q = mem[0][p].hi;
    if (q)
    {
        if (mem[0][q].mark == 0)
            countsols(q);
        c = dadd(c, count[q]);
    }
    mem[0][p].mark = 1;
    count[p] = c;
}

/*:3*/
#line 44 "zddread.w"

int main(int argc, char *argv[])
{
    register int j, k, r, minv;
    for (r = 0; r < bdds; r++)
    {
        mem[r] = (node *)malloc(memsize * sizeof(node));
        if (!mem[r])
        {
            printf("Sorry, I can't allocate mem[%d]!\n", r);
            exit(-99);
        }
        for (k = 0; k < memsize; k++)
            mem[r][k].lo = mem[r][k].hi = 0;
        if (!(infile = fopen(argv[r + 1], "r")))
        {
            printf("Sorry, I can't open `%s' for reading!\n", argv[r + 1]);
            exit(-1);
        }
        for (k = 0, minv = varsize;;)
        {
            if (!fgets(buf, bufsize, infile))
                break;
            j = sscanf(buf, "%x: (~%u?%x:%x)\n", &i1, &i2, &i3, &i4);
            if (j != 4)
                printf("! I got only %d inputs from the line %s", j, buf);
            else
            {
                if (i1 > memmax)
                    memmax = i1;
                if (i3 > memmax)
                    memmax = i3;
                if (i4 > memmax)
                    memmax = i4;
                if (i1 >= memsize || i2 >= varsize || i3 >= memsize || i4 >= memsize)
                {
                    printf("! address out of range in the line %s", buf);
                    exit(-69);
                }
                else if (mem[r][i1].lo || mem[r][i1].hi)
                    printf("! clobbered node in the line %s", buf);
                else
                {
                    if (i2 < minv)
                        minv = i2, root[r] = i1;
                    k++, mem[r][i1].v = i2, mem[r][i1].lo = i3, mem[r][i1].hi = i4;
                    present[i2] = 1;
                }
            }
        }
        fprintf(stderr, "%d nodes input into mem%d\n", k, r);
        fprintf(stderr, "(memmax=%d)\n", memmax);
    }
    for (j = k = 0; j < varsize; j++)
        if (present[j])
            k++;
    fprintf(stderr, "There are %d variables.\n", k);
/*4:*/
#line 66 "zddread-count.ch"

    count[1] = dlong1, mem[0][1].mark = 1, mem[0][1].v = varsize;
    countsols(root[0]);
    print_dlong(stdout, count[root[0]]);
    printf(" solutions.\n");
#line 92 "zddread.w"

/*:4*/
#line 86 "zddread.w"
    ;
}

#line 22 "zddread-count.ch"
/*:1*/
