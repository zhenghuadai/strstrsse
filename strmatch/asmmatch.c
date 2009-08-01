#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include "match.h"
#include "util.h"
#include "time.h"
#include "stdio.h"
int main(int argc,char *argv[])
{
 /*  读入目标串和模式串 初始化 */ 
 int i,j;
 char *subjfname,*quryfname;
time_t   start, finish;
double elapsed_time;
void (* matchalg[20])(char * text,char * pat,int kerrs);
char * matchalgstr[20];
int boolmatch[20],kerrs=2;
FILE *fp;
//FILE *fp;
_U64 startrdt,endrdt;
for(i=0;i<20;i++)
	matchalg[i]=NULL;
matchalg[0]=Ady;
matchalgstr[16]="Ady";
for(i=0;i<18;i++)
{
	boolmatch[i]=1;
}
if((fp=fopen("boolmatch","r"))==NULL)
{
	printf("err");
	exit(0);
}
for(i=0;i<18;i++)
	fscanf(fp,"%d",&boolmatch[i]);

fclose(fp);
//Pat="Natasha";
/*
if(argc==1)
{
quryfname="input/pattern";
subjfname="input/subject";
}
else
{
quryfname=argv[2];
subjfname=argv[1];
}

Pat=Getsubjectfromfile(quryfname);
Text=Getsubjectfromfile(subjfname);i*/
/*fp=fopen("sub","w");
fprintf(fp,"%s",Text);
fclose(fp);
printf("%s\n",Pat);*/
Pat="ncinc";
 Text="Till today, the lantern ncinchpc  festival is Natashastill held each year ncinchpc around the country. Lanterns of various shapes and sizes ncinchpc are hung in the streets, attracting countless visitors. Children will hold self-made or bought lanterns to stroll with on the streets, extremely excite";
occurnum=0;
 /* 调用串匹配函数 */
//time( &start );
/*
Mtime(&startrdt);
//for(i=0;i<1;i++)
{
printf("bf:\n");
    	Sbf(Text,Pat);
printf("mp:\n");
 Smp(Text,Pat);
printf("kmp:\n");
 Skmp(Text,Pat);
printf("bm:\n");
 Sbm(Text,Pat);
printf("bmh:\n");
 Sbmh(Text,Pat);
printf("bmhs:\n");
 Sbmhs(Text,Pat);
printf("smith:\n");
 Ssmith(Text,Pat);
printf("dfa:\n");
Sdfa(Text,Pat);
printf("bdm:\n");
   Sbdm(Text,Pat);
printf("byh:\n");
 Sbyh(Text,Pat);
printf("kr:\n");
   Skr(Text,Pat);
printf("skip:\n");
   Sskip(Text,Pat);
printf("kmpskip:\n");
   Skmpskip(Text,Pat);
printf("shiftor:\n");
    Sshiftor(Text,Pat);
printf("\n");
 }
Mtime(&endrdt);*/
//time( &finish );
 //elapsed_time= difftime( finish, start );
if((fp=fopen("result","a"))==NULL)
{
	printf("open result file err");
	exit(0);
}
fprintf(fp,"***********************************************\n");
fprintf(fp,"length of Text:%d\nlength of pattern:%d\n ",strlen(Text),strlen(Pat));
for(i=0;i<18;i++)
{   
	if(matchalg[i]&&boolmatch[i])
	{
	Mtime(&startrdt);
	matchalg[i](Text,Pat,kerrs);
	Mtime(&endrdt);
	elapsed_time =Mdifftime(startrdt,endrdt);
	printf("algorithm %s takes\n %20.15f seconds.\n",matchalgstr[i], elapsed_time );
	fprintf(fp,"%20.15f seconds:algorithm %s takes \n ", elapsed_time, matchalgstr[i]);
	
	}
	
}//end for
fclose(fp);

/* 输出结果 */ 

for(i=0;i<occurnum;i++)
   printf("%d,",occurrenceint[i]);
//printf("\nalgorithm takes %6.2f seconds.\n", elapsed_time );
// elapsed_time =Mdifftime(startrdt,endrdt);
//printf("\nalgorithm takes %20.15f seconds.\n", elapsed_time );

}
