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


class  Value_Hash{
	public:
		Uint value;
		Uint h;
		void set(Uint v, Uint _h){ value=v; h=_h;}
		static int compareValue( const void * node1, const void* node2){
			return (((Value_Hash*)node1)-> value> ((Value_Hash*)node2)->value? 1:-1);
		}
		static int compareHash( const void * node1, const void* node2){
			return (((Value_Hash*)node1)-> h> ((Value_Hash*)node2)->h? 1:-1);
		}
} ;

template<int HashBit=22>
class OutBuffer2:public OutBufferBase{
	public:
		enum{MAX_HASH_VALUE= (1<< HashBit) -1, HashTableSize= 1<< HashBit};
	public:
		OutBuffer2(){ memset(this, 0, sizeof(OutBuffer2));init();}
		OutBuffer2(char* fnin){ memset(this, 0, sizeof(OutBuffer2));init(); setFnInput(fnin);}
		~OutBuffer2(){free(pVH); pVH=0;}
	public:
		void write(int h, Uint idx);
	public:
		void setFnInput(char* fn){ fnInput = strdup(fn);}
		void finish(){ write2file(); mergeFile();}
	private:
		void init(){	mBufferFull = 1024 * 1024 * 16; pVH = (Value_Hash*) malloc(mBufferFull*sizeof(Value_Hash));}
		void distroy();
		void write2file();
		void cleanBeforContinue();
		void mergeFile();
	protected:
		char* fnInput;
	private:
		size_t curSize;
		size_t mBufferFull;
		int curFileNo;
		union{
			Value_Hash* pVH;
			Uint* pInt;
		};
};




#include "buffer.hxx"





#endif   /* ----- #ifndef BUFFER_HEADER__INC  ----- */
