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

#define interface public
#define constructor public
#define __static static 

#if defined(__GNUC__)
inline size_t _msize(void* p){
    return p?((size_t*)p)[-1]:0;
}
#else      /* -----  not  defined(__GNUC__)----- */
#endif     /* -----  not  defined(__GNUC__)----- */

//#define ASSERT(a, ...) {if(! (a)){ err(__VA_ARGS__##__LINE__);}}
#define ASSERT(a, ...) {assert(a);}

using namespace std;
namespace dmMatch{
typedef enum{
    maAC, geneAC, maWM, mACDep, mACWid, geneACDep, geneACWid
} mAlgtype;

typedef int (* reportFunc)(int patID, int idx);
#if 0
#define MMalloc(x) ({printf("%0x +",this);printf(#x); mMalloc(x);})
#define MFree(x)   {printf("%0x -", this);printf(#x); mFree(x);}
#define DEBUG_MALLOC 1
#else
#define MMalloc(x) mMalloc(x)
#define MFree(x) mFree(x)
#define DEBUG_MALLOC 0
#endif
class memBase
{
    public:
        memBase(){bytesUsed =0;}
        ~memBase(){  /*printf("destroy :%d bytes left\n", bytesUsed); ASSERT( bytesUsed <=10);*/}
		void* mMalloc(size_t n){ 
            void *p;
            p = (void*) malloc(n);
            bytesUsed += _msize(p);
            if(DEBUG_MALLOC)printf("+%zd=%d\n", _msize(p), bytesUsed);
            return p;
        }
        template<typename T>
		void mFree(T*& p) {
            if(p==NULL)return; 
            bytesUsed -= _msize(p); 
            if(DEBUG_MALLOC) printf("-%zd=%d\n", _msize(p),bytesUsed);
            free(p);
            p=NULL;
        }
        void mDecrease(size_t n){bytesUsed -=n;}
        size_t memMalloced(){return bytesUsed;}
    protected:
		int bytesUsed;
};

class PatternsBase:public memBase
{

    protected:
        PatternsBase():mPatterns(NULL),mPatLen(NULL),mPatNum(0){}
interface:
		//!----------------------------------------------------------------------------
		//  
		//!----------------------------------------------------------------------------
        void setPatterns(char** pats,int n);
		//!----------------------------------------------------------------------------
		//return the memory that has been used  
		//!----------------------------------------------------------------------------
        virtual size_t memUsed(){ return memMalloced();}
    protected:
        unsigned int charNum(){unsigned int n=0; for(int i=0;i<mPatNum;i++) n += strlen(mPatterns[i]); return n; }
    protected:
		int type; 		  //! algorithm type
		char** mPatterns; //! array of patterns' pointer
		int* mPatLen;     //! array of patterns' length
		int mPatNum;      //! number of patterns
		list<Pattern_t>* pPatList; //! list of patterns
};

class mMatch:public PatternsBase
{
    public:
        mMatch(char** pat, int patNum){memset(this, 0, sizeof(mMatch) ); setPatterns(pat, patNum); report=reportSilent;};
        mMatch(){memset(this, 0, sizeof(mMatch)); report=reportDefault;};
        ~mMatch(){ MFree(mPatLen); }
        enum{SEARCH_CONTINUE=0,SEARCH_STOP=1 };
interface:
		//!----------------------------------------------------------------------------
		// 
		//!----------------------------------------------------------------------------
        virtual int search(char* txt, int n) 		{(void)txt; (void)n; return 0;}
        virtual int search(char* txt) 			 	{(void)txt; return 0;}
        virtual int searchGene(char* txt, int n) 	{(void)txt; (void)n; return 0;}
        virtual int searchGene(char* txt) 			{(void)txt; return 0;}
        virtual int searchGene_(char* txt, int n) 	{(void)txt; (void)n; return 0;}
        virtual int searchGene_(char* txt) 			{(void)txt; return 0;}

		//!----------------------------------------------------------------------------
        //! continue searching 
		//!----------------------------------------------------------------------------
        virtual int searchC(char* txt, int n) 		{(void)txt; (void)n; return 0;}
        virtual int searchC(char* txt) 				{(void)txt; return 0;}
        virtual int searchGeneC(char* txt, int n) 	{(void)txt; (void)n; return 0;}
        virtual int searchGeneC(char* txt) 			{(void)txt; return 0;}

		//!----------------------------------------------------------------------------
		// 
		//!----------------------------------------------------------------------------
        int Tsearch(char* txt, int n)     {startTime();int ret=search(txt,n);     endTime();return ret;}
        int Tsearch(char* txt)            {startTime();int ret=search(txt);       endTime();return ret;}
        int TsearchGene(char* txt, int n) {startTime();int ret=searchGene(txt,n); endTime();return ret;}
        int TsearchGene(char* txt)        {startTime();int ret=searchGene(txt);   endTime();return ret;}
        int TsearchGene_(char* txt, int n){startTime();int ret=searchGene_(txt,n);endTime();return ret;}
        int TsearchGene_(char* txt)       {startTime();int ret=searchGene_(txt);  endTime();return ret;}

		//!----------------------------------------------------------------------------
		// 
		//!----------------------------------------------------------------------------
        void setReportFunc(reportFunc f){report = f;}


		//!----------------------------------------------------------------------------
		//  
		//!----------------------------------------------------------------------------
        double getTime(){return (double)(mTimeEnd - mTimeStart);}

    public:
        static int reportDefault(int patid, int idx){ printf("(%d,%d) ", patid, idx); return SEARCH_CONTINUE;}
        static int reportSilent(int patid, int idx){(void)patid; (void)idx;return SEARCH_CONTINUE;}
    protected:
        virtual void compile(){};
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
            return reportList(patIDList, report, idx);
        }
        unsigned int minPatLen(){unsigned int n=patLen(0); for(int i=1;i<mPatNum;i++) n=(n < patLen(i)? n:patLen(i)); return n; }
    private:
        void clean();
        unsigned long long startTime();
        unsigned long long endTime(); 
		unsigned int patLen(unsigned idx) { return strlen( mPatterns[idx]);}
	protected:
		reportFunc report;//! report call back function
		//! the following is member for performance tuning
		unsigned long long mTimeStart;
		unsigned long long mTimeEnd;

};
}
#endif   /* ----- #ifndef MMATCH_INC  ----- */
