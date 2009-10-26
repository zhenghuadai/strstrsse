#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include "match.h"
#include "global.h"
#include<stdio.h>
#include "mAc.h"
using namespace dmMatch;

static char** gPatList=0;
static char* curText = 0;

int  myreport(int patID, int idx)
{
	printf("\n-----------------------\n");
	printf("%s\n", gPatList[patID]);
	int m = strlen(gPatList[patID]);
	for(int i=1-m;i< 10;i++)
		printf("%c", curText[idx+i]);
}


int main(int argc,char *argv[])
{
    /*  读入目标串和模式串 初始化 */ 
    int i ;
    static int stats_flag=0;
    char *subjfname,*quryfname;
    double elapsed_time;
    void (* matchalg[5])(char * text,char * pat[],int num);
    char * matchalgstr[5];
    int boolmatch[5];
    FILE *fp;

    _U64 startrdt,endrdt;

    for(i=0;i<5;i++)
        matchalg[i]=NULL;
    matchalgstr[0]="ac";
    matchalgstr[1]="snortwm";
    matchalgstr[2]="ac";
    matchalgstr[3]="WM";

    Patts[0]="Natasha";
    Patts[1]="ocean";
    Patts[2]="romantic";
    Patts[3]="shape";
    Patts[4]="still";
    ps=5;
    Text="Till today, the lantern ncichpc  festival is still held each year ncichpc around the country. Lanterns of various shapes and sizes ncichpc are hung in the streets, attracting countless visitors. Children will hold self-made or bought lanterns to stroll with on the streets, extremely excite";
    if(argc==1)
    {
        quryfname="patterns";
        subjfname="sub";
    }
    else
    {
        quryfname=argv[2];
        subjfname=argv[1];
    }

    ps=Getpatternfromfile(quryfname,Patts);
    Text=Getsubjectfromfile(subjfname);

    //printf("%s\n",Pat);
    occurnum=0;
    //printf("%s,",Text);
    printf("\n");
    printf("\n%d ok\n",strlen(Text));
    /* 调用串匹配函数 */
    mAcBase<256> ac(Patts, ps);

	
	ac.setReportFunc(myreport);
	gPatList=Patts;
	curText = Text;

    i = 0;
    //for(i=0;i<5;i++)
    {

        {
            Mtime( &startrdt );
            ac.search(Text);
            Mtime( &endrdt );
            elapsed_time= Mdifftime( startrdt, endrdt );
            printf("\nalgorithm %s takes\t %20.15f seconds.\n",matchalgstr[i], elapsed_time );
            //  fprintf(fp,"%20.15f seconds:algorithm %s takes \n ", elapsed_time, matchalgstr[i]);
        }
    }
    //fclose(fp);
}
