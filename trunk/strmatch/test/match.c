/**
 * =====================================================================================
 *       @file    match.c
 *
 *       @brief   test the performance of the string matching algorithms.
 *
 *       @author  DAI ZHENGHUA (), djx.zhenghua@gmail.com
 *       @version 1.0
 *       @date    01/02/2011 02:53:25 PM
 *
 *       Revision none
 *       Compiler gcc
 *       Company  
 * =====================================================================================
 */
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include "match.h"
#include "global.h"
#include "time.h"
#include "stdio.h"
#define ALLALG 30 
#include "strstrsse.h"
#include "rdtsc.h"
char* lstrstrsseLong(const char* text, const char* pat);// gcc 
char * GetgenefromfileU(char *pfname);
int isFastaFile(char* fn);
typedef struct matchtest_
{
    char* (* matchalg)(char * text,char * pat);
    char* (* matchalg2)(char * text,char * pat,int n, int m);
    char * matchalgstr;
    int boolmatch;
} matchTest;
int main(int argc,char *argv[])
{
    /*  读入目标串和模式串 初始化 */ 
    int i;
    char *subjfname=0,*quryfname=0;
//    time_t   start, finish;
    double elapsed_time;
    int n, m;
    int isGene = 0;
    //void (* matchalg[20])(char * text,char * pat);
    //void (* matchalg2[20])(char * text,char * pat,int n, int m);
    //char * matchalgstr[20]={0};
    //int boolmatch[20];
    matchTest match[ALLALG ];
    double time_used[ALLALG ];
    FILE *fp;
    int verbose = 0;
    //FILE *fp;
//    _U64 startrdt,endrdt;
    if(argc==1)
    {
        printf("match [-t text_file|-s text] [-a pattern| -q pattern_file] -v n\n");
        printf("search pattern in text_file or text\n");
        printf("-t text_file       :text_file is the text file in which you want to search  \n");
        printf("-s text            :text is the text in which you want to search  \n");
        printf("-q pattern_file    :pattern_file contains the pattern  which you want to search  \n");
        printf("-a pattern         :pattern is which you want to search  \n");
        printf("-v n  \n");
        printf("   n is 0: the reporter does nothing  \n");
        printf("   n is 1: the reporter print the matching position\n");
		printf("for example: match -s helloworld -a llo -v 1\n");
		printf("for example: match -t helloworld.txt -a llo -v 1\n");
        exit(0);
        //subjfname="sub";
        //quryfname="pattern";
    }
    else
    {
        int i;
        for(i=0;i<argc;i++){
            if(argv[i][0] == '-'){
                switch(argv[i][1]){
                    case 't':
                        subjfname=argv[i+1];
                        isGene = isFastaFile(subjfname);
                        break;
                    case 'q':
                        quryfname=argv[i+1];
                        break;
                    case 'a':
                        Pat=argv[i+1];
                        break;
                    case 's': Text = argv[i+1];
                        break;
                    case 'v':
						if (i+1 < argc)
							verbose = atoi(argv[i+1]);
                        break;
                }
            }
        }
    }


    for(i=0;i<ALLALG ;i++)
    {
        //matchalg[i]=NULL;
        //matchalg2[i]=NULL;
        match[i].matchalg = NULL;
        match[i].matchalg2= NULL;
    }
    match[0]. matchalg         =bfstr; 
    match[0]. matchalg2         =bfstr2;
    match[0]. matchalgstr     ="bfstr";
    match[1]. matchalg         =Sbm;
    match[1]. matchalg2        =Sbm2;
    match[1]. matchalgstr    ="Sbm";
    match[2]. matchalg         =Sbmh;
    match[2]. matchalg2         =Sbmh2;
    match[2]. matchalgstr    ="Sbmh";
    match[3]. matchalg        =Sbmhs;
    match[3]. matchalg2        =Sbmhs2;
    match[3]. matchalgstr    ="Sbmhs";
    match[4]. matchalg         =Ssmith;
    match[4]. matchalg2         =Ssmith2;
    match[4]. matchalgstr    ="Ssmith";
    match[5]. matchalg        =Smp;
    match[5]. matchalg2         =Smp2;
    match[5]. matchalgstr    ="Smp";
    match[6]. matchalg         =Skmp;
    match[6]. matchalg2         =Skmp2;
    match[6]. matchalgstr    ="Skmp";
    match[7]. matchalg         =Sdfa;
    match[7]. matchalg2        =Sdfa2;
    match[7]. matchalgstr    ="Sdfa";
    match[8]. matchalg         =Sbom;
    match[8]. matchalg2         =Sbom2;
    match[8]. matchalgstr    ="Sbom";
    match[9]. matchalg        =Sbdm;
    match[9]. matchalg2        =Sbdm2;
    match[9]. matchalgstr    ="Sbdm";
    match[10].matchalg        =Sbndm;
    match[10].matchalg2        =Sbndm2;
    match[10].matchalgstr    ="Sbndm";
    match[11].matchalg        =Skr;
    match[11].matchalg2        =Skr2;
    match[11].matchalgstr    ="Skr";
    match[12].matchalg        =0;//Sbyh;
    match[12].matchalg2        =0;//Sbyh2;
    match[12].matchalgstr    ="Sbyh";
    match[13].matchalg        =0;//Sskip;
    match[13].matchalg2        =0 ;// Sskip2;
    match[13].matchalgstr    ="Sskip";
    match[14].matchalg        =Skmpskip;
    match[14].matchalg2        =Skmpskip2;
    match[14].matchalgstr    ="Skmpskip";
    match[15].matchalg        =Sshiftor;
    match[15].matchalg2        =Sshiftor2;
    match[15].matchalgstr    ="Sshiftor";
    match[16].matchalg        =Sshiftand;
    match[16].matchalg2        =Sshiftand2;
    match[16].matchalgstr    ="Sshiftand";
    match[17].matchalg        =SshiftorW;
    match[17].matchalg2        =SshiftorW2;
    match[17].matchalgstr    ="SshiftorW";
    match[18].matchalg        =strstrsse;
    match[18].matchalg2        =0;
    match[18].matchalgstr    ="strstrsse2";
    #ifdef TEST_2
    match[19].matchalg        =lstrstrsseLong;
    match[19].matchalg2        =0;
    match[19].matchalgstr    ="lstrstrsse2";
    match[20].matchalg        =lstrstr;
    match[20].matchalg2        =0;
    match[20].matchalgstr    ="lstrstr";
    #endif
    #ifdef SSE4
    match[21].matchalg        =strstrsse42;
    match[21].matchalg2        =0;
    match[21].matchalgstr    ="strstrsse42";

    match[22].matchalg        =strstrsse42a;
    match[22].matchalg2        =0;
    match[22].matchalgstr    ="strstrsse42a";
    #endif
   // match[22].matchalg        =strstrmmx;
   // match[22].matchalg2        =0;
   // match[22].matchalgstr    ="strstrmmx";
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

    if(quryfname !=NULL)
        Pat=Getsubjectfromfile(quryfname);
	if(subjfname!=NULL){
		if(isGene){
			Text=GetgenefromfileU(subjfname);
		}else{
			Text=Getsubjectfromfile(subjfname);
		}
	}
	n = strlen(Text);
	m = strlen(Pat);

	if(Pat[m-1] == '\n') Pat[m-1]=0;

	occurnum=0;
	if((fp=fopen("result","w"))==NULL)
	{
		printf("open result file err");
		exit(0);
	}
	fprintf(fp,"***********************************************\n");
	fprintf(fp,"length of Text:%d\nlength of pattern:%d\n ",strlen(Text),strlen(Pat));
	fprintf(stdout,"length of Text:%d\nlength of pattern:%d %s\n",strlen(Text),strlen(Pat),Pat);
	fprintf(stdout,"Text Address: %p; Pattern Address:%p\n ",Text,Pat);

	setReportFunc(SEARCH_SILENT);
	for(i=0;i<ALLALG;i++)
	{   
		if(match[i].matchalg2 && match[i].boolmatch)
			match[i].matchalg2(Text,Pat, n, m);
		if(match[i].matchalg && match[i].boolmatch)
			match[i].matchalg(Text,Pat);
	}

	if(verbose ==0)
		setReportFunc(SEARCH_SILENT);
	else if(verbose == 1) 
		setReportFunc(SEARCH_ALL);
    else 
		setReportFunc(SEARCH_FIRST);

	printf("strstr(char * text,char * pat,int n, int m): length of text and pattern are known\n");
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
			printf("algorithm %15s takes %20f clock cycles.\n",match[i].matchalgstr, elapsed_time );
			fprintf(fp,"%20.15f seconds:algorithm %s takes \n ", elapsed_time, match[i].matchalgstr);

		}

	}//end for

	printf("strstr(char * text,char * pat): text and pattern are NULL-terminated\n");
	for(i=0;i<ALLALG;i++)
	{   
		if(match[i].matchalg&& match[i].boolmatch)
		{
            char* pcur;
			mdtime(0);
			//Mtime(&startrdt);
			//matchalg[i](Text,Pat);
			pcur = match[i].matchalg(Text,Pat);

			//Mtime(&endrdt);
			//elapsed_time =Mdifftime(startrdt,endrdt);
            elapsed_time=mdtime(1);
            time_used[i] = elapsed_time;
            if(verbose ==2)
                printf("(%d)", pcur - Text);
            printf("algorithm %15s takes %20f clock cycles.\n",match[i].matchalgstr, elapsed_time );
            fprintf(fp,"%20.15f seconds:algorithm %s takes \n ", elapsed_time, match[i].matchalgstr);
        }

    }//end for

    fclose(fp);

    printf("strstrsse2   speedup to bfStr :%f\n", time_used[0] / time_used[18]);
    printf("strstrsse2   speedup to bmStr :%f\n", time_used[1] / time_used[18]);
    printf("strstrsse2   speedup to bmhStr:%f\n", time_used[2] / time_used[18]);
#ifdef SSE4
    printf("strstrsse42  speedup to bfStr :%f (released in glibc, created by intel)\n", time_used[0] / time_used[21]);
    printf("strstrsse42  speedup to bmStr :%f (released in glibc, created by intel)\n", time_used[1] / time_used[21]);
    printf("strstrsse42  speedup to bmhStr:%f (released in glibc, created by intel)\n", time_used[2] / time_used[21]);

    printf("strstrsse42a speedup to bfStr :%f\n", time_used[0] / time_used[22]);
    printf("strstrsse42a speedup to bmStr :%f\n", time_used[1] / time_used[22]);
    printf("strstrsse42a speedup to bmhStr:%f\n", time_used[2] / time_used[22]);
#endif
    /* 输出结果 */ 
    //printf("\nalgorithm takes %6.2f seconds.\n", elapsed_time );
    // elapsed_time =Mdifftime(startrdt,endrdt);
    //printf("\nalgorithm takes %20.15f seconds.\n", elapsed_time );

    return 0;
}

int isFastaFile(char* fn){
    if(fn ==NULL) return 0;
    int m = strlen(fn);
    if((fn[m-3]=='.')&&(fn[m-2]=='f')&&(fn[m-1]=='a')) return 1;
    return 0;
}

