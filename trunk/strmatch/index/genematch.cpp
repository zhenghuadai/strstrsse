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

    _U64 startrdt,endrdt;
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
                    }
                    break;
                default:
                    break;
            }
        }
    }
    printf("reading reference...\n");
    //Text=GetGenesubjectfromfile(subjfname);
    Pattern_fasta* genome = loadGeneFasta(subjfname);
    Text = genome->str;

    {

        {
            Mtime( &startrdt );
            Mtime( &endrdt );
            elapsed_time= Mdifftime( startrdt, endrdt );
            printf("\nalgorithm %s takes\t %20.15f seconds.\n",matchalgstr[i], elapsed_time );
        }
    }
    //fclose(fp);
    printf("test finished\n");

}
