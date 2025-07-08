#define memsize 40000000
#define varsize 8192
#define bdds 1
#define bufsize 100 \

/*1:*/
#line 28 "zddread.w"

#include <stdio.h> 
#include <stdlib.h> 
typedef struct{
int v;
int lo;
int hi;
int mark;
}node;
int present[varsize];
#line 11 "zddread-minsols-short.ch"
node*mem[bdds];
int stack[varsize];
int stackptr;
int serial;
#line 39 "zddread.w"
int root[bdds];
FILE*infile;
char buf[bufsize];
unsigned int i1,i2,i3,i4;
int memmax;
/*2:*/
#line 30 "zddread-minsols-short.ch"

void prep(int p){
register int q,lomark,himark;
q= mem[0][p].lo,lomark= varsize+2;
if(q){
if(mem[0][q].mark==0)prep(q);
lomark= mem[0][q].mark;
}
q= mem[0][p].hi,himark= varsize+2;
if(q){
if(mem[0][q].mark==0)prep(q);
himark= mem[0][q].mark+1;
}
if(lomark> himark)mem[0][p].lo= 0,mem[0][p].mark= himark;
else if(lomark<himark)mem[0][p].hi= 0,mem[0][p].mark= lomark;
else mem[0][p].mark= lomark;
}

/*:2*//*3:*/
#line 50 "zddread-minsols-short.ch"

void printpaths(int p){
register int q,s= stackptr;
if(p<=1){
if(serial){
printf(" and more...\n");
exit(0);
}else{
serial= 1;
for(q= 0;q<stackptr;q++)printf(" %d",stack[q]);
printf(" (length %d)\n",stackptr);
}
return;
}
q= mem[0][p].hi;
if(q){
stack[stackptr++]= mem[0][p].v;
printpaths(q);
}
q= mem[0][p].lo;
if(q){
printpaths(q);
}
stackptr= s;
}

/*:3*/
#line 44 "zddread.w"


int
main(int argc,char*argv[]){
register int j,k,r,minv;
for(r= 0;r<bdds;r++){
mem[r]= (node*)malloc(memsize*sizeof(node));
if(!mem[r]){
printf("Sorry, I can't allocate mem[%d]!\n",r);
exit(-99);
}
#line 19 "zddread-minsols-short.ch"
for(k= 0;k<memsize;k++)mem[r][k].lo= mem[r][k].hi= mem[r][k].mark= 0;
#line 56 "zddread.w"
if(!(infile= fopen(argv[r+1],"r"))){
printf("Sorry, I can't open `%s' for reading!\n",argv[r+1]);
exit(-1);
}
for(k= 0,minv= varsize;;){
if(!fgets(buf,bufsize,infile))break;
j= sscanf(buf,"%x: (~%u?%x:%x)\n",&i1,&i2,&i3,&i4);
if(j!=4)
printf("! I got only %d inputs from the line %s",j,buf);
else{
if(i1> memmax)memmax= i1;
if(i3> memmax)memmax= i3;
if(i4> memmax)memmax= i4;
if(i1>=memsize||i2>=varsize||i3>=memsize||i4>=memsize){
printf("! address out of range in the line %s",buf);
exit(-69);
}else if(mem[r][i1].lo||mem[r][i1].hi)
printf("! clobbered node in the line %s",buf);
else{
if(i2<minv)minv= i2,root[r]= i1;
k++,mem[r][i1].v= i2,mem[r][i1].lo= i3,mem[r][i1].hi= i4;
present[i2]= 1;
}
}
}
fprintf(stderr,"%d nodes input into mem%d\n",k,r);
fprintf(stderr,"(memmax=%d)\n",memmax);
}
for(j= k= 0;j<varsize;j++)if(present[j])k++;
fprintf(stderr,"There are %d variables.\n",k);
/*4:*/
#line 76 "zddread-minsols-short.ch"

mem[0][1].mark= 1,mem[0][1].v= varsize;
prep(root[0]);
printpaths(root[0]);
#line 92 "zddread.w"

/*:4*/
#line 86 "zddread.w"
;
}

#line 26 "zddread-minsols-short.ch"
/*:1*/
