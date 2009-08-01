#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include "match.h"
#include "global.h"
#include "time.h"
#include "stdio.h"
int main(int argc,char *argv[])
{
 /*  读入目标串和模式串 初始化 */ 
 int i,j;
 char *subjfname,*quryfname;
time_t   start, finish;
double elapsed_time;
void (* matchalg[20])(char * text,char * pat);
void (* matchalg2[20])(char * text,char * pat,int n, int m);
char * matchalgstr[20];
int boolmatch[20];
FILE *fp;
//FILE *fp;
_U64 startrdt,endrdt;
for(i=0;i<20;i++)
	matchalg[i]=NULL;
matchalg[0]=bfstr;
matchalg2[0]=bfstr2;
matchalgstr[0]="bfstr";
matchalg[1]=Sbm;
matchalg2[1]=Sbm2;
matchalgstr[1]="Sbm";
matchalg[2]=Sbmh;
matchalg2[2]=Sbmh2;
matchalgstr[2]="Sbmh";
matchalg[3]=Sbmhs;
matchalg2[3]=Sbmhs2;
matchalgstr[3]="Sbmhs";
matchalg[4]=Ssmith;
matchalg2[4]=Ssmith2;
matchalgstr[4]="Ssmith";
matchalg[5]=Smp;
matchalg2[5]=Smp2;
matchalgstr[5]="Smp";
matchalg[6]=Skmp;
matchalg2[6]=Skmp2;
matchalgstr[6]="Skmp";
matchalg[7]=Sdfa;
matchalg2[7]=Sdfa2;
matchalgstr[7]="Sdfa";
matchalg[8]=Sbom;
matchalg2[8]=Sbom2;
matchalgstr[8]="Sbom";
matchalg[9]=Sbdm;
matchalg2[9]=Sbdm2;
matchalgstr[9]="Sbdm";
matchalg[10]=Sbndm;
matchalg2[10]=Sbndm2;
matchalgstr[10]="Sbndm";
matchalg[11]=Skr;
matchalg2[11]=Skr2;
matchalgstr[11]="Skr";
matchalg[12]=Sbyh;
matchalg2[12]=Sbyh2;
matchalgstr[12]="Sbyh";
matchalg[13]=Sskip;
matchalg2[13]=Sskip2;
matchalgstr[13]="Sskip";
matchalg[14]=Skmpskip;
matchalg2[14]=Skmpskip2;
matchalgstr[14]="Skmpskip";
matchalg[15]=Sshiftor;
matchalg2[15]=Sshiftor2;
matchalgstr[15]="Sshiftor";
matchalg[16]=Sshiftand;
matchalg2[16]=Sshiftand2;
matchalgstr[16]="Sshiftand";
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
if(argc==1)
{
	printf("match subj qury\n");
subjfname="sub";
quryfname="pattern";
}
else
{
quryfname=argv[2];
subjfname=argv[1];
}

Pat=Getsubjectfromfile(quryfname);
Text=Getsubjectfromfile(subjfname);
/*fp=fopen("sub","w");
fprintf(fp,"%s",Text);
fclose(fp);
printf("%s\n",Pat);*/
//Pat="ncinc";
// Text="Till today, the lantern ncinchpc  festival is Natashastill held each year ncinchpc around the country. Lanterns of various shapes and sizes ncinchpc are hung in the streets, attracting countless visitors. Children will hold self-made or bought lanterns to stroll with on the streets, extremely excite";
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
	int n, m;
	n = strlen(Text);
	m = strlen(Pat);
	Mtime(&startrdt);
	//matchalg[i](Text,Pat);
	matchalg2[i](Text,Pat, n, m);
	
	Mtime(&endrdt);
	elapsed_time =Mdifftime(startrdt,endrdt);
	printf("algorithm %10s takes %20.15f clocks.\n",matchalgstr[i], elapsed_time );
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
