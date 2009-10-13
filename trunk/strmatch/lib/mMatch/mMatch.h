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
typedef enum{
mAC,mWM
} mAlgtype;

typedef int (* reportFunc)(int patID, int idx);
class mMatch{
	protected:
		int type;
		char** mPatterns;
		int* mPatLen;
		int mPatNum;
		reportFunc report;
	public:
		mMatch();
	public:
		void setReportFunc(reportFunc f){report = f;}
		void reset(char** ,int n);
		virtual int search(char* txt, int n){};
		virtual int search(char* txt){};
		virtual void init(){};
	private:
		void clean();
};
}
