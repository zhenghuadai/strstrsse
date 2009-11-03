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

#ifndef  MMATCH_INC
#define  MMATCH_INC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <assert.h>
#include "dmutil.h"

#ifndef rdtsc 
#define rdtsc(low,high) \
    __asm__ __volatile__("xorl %%eax, %%eax; cpuid; rdtsc" : "=a" (low), "=d" (high)::"%ecx","%ebx");
#endif

//#define ASSERT(a, ...) {if(! (a)){ err(__VA_ARGS__##__LINE__);}}
#define ASSERT(a, ...) {assert(a);}

using namespace std;
namespace dmMatch{
typedef enum{
    mAC, geneAC, mWM, mACDep, mACWid, geneACDep, geneACWid
} mAlgtype;
typedef enum {ACDep_First, ACWid_First} AC_Store_t;

typedef int (* reportFunc)(int patID, int idx);
class mMatch{
    public:
        mMatch(char** pat, int patNum){memset(this, 0, sizeof(mMatch) ); init(pat, patNum); report=reportSilent; report=reportDefault;};
        mMatch(){memset(this, 0, sizeof(mMatch)); report=reportDefault;};
    public:
        virtual int search(char* txt, int n) 		{return 0;}
        virtual int search(char* txt) 			 	{return 0;}
        virtual int searchGene(char* txt, int n) 	{return 0;}
        virtual int searchGene(char* txt) 			{return 0;}
        virtual int searchGene4(char* txt, int n) 	{return 0;}
        virtual int searchGene4(char* txt) 			{return 0;}
        //! continue searching 
        virtual int searchC(char* txt, int n) 		{return 0;}
        virtual int searchC(char* txt) 				{return 0;}
        virtual int searchGeneC(char* txt, int n) 	{return 0;}
        virtual int searchGeneC(char* txt) 			{return 0;}
        virtual int searchGene4C(char* txt, int n) 	{return 0;}
        virtual int searchGene4C(char* txt) 		{return 0;}
        int Tsearch(char* txt, int n)     {startTime();int ret=search(txt,n);     endTime();return ret;}
        int Tsearch(char* txt)            {startTime();int ret=search(txt);       endTime();return ret;}
        int TsearchGene(char* txt, int n) {startTime();int ret=searchGene(txt,n); endTime();return ret;}
        int TsearchGene(char* txt)        {startTime();int ret=searchGene(txt);   endTime();return ret;}
        int TsearchGene4(char* txt, int n){startTime();int ret=searchGene4(txt,n);endTime();return ret;}
        int TsearchGene4(char* txt)       {startTime();int ret=searchGene4(txt);  endTime();return ret;}
        void setReportFunc(reportFunc f){report = f;}
        void init(char** ,int n);
        ~mMatch(){ free(mPatLen);}
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
        unsigned int minPatLen(){unsigned int n=patLen(0); for(int i=1;i<mPatNum;i++) n=(n < patLen(i)? n:patLen(i)); return n; }
    private:
        void clean();
        void startTime(){};
        void endTime(){};
		unsigned int patLen(unsigned idx) { return strlen( mPatterns[idx]);}
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
#endif   /* ----- #ifndef MMATCH_INC  ----- */
