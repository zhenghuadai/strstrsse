#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include "match.h"
#include "global.h"
#include<stdio.h>
#include "dmutil.h"
#include <list>
#include "geneindex.h"
using namespace std;
int   loadGenePatternFasta(char *pfname, list<Pattern_fasta>* patts);
Pattern_fasta* loadGeneFasta(char *pfname);
char** transList1(list<Pattern_fasta>* tList);
int main(int argc,char *argv[])
{
    /*  读入目标串和模式串 初始化 */ 
    int i ;
    static int stats_flag=0;
    char *databasefname,*inputfname;
    double elapsed_time;
    void (* matchalg[5])(char * text,char * pat[],int num);
    char * matchalgstr[5];
    int boolmatch[5];
    FILE *fp;

    _U64 startrdt,endrdt;
    if(argc==1)
    {
        inputfname="chrM.fa";
        databasefname="chrM.fa.index";
        //return 0;
    } else{ 
        for(i=1;i<argc;i++)
        {
            switch(argv[i][0]){
                case '-':
                    switch(argv[i][1]){
                        case 'i':
                            inputfname=argv[i+1];
                            i++;
                            break;
                        case 'o':
                            databasefname=argv[i+1];
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
    Pattern_fasta* genome = loadGeneFasta(inputfname);
    Text = genome->str;
    geneIndex GI(inputfname);
    {

        {
            Mtime( &startrdt );
            //GI.build3(Text, 0, 1024);
            GI.build3(Text, 0);
            Mtime( &endrdt );
            elapsed_time= Mdifftime( startrdt, endrdt );
            printf("\nbuild takes\t %20.15f seconds.\n", elapsed_time );
        }
    }
    //fclose(fp);
    printf("test finished\n");

}
