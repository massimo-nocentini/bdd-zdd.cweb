#define memsize 40000000
#define varsize 8192
#define bdds 1
#define gfsize 85000000
#define bufsize 100 \

#define ten_to_18th 1000000000000000000 \

#define gfx(j) gf[j].u \

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
#line 21 "zddread-gf.ch"
node*mem[bdds];
typedef struct{
long long u,l;
}dlong;
dlong dlong0= {0,0};
dlong dlong1= {0,1};
dlong*gf;
int gfptr;
dlong acc1[varsize+1],acc2[varsize+1];
#line 39 "zddread.w"
int root[bdds];
FILE*infile;
char buf[bufsize];
unsigned int i1,i2,i3,i4;
int memmax;
/*2:*/
#line 52 "zddread-gf.ch"

dlong dadd(dlong x,dlong y){
dlong z;
z.l= x.l+y.l;
if(z.l> ten_to_18th)z.l-= ten_to_18th,z.u= x.u+y.u+1;
else z.u= x.u+y.u;
if(z.u> ten_to_18th){
fprintf(stderr,"Possible integer overflow!\n");
printf("Possible integer overflow!\n");
exit(-666);
}
return z;
}
void print_dlong(FILE*f,dlong x){
if(x.u)fprintf(f,"%lld%018lld",x.u,x.l);
else printf("%lld",x.l);
}

/*:2*//*3:*/
#line 72 "zddread-gf.ch"

void findgf(int p){
register int k,q;
int c= 0,cc= 0,ccc,kk,d,dd,l;
q= mem[0][p].lo;
if(q){
if(mem[0][q].mark==0)findgf(q);
c= mem[0][q].mark;
}
q= mem[0][p].hi;
if(q){
if(mem[0][q].mark==0)findgf(q);
cc= mem[0][q].mark;
}else{
fprintf(stderr,"This isn't a ZDD!\n");
exit(-66);
}
/*4:*/
#line 98 "zddread-gf.ch"

if(gfptr+varsize>=gfsize){
fprintf(stderr,"Memory overflow (gfsize=%d)!\n",gfsize);
exit(-97);
}
ccc= gfptr+1;
if(c==0){
while(gfx(cc)>=0)gf[++gfptr]= gf[cc++];
gfx(++gfptr)= gfx(cc)-1;
}else{
for(k= 0;gfx(c+k)>=0;k++)acc1[k]= gf[c+k];
d= k,c= -1-gfx(c+k);
for(k= 0;gfx(cc+k)>=0;k++)acc2[k]= gf[cc+k];
dd= k,cc= -gfx(cc+k);
l= (c<cc?c:cc);
for(k= kk= 0;k<d||kk<dd;){
if(c<cc){
if(k<d)gf[++gfptr]= acc1[k++],c++;
else gf[++gfptr]= dlong0,c++;
}else if(c> cc){
if(kk<dd)gf[++gfptr]= acc2[kk++],cc++;
else gf[++gfptr]= dlong0,cc++;
}else if(k==d)gf[++gfptr]= acc2[kk++];
else if(kk==dd)gf[++gfptr]= acc1[k++];
else{
gf[++gfptr]= dadd(acc1[k++],acc2[kk++]);
}
}
gfx(++gfptr)= -1-l;
}

/*:4*/
#line 89 "zddread-gf.ch"
;
mem[0][p].mark= ccc;
}

/*:3*/
#line 44 "zddread.w"


int
main(int argc,char*argv[]){
#line 34 "zddread-gf.ch"
register int j,k,r,minv;
gf= (dlong*)malloc(gfsize*sizeof(dlong));
if(!gf){
printf("Sorry, I can't allocate %d dlongs for the gf array!\n",gfsize);
exit(-98);
}
#line 49 "zddread.w"
for(r= 0;r<bdds;r++){
mem[r]= (node*)malloc(memsize*sizeof(node));
if(!mem[r]){
printf("Sorry, I can't allocate mem[%d]!\n",r);
exit(-99);
}
for(k= 0;k<memsize;k++)mem[r][k].lo= mem[r][k].hi= 0;
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
/*5:*/
#line 129 "zddread-gf.ch"

gf[1]= dlong1,gfx(2)= -1,gfptr= 2;
mem[0][1].mark= 1,mem[0][1].v= varsize;
findgf(root[0]);
printf("The generating function coefficients are");
for(k= mem[0][root[0]].mark;gfx(k)>=0;k++){
printf(" ");
print_dlong(stdout,gf[k]);
}
printf(" (* z^%lld..z^%lld).\n",-1-gfx(k),k-mem[0][root[0]].mark-2-gfx(k));
#line 92 "zddread.w"

/*:5*/
#line 86 "zddread.w"
;
}

#line 46 "zddread-gf.ch"
/*:1*/
