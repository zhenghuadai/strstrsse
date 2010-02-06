/*
 * =====================================================================================
 *
 *       Filename:  lstrstr.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/22/2008 12:27:45 PM
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
#include <emmintrin.h>
#include <xmmintrin.h>
#include "strstrsse.h"
char* lstrchr(const char *str,char c);
char* lstrstrabsse(char* text, char* pattern);
//#define REPORT(i) return i;
#define REPORT(i) {if( report_function(text, i-text, pattern)== SEARCH_STOP) return i;};

static inline unsigned int hasByteC(__m128i a0, __m128i a1, register __m128i sseic)
{
	return ((_mm_movemask_epi8(_mm_cmpeq_epi8(a0,sseic))  )  | \
			(_mm_movemask_epi8(_mm_cmpeq_epi8(a1,sseic)) << 16) \
		   );	
}

static inline unsigned int hasByteC1(__m128i a0, register __m128i sseic)
{
	return _mm_movemask_epi8(_mm_cmpeq_epi8(a0,sseic))   ;
}


#define haszeroByte hasByteC
#define haszeroByte1 hasByteC1
inline static int strcmpInline(char* str1,char* str2)
{
	while((*str2) && (*str1 == * str2)) {
		str1++;
		str2++;
	}
	if(*str2 == 0) return 0;
	return 1;
}

#    define bsf(x) __builtin_ctz(x) 
char* lstrstrsseLong(const char* text, const char* pattern)
{
	__m128i * sseiPtr = (__m128i *) text;
	unsigned char * chPtrAligned = (unsigned char*)text;
	__m128i sseiWord0 ;//= *sseiPtr ;
	__m128i sseiWord1 ;//= *sseiPtr ;
	__m128i sseiZero = _mm_set1_epi8(0);
	char chara = pattern[0];
	char charb = pattern[1];
	char charc = pattern[4];
	unsigned int reta=0;
	unsigned int retb=0;
	unsigned int retc=0;
	register __m128i byte16a;
	register __m128i byte16b;
	register __m128i byte16c;
	char* bytePtr =text;
	int m =strlen(pattern);
	if(m < 5) 
		return strstrsse(text, pattern);
	byte16a = _mm_set1_epi8(chara);
	byte16b = _mm_set1_epi8(charb);
	byte16c = _mm_set1_epi8(charc);
#if 1
	//! the pre-byte that is not aligned.
	{
		int i;
		int j;
		int preBytes = 16 - (((unsigned long long) text) & 15);
		preBytes &= 15;
		if (preBytes == 0) goto alignStart;
		chPtrAligned = (unsigned char*)text + preBytes;
		for(j =0;j< preBytes; j++){
			if(text[j] ==0) return NULL;
			if(text[j] == chara){
				if(text[j+1] == charb){
					int i=1;
					bytePtr = & text[j];
					while((pattern[i] )&&(bytePtr[i] == pattern[i])) i++;
					if(pattern[i] == 0) REPORT(bytePtr);
					if(bytePtr[i] == 0) return NULL;
				}
			}
		}
		sseiPtr = (__m128i *) chPtrAligned;
	}


#endif
alignStart:
	sseiWord0 = *sseiPtr++;
	reta = haszeroByte1(sseiWord0, byte16a);
	sseiWord1 = *(sseiPtr);
	while( haszeroByte1(sseiWord1,sseiZero) ==0) 
	{
		if(reta ==0){
			reta = haszeroByte1(sseiWord1, byte16a);
			retb =0;
			retc=0;
		}else{
			unsigned int retabc;
			reta = (reta) | haszeroByte1(sseiWord1, byte16a);
			retb = (retb) | haszeroByte1(sseiWord1, byte16b);
			retc = (retc) | haszeroByte1(sseiWord1, byte16c);
			retabc = (retc>>4) & (retb >>1) & reta & 65535;
			if(retabc){ 
				int i=1;
				char * bytePtr0 = (char*) ( sseiPtr-1 );
				int j;
				while(retabc){
					int idx ;
					idx = bsf(retabc);
					bytePtr = bytePtr0 + idx ;
					i = 3;
					while((pattern[i] )&&(bytePtr[i] == pattern[i])) i++;
					if(pattern[i] == 0) REPORT(bytePtr);
					retabc = retabc & ( ~(1<<idx));
				}
			}
			reta >>=16;	
			retb >>=16;	
			retc >>=16;	
		}
		sseiWord0= sseiWord1;
		sseiPtr ++;
		sseiWord1 = *sseiPtr;
	}
prePareForEnd:
	{
		unsigned int reta;
		unsigned int retb;
		reta =hasByteC(sseiWord0,sseiWord1,  byte16a);
		retb =hasByteC(sseiWord0,sseiWord1,  byte16b);
		if(((reta<<1) & retb)){
			bytePtr = (char*)sseiPtr;
			while(*bytePtr){
				if(*bytePtr == chara) {
					int i=1;
					while((pattern[i] )&&(bytePtr[i] == pattern[i])) i++;
					if(pattern[i] == 0) REPORT(bytePtr);
					if(bytePtr[i] == 0) return NULL;

				}
				bytePtr++;
			}
		}
	}
	return NULL;
}

