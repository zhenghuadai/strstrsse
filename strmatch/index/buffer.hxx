/*
 * =====================================================================================
 *
 *       Filename:  buffer.hxx
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/05/2009 10:36:06 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhenghua Dai (Zhenghua Dai), djx.zhenghua@gamil.com
 *        Company:  dzh
 *
 * =====================================================================================
 */

#ifndef  BUFFER_TEMPLAT_INC
#define  BUFFER_TEMPLAT_INC
#include <unistd.h>
#include "buffer.h"
#define OutBuffer_DEFINITION_HEADER( type ) template<int HashBit> type OutBuffer<HashBit>

OutBuffer_DEFINITION_HEADER(void)::init()
{
	mBufferFull = 1024 * 1024 * 16;
	bucket = new PosList[HashTableSize];	
}

OutBuffer_DEFINITION_HEADER(void)::write(int h, Uint idx)
{
	bucket[h].appand(idx);
	curSize ++;
	if( curSize == mBufferFull){
		write2file();
	}
}

OutBuffer_DEFINITION_HEADER(void):: write2file()
{
	if(curSize ==0) return;
	FILE* fp;
	char fname[512];
	Uint* tmpBuf;
	Uint tmpBufLen;
	tmpBufLen = curSize < HashTableSize?HashTableSize:curSize;
	tmpBuf = new Uint[tmpBufLen];
	sprintf(fname,".%s.index.%d.tmp", fnInput, curFileNo++);
	//if(access(fname, 0)== -1) 
	fwriteHeader(fname);
	fp = fopen(fname, "a");
	
	//! write info 
	for(int i=0;i<HashTableSize;i++)
		tmpBuf[i] =(Uint) bucket[i].size();
	//fseek(fp, 0,SEEK_END);
	::fwrite((void*)tmpBuf,  HashTableSize*sizeof(Uint), 1, fp);

	//! write data
	Uint* pcur=tmpBuf;
	for(int i=0;i<HashTableSize;i++){
		bucket[i].copyTo(pcur);
		pcur+=bucket[i].size();
	}
	//fseek(fp, 0,SEEK_END);
	::fwrite((void*)tmpBuf,  curSize*sizeof(Uint), 1, fp);
	//! update num
	fclose(fp);	

	delete tmpBuf;
}


OutBuffer_DEFINITION_HEADER(void)::cleanBeforContinue()
{
	for(int i=0;i< HashTableSize;i++){
		bucket[i].clean();
	}
	curSize=0;
}


/*************************************************************************
 *
 *
 *************************************************************************/
#define OutBuffer2_DEFINITION_HEADER( type ) template<int HashBit> type OutBuffer2<HashBit>


OutBuffer2_DEFINITION_HEADER(void)::write(int h, Uint idx)
{
	pVH[curSize].set(idx,h);
	curSize ++;
	if( curSize == mBufferFull){
		write2file();
		cleanBeforContinue();
	}
}


OutBuffer2_DEFINITION_HEADER(void):: write2file()
{
	if(curSize ==0) return;
	FILE* fp;
	char fname[512];
	Uint* tmpBuf;
	Uint tmpBufLen;
	//!  sort the pVH
    qsort(pVH, curSize, sizeof(Value_Hash), Value_Hash::compareHash);
	//!
	sprintf(fname,".%s.index.%d.tmp", fnInput, curFileNo++);
	//if(access(fname, 0)== -1) 
	fwriteHeader(fname);
	fp = fopen(fname, "a");
	//! write info 
	Value_Hash* pCurVH = pVH;
	Value_Hash* pEndVH = pVH+curSize;
	for(Uint i=0;i<HashTableSize;i++){
		Uint sum = 0;
		if(pCurVH >= pEndVH){
			if(pCurVH == pEndVH){
				while(i<HashTableSize){fwrite(&sum, 4, 1, fp);i++;}
			}else{
				printf("err\n");
			}
			break;
		}
		if( i == pCurVH->h ){
			while((pCurVH<pEndVH)&&( i== pCurVH->h)) {
				sum++;
				pCurVH++;
			}
			qsort( pCurVH-sum, sum, sizeof(Value_Hash), Value_Hash::compareValue);
		} else if( i< pCurVH->h){
		} else if( i> pCurVH->h){
			printf("%d err\n",i);
		}
		fwrite(&sum, 4, 1, fp);

	}
	//! write data
	for(int i=0;i<curSize; i++) 
		pInt[i] = pInt[2*i];
	fwrite((void*)pInt, curSize*sizeof(int), 1, fp);

	//!
	fclose(fp);


}

OutBuffer2_DEFINITION_HEADER(void)::cleanBeforContinue()
{
	curSize=0;
}







#endif   /* ----- #ifndef BUFFER_INC  ----- */

