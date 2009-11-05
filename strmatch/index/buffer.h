/*
 * =====================================================================================
 *Copyright(C) by Zhenghua Dai. All rights reserved.
 *
 *
 *
 * ==================================
 * ==================================
 *
 *       Filename:  buffer.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年10月25日 10时32分43秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhenghua Dai (Zhenghua Dai), djx.zhenghua@gmail.com
 *        Company:  dzh
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef  BUFFER_HEADER__INC
#define  BUFFER_HEADER__INC
#include <vector>
#include "dmutil.h"

class OutBufferBase
{
    protected:
        void fwriteHeader(char* fn);
};


class OutBuffer6b:public OutBufferBase
{
    public:
        enum{ bufSize = 1024*64};
    public:
        OutBuffer6b(){ memset(this, 0, sizeof(OutBuffer6b));init();}
        OutBuffer6b(char* fnin){ memset(this, 0, sizeof(OutBuffer6b));init(); setFnInput(fnin);}
    public:
        void write(int h, Uint idx);
    public:
        void setFnInput(char* fn){ fnInput = strdup(fn);}
        void init();
        void distroy();
        void fwrite(int fileNo);
        void finish();
    protected:
        FILE* fpin;
        FILE* fpDataBase;
        FILE* fpLog;
        Uint* memBuffer; 
        int* buffer[64];
        int curIdx[64];
        char* fnInput;

};

class PosList
{
	private:
		std::vector<int> mVec;
	public:
		PosList(){}
		~PosList(){mVec.~vector();}
	public:
		void appand(int idx) { mVec.push_back(idx);}
		size_t size(){return mVec.size();}
		void clean(){ mVec.empty();}
		void copyTo(Uint* p){ for(std::vector<int>::iterator i=mVec.begin(); i!=mVec.end();i++,p++){*p=*i;}}

};

template<int HashBit=22>
class OutBuffer:public OutBufferBase 
{
	public:
		enum{MAX_HASH_VALUE= (1<< HashBit) -1, HashTableSize= 1<< HashBit};
	public:
		OutBuffer(){ memset(this, 0, sizeof(OutBuffer));init();}
		OutBuffer(char* fnin){ memset(this, 0, sizeof(OutBuffer));init(); setFnInput(fnin);}
		//~OutBuffer(){if(bucket){ delete bucket; bucket=0;}}
	public:
		void write(int h, Uint idx);
	public:
		void setFnInput(char* fn){ fnInput = strdup(fn);}
		void finish(){ write2file();}
	private:
		void init();
		void distroy();
		void write2file();
		void cleanBeforContinue();
	protected:
		char* fnInput;
	private:
		size_t curSize;
		size_t mBufferFull;
		int curFileNo;
		PosList* bucket;//[HashTableSize];


};

#include "buffer.hxx"

#endif   /* ----- #ifndef BUFFER_HEADER__INC  ----- */
