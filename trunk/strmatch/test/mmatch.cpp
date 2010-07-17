#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include "match.h"
#include "global.h"
#include<stdio.h>
#include "mAc.h"
#include "mWm.h"
using namespace dmMatch;

static char** gPatList=0;
static char* curText = 0;

int  myreport(int patID, int idx)
{
	printf("\n-----------------------%d %d\n", patID, idx);
	printf("%s\n", gPatList[patID]);
	int m = strlen(gPatList[patID]);
	for(int i=1-m;i< 10;i++)
		printf("%c", curText[idx+i]);
}


int main(int argc,char *argv[])
{
    int i ;
    static int stats_flag=0;
    char *subjfname,*quryfname;
    double elapsed_time;
    void (* matchalg[5])(char * text,char * pat[],int num);
    char * matchalgstr[5];
    int boolmatch[5];

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

    occurnum=0;
    printf("\n");
    printf("\n%d ok\n",strlen(Text));

	
	gPatList=Patts;
    curText = Text;

    i = 0;
    {
//        mAcBase<256> ac(Patts, ps, mACWid);
//        ac.setReportFunc(myreport);
        Ac<mAcBase<256,StoreArray,UseBadChar>, 256,UseBadChar> ac(Patts, ps, mACWid);
        printf("mem:%d\n", ac.memUsed());
        Mtime( &startrdt );
        ac.search(Text);
        Mtime( &endrdt );
        printf("\n\n");
        elapsed_time= Mdifftime( startrdt, endrdt );
        printf("\nalgorithm %s takes\t %20.15f seconds.\n","AC", elapsed_time );
    }

    {
        mWm<> wm(Patts, ps);
//        wm.setReportFunc(myreport);
        printf("mem:%d\n", wm.memUsed());
        Mtime( &startrdt );
        wm.search(Text);
        Mtime( &endrdt );
        printf("\n\n");
        elapsed_time= Mdifftime( startrdt, endrdt );
        printf("\nalgorithm %s takes\t %20.15f seconds.\n","WM", elapsed_time );
    }
}
