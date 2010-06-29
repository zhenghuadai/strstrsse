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

#if defined(__GNUC__)
# 	define nasm0(op) __asm__( #op)
inline size_t _msize(void* p){
    return p?((size_t*)p)[-1]:0;
}
#else      /* -----  not  defined(__GNUC__)----- */
# 	define nasm0(op) __asm op 
#endif     /* -----  not  defined(__GNUC__)----- */

static inline unsigned long long getrdtsc(){
	nasm0(rdtsc);
}
//#define ASSERT(a, ...) {if(! (a)){ err(__VA_ARGS__##__LINE__);}}
#define ASSERT(a, ...) {assert(a);}

using namespace std;
namespace dmMatch{
typedef enum{
    mAC, geneAC, mWM, mACDep, mACWid, geneACDep, geneACWid
} mAlgtype;
typedef enum {ACDep_First, ACWid_First} AC_Store_t;

typedef int (* reportFunc)(int patID, int idx);

class memBase
{
    public:
        memBase(){bytesUsed =0;}
        ~memBase(){ASSERT( bytesUsed ==0);}
		void* mMalloc(size_t n){ void*p; bytesUsed += n; p = (void*) malloc(n); return p;}
        template<typename T>
		void mFree(T*& p) {if(p==NULL)return; bytesUsed -= _msize(p); free(p); p=NULL;}
        void mDecrease(size_t n){bytesUsed -=n;}
    protected:
		int bytesUsed;
};


class mMatch:public memBase
{
    public:
        mMatch(char** pat, int patNum){memset(this, 0, sizeof(mMatch) ); setPatterns(pat, patNum); report=reportSilent; report=reportDefault;};
        mMatch(){memset(this, 0, sizeof(mMatch)); report=reportDefault;};
        ~mMatch(){ mFree(mPatLen); }
    public:
		//!----------------------------------------------------------------------------
		// 
		//!----------------------------------------------------------------------------
        virtual int search(char* txt, int n) 		{return 0;}
        virtual int search(char* txt) 			 	{return 0;}
        virtual int searchGene(char* txt, int n) 	{return 0;}
        virtual int searchGene(char* txt) 			{return 0;}
        virtual int searchGene_(char* txt, int n) 	{return 0;}
        virtual int searchGene_(char* txt) 			{return 0;}
        virtual int searchGene4(char* txt, int n) 	{return 0;}
        virtual int searchGene4(char* txt) 			{return 0;}

		//!----------------------------------------------------------------------------
        //! continue searching 
		//!----------------------------------------------------------------------------
        virtual int searchC(char* txt, int n) 		{return 0;}
        virtual int searchC(char* txt) 				{return 0;}
        virtual int searchGeneC(char* txt, int n) 	{return 0;}
        virtual int searchGeneC(char* txt) 			{return 0;}
        virtual int searchGene4C(char* txt, int n) 	{return 0;}
        virtual int searchGene4C(char* txt) 		{return 0;}

		//!----------------------------------------------------------------------------
		// 
		//!----------------------------------------------------------------------------
        int Tsearch(char* txt, int n)     {startTime();int ret=search(txt,n);     endTime();return ret;}
        int Tsearch(char* txt)            {startTime();int ret=search(txt);       endTime();return ret;}
        int TsearchGene(char* txt, int n) {startTime();int ret=searchGene(txt,n); endTime();return ret;}
        int TsearchGene(char* txt)        {startTime();int ret=searchGene(txt);   endTime();return ret;}
        int TsearchGene_(char* txt, int n){startTime();int ret=searchGene_(txt,n);endTime();return ret;}
        int TsearchGene_(char* txt)       {startTime();int ret=searchGene_(txt);  endTime();return ret;}
        int TsearchGene4(char* txt, int n){startTime();int ret=searchGene4(txt,n);endTime();return ret;}
        int TsearchGene4(char* txt)       {startTime();int ret=searchGene4(txt);  endTime();return ret;}

		//!----------------------------------------------------------------------------
		// 
		//!----------------------------------------------------------------------------
        void setReportFunc(reportFunc f){report = f;}

		//!----------------------------------------------------------------------------
		//  
		//!----------------------------------------------------------------------------
        void setPatterns(char** pats,int n);

		//!----------------------------------------------------------------------------
		//  
		//!----------------------------------------------------------------------------
        double getTime(){return (double)(mTimeEnd - mTimeStart);}
    public:
        static int reportDefault(int patid, int idx){ printf("(%d,%d) ", patid, idx);}
        static int reportSilent(int patid, int idx){}
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
        void startTime(){ mTimeStart = getrdtsc();};
        void endTime()  { mTimeEnd = getrdtsc();};
		unsigned int patLen(unsigned idx) { return strlen( mPatterns[idx]);}
	protected:
		int type; 		  //! algorithm type
		char** mPatterns; //! array of patterns' pointer
		int* mPatLen;     //! array of patterns' length
		int mPatNum;      //! number of patterns
		reportFunc report;//! report call back function
		list<Pattern_t>* pPatList; //! list of patterns
		//! the following is member for performance tuning
		unsigned long long mTimeStart;
		unsigned long long mTimeEnd;

};
}
#endif   /* ----- #ifndef MMATCH_INC  ----- */
