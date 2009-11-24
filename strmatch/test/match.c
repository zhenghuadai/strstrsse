#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include "match.h"
#include "global.h"
#include "time.h"
#include "stdio.h"
#define ALLALG 20 
#include "strstrsse.h"
#include "../../rdtsc.h"
typedef struct matchtest_
{
	void (* matchalg)(char * text,char * pat);
	void (* matchalg2)(char * text,char * pat,int n, int m);
	char * matchalgstr;
	int boolmatch;
} matchTest;
int main(int argc,char *argv[])
{
	/*  读入目标串和模式串 初始化 */ 
	int i,j;
	char *subjfname=0,*quryfname=0;
	time_t   start, finish;
	double elapsed_time;
	int n, m;
	//void (* matchalg[20])(char * text,char * pat);
	//void (* matchalg2[20])(char * text,char * pat,int n, int m);
	//char * matchalgstr[20]={0};
	//int boolmatch[20];
	matchTest match[20];
	double time_used[20];
	FILE *fp;
	int verbose = 0;
	//FILE *fp;
	_U64 startrdt,endrdt;
	for(i=0;i<20;i++)
	{
		//matchalg[i]=NULL;
		//matchalg2[i]=NULL;
		match[i].matchalg = NULL;
		match[i].matchalg2= NULL;
	}
	match[0]. matchalg	 	=bfstr; 
	match[0]. matchalg2	 	=bfstr2;
	match[0]. matchalgstr 	="bfstr";
	match[1]. matchalg	 	=Sbm;
	match[1]. matchalg2		=Sbm2;
	match[1]. matchalgstr	="Sbm";
	match[2]. matchalg	 	=Sbmh;
	match[2]. matchalg2	 	=Sbmh2;
	match[2]. matchalgstr	="Sbmh";
	match[3]. matchalg		=Sbmhs;
	match[3]. matchalg2		=Sbmhs2;
	match[3]. matchalgstr	="Sbmhs";
	match[4]. matchalg	 	=Ssmith;
	match[4]. matchalg2	 	=Ssmith2;
	match[4]. matchalgstr	="Ssmith";
	match[5]. matchalg		=Smp;
	match[5]. matchalg2	 	=Smp2;
	match[5]. matchalgstr	="Smp";
	match[6]. matchalg	 	=Skmp;
	match[6]. matchalg2	 	=Skmp2;
	match[6]. matchalgstr	="Skmp";
	match[7]. matchalg	 	=Sdfa;
	match[7]. matchalg2		=Sdfa2;
	match[7]. matchalgstr	="Sdfa";
	match[8]. matchalg	 	=Sbom;
	match[8]. matchalg2		 =Sbom2;
	match[8]. matchalgstr	="Sbom";
	match[9]. matchalg		=Sbdm;
	match[9]. matchalg2		=Sbdm2;
	match[9]. matchalgstr	="Sbdm";
	match[10].matchalg		=Sbndm;
	match[10].matchalg2		=Sbndm2;
	match[10].matchalgstr	="Sbndm";
	match[11].matchalg		=Skr;
	match[11].matchalg2		=Skr2;
	match[11].matchalgstr	="Skr";
	match[12].matchalg		=Sbyh;
	match[12].matchalg2		=Sbyh2;
	match[12].matchalgstr	="Sbyh";
	match[13].matchalg		=0;//Sskip;
	match[13].matchalg2		=0 ;// Sskip2;
	match[13].matchalgstr	="Sskip";
	match[14].matchalg		=Skmpskip;
	match[14].matchalg2		=Skmpskip2;
	match[14].matchalgstr	="Skmpskip";
	match[15].matchalg		=Sshiftor;
	match[15].matchalg2		=Sshiftor2;
	match[15].matchalgstr	="Sshiftor";
	match[16].matchalg		=Sshiftand;
	match[16].matchalg2		=Sshiftand2;
	match[16].matchalgstr	="Sshiftand";
	match[17].matchalg		=SshiftorW;
	match[17].matchalg2		=SshiftorW2;
	match[17].matchalgstr	="SshiftorW";
	match[18].matchalg		=lstrstrsse;
	match[18].matchalg2		=0;
	match[18].matchalgstr	="lstrstrsse";
	for(i=0;i<ALLALG;i++)
	{
		match[i].boolmatch=1;
	}
	if((fp=fopen("boolmatch","r"))==NULL)
	{
		printf("err");
		exit(0);
	}
	{
		for(i=0;i<18;i++)
		{
			char buf[128];
			char* ret =fgets(buf, 128,fp);
			if(ret ==NULL) break;
			sscanf(buf,"%d", &(match[i].boolmatch));
		}
	}
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
		int i;
		for(i=0;i<argc;i++){
			if(argv[i][0] == '-'){
				switch(argv[i][1]){
					case 't':
						subjfname=argv[i+1];
						break;
					case 'q':
						quryfname=argv[i+1];
						break;
					case 'a':
						Pat=argv[i+1];
						break;
					case 'v':
						verbose = atoi(argv[i+1]);
						break;
				}
			}
		}
	}


	if(verbose ==0)
		setReportFunc(SEARCH_SILENT);
	else 
		setReportFunc(SEARCH_ALL);

	if(quryfname !=NULL)
		Pat=Getsubjectfromfile(quryfname);
	Text=Getsubjectfromfile(subjfname);
	n = strlen(Text);
	m = strlen(Pat);

	if(Pat[m-1] == '\n') Pat[m-1]=0;

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
	if((fp=fopen("result","w"))==NULL)
	{
		printf("open result file err");
		exit(0);
	}
	fprintf(fp,"***********************************************\n");
	fprintf(fp,"length of Text:%d\nlength of pattern:%d\n ",strlen(Text),strlen(Pat));
	fprintf(stdout,"length of Text:%d\nlength of pattern:%d %s\n ",strlen(Text),strlen(Pat),Pat);
	printf("alg2\n");
	for(i=0;i<ALLALG;i++)
	{   
		if(match[i].matchalg2 && match[i].boolmatch)
		{
			mdtime(0);
			//Mtime(&startrdt);
			//matchalg[i](Text,Pat);
			match[i].matchalg2(Text,Pat, n, m);

			//Mtime(&endrdt);
			//elapsed_time =Mdifftime(startrdt,endrdt);
			elapsed_time=mdtime(1);
			time_used[i] = elapsed_time;
			printf("algorithm %10s takes %20f clocks.\n",match[i].matchalgstr, elapsed_time );
			fprintf(fp,"%20.15f seconds:algorithm %s takes \n ", elapsed_time, match[i].matchalgstr);

		}

	}//end for

	printf("alg\n");
	for(i=0;i<ALLALG;i++)
	{   
		if(match[i].matchalg&& match[i].boolmatch)
		{
			mdtime(0);
			//Mtime(&startrdt);
			//matchalg[i](Text,Pat);
			match[i].matchalg(Text,Pat);

			//Mtime(&endrdt);
			//elapsed_time =Mdifftime(startrdt,endrdt);
			elapsed_time=mdtime(1);
			if(i>16)
			time_used[i] = elapsed_time;
			printf("algorithm %10s takes %20f clocks.\n",match[i].matchalgstr, elapsed_time );
			fprintf(fp,"%20.15f seconds:algorithm %s takes \n ", elapsed_time, match[i].matchalgstr);
		}

	}//end for

	fclose(fp);

	printf("speedup to bfStr:%f\n", time_used[0] / time_used[18]);
	printf("speedup to bmStr:%f\n", time_used[1] / time_used[18]);

	/* 输出结果 */ 

	for(i=0;i<occurnum;i++)
		printf("%d,",occurrenceint[i]);
	//printf("\nalgorithm takes %6.2f seconds.\n", elapsed_time );
	// elapsed_time =Mdifftime(startrdt,endrdt);
	//printf("\nalgorithm takes %20.15f seconds.\n", elapsed_time );

}
