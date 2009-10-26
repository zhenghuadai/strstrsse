#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include "match.h"
#include "global.h"
#include<stdio.h>
#include "mAc.h"
#include "dmutil.h"
using namespace std;
int   loadGenePatternFasta(char *pfname, list<Pattern_fasta>* patts);
Pattern_fasta* loadGeneFasta(char *pfname);
char** transList1(list<Pattern_fasta>* tList);

static char** gPatList=0;
static char* curText = 0;
FILE* fpout;
int  myreport(int patID, int idx)
{
	fprintf(fpout, "\n-----------------------\n");
	fprintf(fpout, "%s Pos:%d; patID:%d\n", gPatList[patID],idx, patID);
	int m = strlen(gPatList[patID]);
    int starti = (idx - 150) > 0?(idx-150):0;
    char* start= &curText[idx-m+1-150];
    char* start2 = &curText[idx-m+1];
    fwrite(start, 150, 1, fpout);
    fprintf(fpout,"...");
    fwrite(start2, m, 1, fpout);
    fprintf(fpout,"...");
    fwrite(&curText[idx+1], 150, 1, fpout);
}

using namespace dmMatch;
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
    char* fnout;

    _U64 startrdt,endrdt;
    fpout = stdout;
    if(argc==1)
    {
        quryfname="q1_mapped.txt";
        subjfname="chrM.fa";
        //return 0;
    } else{ 
        for(i=1;i<argc;i++)
        {
            switch(argv[i][0]){
                case '-':
                    switch(argv[i][1]){
                        case 'a':
                            quryfname=argv[i+1];
                            i++;
                            break;
                        case 'D':
                            subjfname=argv[i+1];
                            i++;
                            break;
                        case 'o':
                            fnout=argv[i+1];
                            fpout = fopen(fnout, "w");
                            i++;
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
    }

    for(i=0;i<5;i++){
        matchalg[i]=NULL;
        matchalgstr[i]=NULL;
    }
    matchalgstr[0]="ac";
    Patts[0]="Natasha";
    Patts[1]="ocean";
    Patts[2]="romantic";
    Patts[3]="shape";
    Patts[4]="still";
    ps=5;
    Text="Till today, the lantern ncichpc  festival is still held each year ncichpc around the country. Lanterns of various shapes and sizes ncichpc are hung in the streets, attracting countless visitors. Children will hold self-made or bought lanterns to stroll with on the streets, extremely excite";
    printf("reading pattern ...\n");
    list<Pattern_fasta>* pattsList= new list<Pattern_fasta>;
    ps=loadGenePatternFasta(quryfname,  pattsList);
    char** patts = transList1(pattsList);
    //ps=GetGenepatternfromfile(quryfname,Patts);
    //char** patts = Patts;
    //for(int j=0;j<ps;j++) printf("%s\n",patts[j]);

    printf("reading reference...\n");
    //Text=GetGenesubjectfromfile(subjfname);
    Pattern_fasta* genome = loadGeneFasta(subjfname);
    Text = genome->str;

    //printf("%s\n",Pat);
    occurnum=0;
    //printf("%s,",Text);
    printf("\n");
    printf("\n%d ok\n",strlen(Text));
    /* 调用串匹配函数 */
    mAcBase<4> ac(patts, ps, geneAC);
    mAcD<4,unsigned int> acD(ac);
    //mAcD<4,unsigned short> acD(ac);

    ac.setReportFunc(myreport);
    gPatList=patts;
    curText = Text;

    i = 0;
    //for(i=0;i<5;i++)
    {
        {
            Mtime( &startrdt );
            ac.searchGene(Text);
            Mtime( &endrdt );
            elapsed_time= Mdifftime( startrdt, endrdt );
            printf("\nalgorithm %s takes\t %20.15f seconds.\n",matchalgstr[i], elapsed_time );
            //  fprintf(fp,"%20.15f seconds:algorithm %s takes \n ", elapsed_time, matchalgstr[i]);
        }
    }
    //fclose(fp);
    printf("test finished\n");

    /* 输出结果 */ 
    for(i=0;i<occurnum;i++)
        printf("%d,",occurrenceint[i]);

}
