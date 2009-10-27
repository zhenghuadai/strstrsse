/*
 * =====================================================================================
 *
 *       Filename:  mMatch.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/13/2009 09:11:51 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhenghua Dai (Zhenghua Dai), djx.zhenghua@gamil.com
 *        Company:  dzh
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include "dmutil.h"

#ifndef rdtsc 
#define rdtsc(low,high) \
    __asm__ __volatile__("xorl %%eax, %%eax; cpuid; rdtsc" : "=a" (low), "=d" (high)::"%ecx","%ebx");
#endif

using namespace std;
namespace dmMatch{
typedef enum{
    mAC, geneAC, mWM
} mAlgtype;

typedef int (* reportFunc)(int patID, int idx);
class mMatch{
    public:
        mMatch(char** pat, int patNum){memset(this, 0, sizeof(mMatch) ); init(pat, patNum); report=reportSilent; report=reportDefault;};
        mMatch(){memset(this, 0, sizeof(mMatch)); report=reportDefault;};
    public:
        virtual int search(char* txt, int n){};
        virtual int search(char* txt){};
        virtual int searchGene(char* txt, int n){};
        virtual int searchGene(char* txt){};
        virtual int searchGene4(char* txt, int n){};
        virtual int searchGene4(char* txt){};
        virtual int searchC(char* txt, int n){};
        virtual int searchC(char* txt){};
        virtual int searchGeneC(char* txt, int n){};
        virtual int searchGeneC(char* txt){};
        virtual int searchGene4C(char* txt, int n){};
        virtual int searchGene4C(char* txt){};
        int Tsearch(char* txt, int n)     {startTime(); search(txt,n);     endTime();}
        int Tsearch(char* txt)            {startTime(); search(txt);       endTime();}
        int TsearchGene(char* txt, int n) {startTime(); searchGene(txt,n); endTime();}
        int TsearchGene(char* txt)        {startTime(); searchGene(txt);   endTime();}
        int TsearchGene4(char* txt, int n){startTime(); searchGene4(txt,n);endTime();}
        int TsearchGene4(char* txt)       {startTime(); searchGene4(txt);  endTime();}
        void setReportFunc(reportFunc f){report = f;}
        void init(char** ,int n);
        ~mMatch(){}
        double getTime(){return mTimeSearch;}
    protected:
        virtual void compile(){};
        unsigned int charNum(){unsigned int n=0; for(int i=0;i<mPatNum;i++) n += strlen(mPatterns[i]); return n; }
        int reportList(int patID, int idx){ return report(patID, idx);}
        int reportList(list<int>* patIDList, int idx){
            int ret;
            if(patIDList ==NULL) return 0;
            for(list<int>::iterator i= patIDList->begin(); i!= patIDList->end(); i++) ret = report(*i, idx);
            return ret;
        }
        static int reportList(int* patIDList,reportFunc report, int idx){
            int ret;
            if(patIDList ==NULL) return 0;
            for(int i=1; i<=patIDList[0]; i++) 
                ret = report(patIDList[i], idx);
            return ret;
        }
        int reportList(int* patIDList, int idx){
            reportList(patIDList, report, idx);
        }
    private:
        void clean();
        void startTime(){};
        void endTime(){};
    public:
        static int reportDefault(int patid, int idx){ printf("(%d,%d) ", patid, idx);}
        static int reportSilent(int patid, int idx){}
    protected:
        int type;
        char** mPatterns;
        int* mPatLen;
        int mPatNum;
        reportFunc report;
        list<Pattern_t>* pPatList;
        double mTimeSearch;
};
}
