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
		enum{IndexFileHeaderSize=128};
        void fwriteHeader(char* fn);
        void fwriteHeader(FILE* fp);
		void printLog(char* logMsg){ printf("%s", logMsg);}
		void* dmMalloc(size_t n){ void* ret = malloc(n); if(ret ==NULL) {printf("malloc err\n");} return ret; }
		template<typename T>
		void dmFree(T*& p){ free(p); p = 0;}
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

/*
 *Use buffer to create temporary file
 *
 */
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

/*
 *Use sort  to create temporary file
 */
template<int HashBit=22>
class OutBuffer2:public OutBufferBase{
	public:
		enum{MAX_HASH_VALUE= (1<< HashBit) -1, HashTableSize= 1<< HashBit, HashTableBytes= HashTableSize*2};
	public:
		OutBuffer2(){ memset(this, 0, sizeof(OutBuffer2));init();}
		OutBuffer2(char* fnin){ memset(this, 0, sizeof(OutBuffer2));init(); setFnInput(fnin);}
		~OutBuffer2(){dmFree(pVH); pVH=0;}
	public:
		void write(int h, Uint idx);
	public:
		void setFnInput(char* fn){ fnInput = strdup(fn);}
		void finish(){ write2file(); mergeFile();}
	private:
		void init(){	mBufferFull = 1024 * 1024 * 16; pVH = (Value_Hash*) dmMalloc(mBufferFull*sizeof(Value_Hash));}
		void distroy();
		void write2file();
		void cleanBeforContinue();
		void mergeFile();
		void merge2File(FILE* dst, FILE* src1, FILE* src2);
		void readHashTable(FILE* fp, Uint* dst){ fseek(fp, IndexFileHeaderSize, SEEK_SET); fread(dst, HashTableSize*sizeof(Uint), 1, fp);};
	protected:
		char* fnInput;
	private:
		size_t curSize;
		size_t mBufferFull;
		int curFileNo;
		union{
			Value_Hash* pVH; //! Size== mBufferFull
			Uint* pInt;
		};
};




#include "buffer.hxx"


/*
 *HashBit = 6
 */
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





#endif   /* ----- #ifndef BUFFER_HEADER__INC  ----- */
