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
namespace dmMatch{
typedef unsigned char Uchar;
typedef unsigned short U16;
typedef short I16;
typedef enum{
mAC,mWM
} mAlgtype;

typedef int (* reportFunc)(int patID, int idx);
class mMatch{
	public:
		mMatch(char** pat, int patNum){memset(this, 0, sizeof(mMatch)); init(pat, patNum); report=reportSilent;};
	public:
		virtual int search(char* txt, int n){};
		virtual int search(char* txt){};
		void setReportFunc(reportFunc f){report = f;}
		void init(char** ,int n);
	protected:
		virtual void compile(){};
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

};
}