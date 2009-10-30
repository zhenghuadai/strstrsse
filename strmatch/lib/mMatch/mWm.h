/*
 * =====================================================================================
 *Copyright(C) by Zhenghua Dai. All rights reserved.
 *
 *
 *
 * ==================================
 * ==================================
 *
 *       Filename:  mWm.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年10月27日 21时42分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhenghua Dai (Zhenghua Dai), djx.zhenghua@gmail.com
 *        Company:  dzh
 *
 * =====================================================================================
 */

#ifndef  MWM_HEADER__INC
#define  MWM_HEADER__INC
#include <stdio.h>
#include <stdlib.h>
#include "mMatch.h"


namespace dmMatch{

class mWm :public mMatch
{
	private:
		enum{WM_BLOCK_WIDTH=2 ,SHIFT_WIDTH=2, SHIFT_TABLE_SIZE=(1<< (SHIFT_WIDTH * 8))};
	public:
		mWm(){}
	public:
		virtual void compile();
		virtual int search(char* txt, int n);
		virtual int search(char* txt);
		virtual int searchGene(char* txt, int n);
		virtual int searchGene(char* txt);
		virtual int searchGene4(char* txt, int n);
		virtual int searchGene4(char* txt);
		virtual int searchGeneC(char* txt, int n);
		virtual int searchGeneC(char* txt);
		virtual int searchGene4C(char* txt, int n);
		virtual int searchGene4C(char* txt);
	private:
		Uint hash(Uchar* pc){ return ((U16*)pc)[-1];}
	private:
		Uchar mShift[SHIFT_TABLE_SIZE];
		Uint mMinPatLen;
};

}//! dmMatch
#include "mWm.hxx"
#endif   /* ----- #ifndef MWM_HEADER__INC  ----- */
