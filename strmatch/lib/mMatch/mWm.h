/**
 * =====================================================================================
 *       @file    mWm.h
 *
 *       @brief   '
 *
 *       @author  DAI ZHENGHUA (), djx.zhenghua@gmail.com
 *       @version 1.0
 *       @date    02/11/2011 04:00:59 PM
 *
 *       Revision none
 *       Compiler gcc
 *       Company  
 * =====================================================================================
 */
#ifndef  MWM_TEMPLATE_HEADER__INC
#define  MWM_TEMPLATE_HEADER__INC
#include <stdio.h>
#include <stdlib.h>
#include "mMatch.h"


namespace dmMatch{

typedef Uint (*wmHashFunc)(const Uchar* pc);
inline Uint hash2bytes(const Uchar* pc){ return ((U16*)pc)[-1];}

template<int WM_BLOCK_WIDTH=2, wmHashFunc hash=hash2bytes, int HashCompressRatio=1>
class mWm :public mMatch
{
	private:
		enum{SHIFT_WIDTH=WM_BLOCK_WIDTH, SHIFT_TABLE_SIZE=(1<< ((SHIFT_WIDTH * 8)/HashCompressRatio))};
	public:
		mWm(char** pat, int n) : mMatch(pat, n),matchList(0), matchArray(0),matchArrayMem(0){type=mAC; mWm::compile();}
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
		//Uint hash(Uchar* pc){ return ((U16*)pc)[-1];}
		int reportwmList(list<int>* patIDList, int idx, char* txt){ 
			int ret;
			for(list<int>::iterator i= patIDList->begin(); i!= patIDList->end(); i++){
				if( strncmp(txt+idx,mPatterns[*i],mPatLen[*i]) ==0) 
					ret = report(*i, idx+(mPatLen[*i])-1);
			}
			return ret;
		}

        int reportwmList(int* patIDList, int idx, char* txt){ 
            int ret;
            for(int i=1; i<=patIDList[0];i++){
                int patI = patIDList[i];
                if( strncmp(txt+idx,mPatterns[patI],mPatLen[patI]) ==0) 
                    ret = report(patI, idx+(mPatLen[patI])-1);
            }
            return ret;
        }


        static void transList(list<int>**& matchList, int**& matchArray, int*& matchArrayMem, int n);
        static void freeList(list<int>**& matchList,int n);

    private:
        Uchar mShift[SHIFT_TABLE_SIZE];
        Uint mMinPatLen;
        list<int>** matchList;
        int** matchArray;
        int* matchArrayMem;
};

}//! dmMatch
#include "mWm.hxx"
#endif   /* ----- #ifndef MWM_HEADER__INC  ----- */
