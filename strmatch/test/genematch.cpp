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
char** rctransList1(list<Pattern_fasta>* tList);
const int maxLoopLen = 150;
static char** gPatList=0;
static char* curText = 0;
static int   curTextLen = 0;
FILE* fpout = stdout;

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
	//!  starti1...starti2...idx+1
	//!  preLen ...m      ... postLen
	int m = strlen(gPatList[patID]);
    int starti1 =idx-m+1-150; 
	int starti2 = idx-m+1;
	char* start, *targetStart;
	starti1 = (starti1>0?starti1:0);
	int preLen = starti2-starti1; 
	int postLen = (curTextLen-idx> 150 )?150:curTextLen-idx-1;
    start= &curText[starti1];
    targetStart = &curText[starti2];
    fwrite(start, preLen, 1, fpout);
    fprintf(fpout,"...");
    fwrite(targetStart, m, 1, fpout);
    fprintf(fpout,"...");
    fwrite(&curText[idx+1], postLen, 1, fpout);
	//! loop-stem
#if 1
/*
 * 
 * */
	char rPat[512];
	//reverse(rPat, gPatList[patID], m);
	reverse(rPat, targetStart, m);
	int endi1 = idx+maxLoopLen+1;
	endi1 = endi1> curTextLen?curTextLen:endi1;
	char oldChar = curText[endi1];
	curText[endi1]= 0;
	char* rPos = strstr(&curText[idx-m+1-150], rPat);
	curText[endi1]= oldChar;
	if(rPos !=NULL){
		fprintf(fpout, "\nloop-stem\n");
		int rPosIdx = rPos - curText;
		if(rPosIdx  > idx){ // pat ... rpat
		//! start...targetStart...idx+1 ...rpos...rpos+m
		//! 150  ...m     ...loopbp...m   ...60
			int loopbp = rPosIdx - idx; 
			fwrite(start, preLen, 1, fpout);
			fprintf(fpout,"...");
			fwrite(targetStart, m, 1, fpout);
			fprintf(fpout,"...");
			fwrite(&curText[idx+1], loopbp, 1, fpout);
			fprintf(fpout,"...");
			fwrite(rPos, m, 1, fpout);
			fprintf(fpout,"...");
			fwrite(rPos+m, 60, 1, fpout);

		}else{//rpat ... pat
			int loopbp = idx - rPosIdx -2*m +1;
			if(loopbp <=0) {fprintf(fpout,"interleave\n"); return 0;}
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
return 0;
}

void reportInfo(char* patfn, char* dataBasefn)
{
	fprintf(fpout, "quary:%s dataBase:%s\n",patfn, dataBasefn);
}

void closeReport()
{
	fclose(fpout);
}

using namespace dmMatch;
int main(int argc,char *argv[])
{
	/*  读入目标串和模式串 初始化 */ 
	int i ;
	static int stats_flag=0;
	char *subjfname=0,*quryfname=0;
	double elapsed_time;
	char * matchalgstr[5];
	int boolmatch[5];
	char* fnout;

	fpout = stdout;
	if(argc==1)
	{
		//quryfname="q1_mapped.txt";
		//subjfname="chrM.fa";
		printf("genematch -a quryfile -D dataBasefile -o output\n");
		return 0;
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
		matchalgstr[i]=NULL;
	}
	matchalgstr[0]="ac";
	printf("reading pattern %s...\n",quryfname);
	list<Pattern_fasta>* pattsList= new list<Pattern_fasta>;
	ps=loadGenePatternFastaU(quryfname,  pattsList);
	char** patts = transList1(pattsList);
	char** rcpatts = rctransList1(pattsList);
	//ps=GetGenepatternfromfile(quryfname,Patts);
	//char** patts = Patts;
	//for(int j=0;j<ps;j++) printf("%s\n",patts[j]);

	printf("reading reference %s...\n", subjfname);
	//Text=GetGenesubjectfromfile(subjfname);
	Pattern_fasta* genome = loadGeneFastaU(subjfname);
	Text = genome->str;
	curTextLen=genome->len;

	occurnum=0;
	//printf("%s,",Text);
	printf("\n");
	//printf("\n%d ok\n",strlen(Text));
	/* 调用串匹配函数 */
	//AcBase<4> ac(patts, ps, geneAC);
	Ac<AcBase<4>> ac(patts, ps, geneACWid);
	Ac<AcBase<4>> rac(rcpatts, ps, geneACWid);
    for(int j = 0; j< pattsList -> size(); j++){
        free(rcpatts[j]);
    }
    free(rcpatts);
//	Ac<AcI<4,unsigned int>> acD(ac);
	//AcI<4,unsigned short> acD(ac);
    //mWm<8,geneHashWm8,4> wm(patts, ps);

	ac.setReportFunc(myreport);
	rac.setReportFunc(myreport);
	//wm.setReportFunc(myreport);
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
			//printf("\nalgorithm %s takes\t %20.15f cycles.\n",matchalgstr[i], elapsed_time );
			ac.TsearchGene(Text);
			printf("\nalgorithm %s takes\t %20.15f cycles.\n",matchalgstr[i], ac.getTime());
			//wm.Tsearch(Text);
			//printf("\nalgorithm %s takes\t %20.15f cycles.\n",matchalgstr[i], wm.getTime());
			//! search complement 
			fprintf(fpout, "\n-----------------------\n");
			fprintf(fpout, " The follow is complement\n");
			fprintf(fpout, " The follow is complement\n");
			fprintf(fpout, " The follow is complement\n");
			rac.TsearchGene(Text);
			printf("\nalgorithm %s takes\t %20.15f cycles.\n",matchalgstr[i], ac.getTime());
		}
	}
	//fclose(fp);
	printf("test finished\n");

	/* 输出结果 */ 
	for(i=0;i<occurnum;i++)
		printf("%d,",occurrenceint[i]);

	closeReport();
    for(list<Pattern_fasta>::iterator it=pattsList->begin(); it!=pattsList->end(); it++){
        if(it->name != nullptr) free(it->name);
        if(it->str != nullptr) free(it->str);
    }

}
