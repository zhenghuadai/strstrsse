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

#ifndef  MWM_TEMPLATE_HEADER__INC
#define  MWM_TEMPLATE_HEADER__INC
#include <stdio.h>
#include <stdlib.h>
#include "mMatch.h"


namespace dmMatch{

class mWm :public mMatch
{
	private:
		enum{WM_BLOCK_WIDTH=2 ,SHIFT_WIDTH=2, SHIFT_TABLE_SIZE=(1<< (SHIFT_WIDTH * 8))};
	public:
		mWm(char** pat, int n) : mMatch(pat, n),matchList(0), matchArray(0){type=mAC; mWm::compile();}
	public:
		virtual void compile();
		virtual int search(char* txt, int n);
		virtual int search(char* txt);
		virtual int searchGene(char* txt, int n){};
		virtual int searchGene(char* txt){};
		virtual int searchGene4(char* txt, int n){};
		virtual int searchGene4(char* txt){};
		virtual int searchGeneC(char* txt, int n){};
		virtual int searchGeneC(char* txt){};
		virtual int searchGene4C(char* txt, int n){};
		virtual int searchGene4C(char* txt){};
	private:
		Uint hash(Uchar* pc){ return ((U16*)pc)[-1];}
		int reportwmList(list<int>* patIDList, int idx, char* txt){ 
			int ret;
			for(list<int>::iterator i= patIDList->begin(); i!= patIDList->end(); i++){
				if( strncmp(txt+idx,mPatterns[*i],mPatLen[*i]) ==0) 
					ret = report(*i, idx+(mPatLen[*i])-1);
			}
			return ret;
		};

	private:
		Uchar mShift[SHIFT_TABLE_SIZE];
		Uint mMinPatLen;
		list<int>** matchList;
		int** matchArray;
};

}//! dmMatch
#include "mWm.hxx"
#endif   /* ----- #ifndef MWM_HEADER__INC  ----- */
