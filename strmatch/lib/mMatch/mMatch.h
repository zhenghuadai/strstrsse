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
namespace dmMatch{
typedef unsigned char Uchar;
enum{
mAC,mWM
} mAlgtype;

class mMatch{
	protected:
		int type;
		char** mPatterns;
		int* mPatLen;
		int mPatNum;
	public:
		mMatch();
	public:
		void reset(char** ,int n);
		virtual int search(char* txt, int n);
		virtual int search(char* txt);
	private:
		void clean();
};
}
