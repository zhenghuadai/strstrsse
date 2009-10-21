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

#if __amd64 || __x86_64
	#define BIT_64 1 	
#else
	#define BIT_64 0 	
#endif

using namespace std;
namespace dmMatch{
typedef unsigned char Uchar;
typedef unsigned short U16;
typedef short I16;
#if BIT_64 == 1
typedef long long SSize;
#else 
typedef int SSize;
#endif
typedef enum{
    mAC, geneAC, mWM
} mAlgtype;

typedef int (* reportFunc)(int patID, int idx);
class mMatch{
    public:
        mMatch(char** pat, int patNum){memset(this, 0, sizeof(mMatch) ); init(pat, patNum); report=reportSilent; report=reportDefault;};
        mMatch(){};
    public:
        virtual int search(char* txt, int n){};
        virtual int search(char* txt){};
        virtual int searchGene(char* txt, int n){};
        virtual int searchGene(char* txt){};
        virtual int searchGene4(char* txt, int n){};
        virtual int searchGene4(char* txt){};
        virtual int Tsearch(char* txt, int n){ search(txt,n);};
        virtual int Tsearch(char* txt){};
        virtual int TsearchGene(char* txt, int n){};
        virtual int TsearchGene(char* txt){};
        virtual int TsearchGene4(char* txt, int n){};
        virtual int TsearchGene4(char* txt){};
        void setReportFunc(reportFunc f){report = f;}
        void init(char** ,int n);
        ~mMatch(){}
        unsigned long long getTime(){return timeSearch;}
    protected:
        virtual void compile(){};
		unsigned int charNum(){unsigned int n=0; for(int i=0;i<mPatNum;i++) n += strlen(mPatterns[i]); return n; }
    private:
        void clean();
    public:
        static int reportDefault(int patid, int idx){ printf("(%d,%d) ", idx, patid);}
        static int reportSilent(int patid, int idx){}
    protected:
        int type;
        char** mPatterns;
        int* mPatLen;
        int mPatNum;
        reportFunc report;
        list<Pattern_t>* pPatList;
        unsigned long long timeSearch;
};
}
