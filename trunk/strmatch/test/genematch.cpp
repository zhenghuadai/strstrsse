#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include "match.h"
#include "global.h"
#include<stdio.h>
#include "dmutil.h"
#include "mAc.h"
#include "mWm.h"
#include "io.h"
using namespace std;
char** transList1(list<Pattern_fasta>* tList);

static char** gPatList=0;
static char* curText = 0;
FILE* fpout;

void reverse(char* dst, char* src, int m)
{
	int i;
	for(i=0;i<m;i++){
		dst[i] = agct2pair(src[m-1-i]);
	}
	dst[i] = 0;
}

int  myreport(int patID, int idx)
{
	fprintf(fpout, "\n-----------------------\n");
	fprintf(fpout, "%s Pos:%d patID:%d\n", gPatList[patID],idx, patID);
	//! expand
	int m = strlen(gPatList[patID]);
    int starti1 =idx-m+1-150; 
	int starti2 = idx-m+1;
    char* start= &curText[starti1];
    char* start2 = &curText[starti2];
    fwrite(start, 150, 1, fpout);
    fprintf(fpout,"...");
    fwrite(start2, m, 1, fpout);
    fprintf(fpout,"...");
    fwrite(&curText[idx+1], 150, 1, fpout);
	//! loop-stem
#if 1
	char rPat[512];
	reverse(rPat, gPatList[patID], m);
	int endi1 = idx+200+1;
	char oldChar = curText[endi1];
	curText[endi1]= 0;
	char* rPos = strstr(&curText[idx-m+1-150], rPat);
	curText[endi1]= oldChar;
	if(rPos !=NULL){
		fprintf(fpout, "\nloop-stem\n");
		int rPosIdx = rPos - curText;
		if(rPosIdx  > idx){ // pat ... rpat
			int loopbp = rPosIdx - idx; 
			fwrite(start, 150, 1, fpout);
			fprintf(fpout,"...");
			fwrite(start2, m, 1, fpout);
			fprintf(fpout,"...");
			fwrite(&curText[idx+1], loopbp, 1, fpout);
			fprintf(fpout,"...");
			fwrite(rPos, m, 1, fpout);
			fprintf(fpout,"...");
			fwrite(rPos+m, 60, 1, fpout);

		}else{//rpat ... pat
			int loopbp = idx - rPosIdx -2*m +1;
			fwrite(rPos-60,60,1,fpout);
			fprintf(fpout,"...");
			fwrite(rPos,  m,1,fpout);
			fprintf(fpout,"...");
			fwrite(rPos+m,  loopbp,1,fpout);
			fprintf(fpout,"...");
			fwrite(&curText[idx-m+1],m,1  ,fpout);
			fprintf(fpout,"...");
			fwrite(&curText[idx+1],60,1  ,fpout);
		}
	} else{
		fprintf(fpout, "\nno loop-stem\n");
	}
#endif
}

void reportInfo(char* patfn, char* dataBasefn)
{
	fprintf(fpout, "quary:%s dataBase:%s\n",patfn, dataBasefn);
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

	reportInfo(quryfname, subjfname);

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
	printf("reading pattern %s...\n",quryfname);
	list<Pattern_fasta>* pattsList= new list<Pattern_fasta>;
	ps=loadGenePatternFasta(quryfname,  pattsList);
	char** patts = transList1(pattsList);
	//ps=GetGenepatternfromfile(quryfname,Patts);
	//char** patts = Patts;
	//for(int j=0;j<ps;j++) printf("%s\n",patts[j]);

	printf("reading reference %s...\n", subjfname);
	//Text=GetGenesubjectfromfile(subjfname);
	Pattern_fasta* genome = loadGeneFastaU(subjfname);
	Text = genome->str;

	//printf("%s\n",Pat);
	occurnum=0;
	//printf("%s,",Text);
	printf("\n");
	printf("\n%d ok\n",strlen(Text));
	/* 调用串匹配函数 */
	//mAcBase<4> ac(patts, ps, geneAC);
	mAcBase<4> ac(patts, ps, geneACWid);
	mAcD<4,unsigned int> acD(ac);
	//mAcD<4,unsigned short> acD(ac);

    mWm<8,geneHashWm8,4> wm(patts, ps);
	ac.setReportFunc(myreport);
	wm.setReportFunc(myreport);
	gPatList=patts;
	curText = Text;

	i = 0;
	//for(i=0;i<5;i++)
	{
		{
			//Mtime( &startrdt );
			//ac.searchGene(Text);
			//Mtime( &endrdt );
			//elapsed_time= Mdifftime( startrdt, endrdt );
			//printf("\nalgorithm %s takes\t %20.15f seconds.\n",matchalgstr[i], elapsed_time );
			ac.TsearchGene(Text);
			printf("\nalgorithm %s takes\t %20.15f seconds.\n",matchalgstr[i], ac.getTime());
			//wm.Tsearch(Text);
			//printf("\nalgorithm %s takes\t %20.15f seconds.\n",matchalgstr[i], wm.getTime());
		}
	}
	//fclose(fp);
	printf("test finished\n");

	/* 输出结果 */ 
	for(i=0;i<occurnum;i++)
		printf("%d,",occurrenceint[i]);

}
