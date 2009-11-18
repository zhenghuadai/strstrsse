/*
 * =====================================================================================
 *Copyright(C) by Zhenghua Dai. All rights reserved.
 *
 *
 *
 * =====================================================================================
 * =====================================================================================
 *
 *       Filename:  util.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年10月15日 19时01分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhenghua Dai (Zhenghua Dai), djx.zhenghua@gmail.com
 *        Company:  dzh
 *
 * =====================================================================================
 */
#ifndef  UTIL_HEADER__INC
#define  UTIL_HEADER__INC

#if __amd64 || __x86_64
    #define BIT_64 1 	
#else
    #define BIT_64 0 	
#endif
typedef unsigned char Uchar;
typedef unsigned short U16;
typedef unsigned int Uint;
typedef short I16;
#if BIT_64 == 1
typedef long long SSize;
#else 
typedef int SSize;
#endif


#ifdef __cplusplus
#define __INLINE__ inline
#else
#define __INLINE__ static
#endif

struct Pattern_s{
    char* str;
    int len;
};
typedef struct Pattern_s Pattern_t;

struct Pattern_fasta{
    char* str;
    char* name;
    int len;
};
typedef struct Pattern_fasta Pattern_fasta;

// a 97  0110 0001       00
// c 99  0110 0011       01
// t 116 0111 0100       10
// g 103 0110 0111       11
// a 65  0100 0001       00
// c 67  0100 0011       01
// t 84  0101 0100       10
// g 71  0100 0111       11
// N 78  0100 1110

typedef Uchar (*geneCodeFunc)(Uchar);

__INLINE__
unsigned char agct2pair(unsigned char bp){
	switch(bp){
		case 'a': case'A': return 'T' ;
		case 'c': case'C': return 'G' ;
		case 't': case'T': return 'A' ;
		case 'g': case'G': return 'C' ;
		default: return bp;
		break;
	}
}


__INLINE__
unsigned char num2agct(unsigned char n){
	static unsigned char code[4]={'A','C','T','G'};
	if(n>4) return 'N';
	return code[n];
}

__INLINE__
unsigned char agct2num(unsigned char bp){
#if 1
    if(bp == 'N' || bp == 'n') return 4;
	return ((bp>>1) & 3);
#else
	switch(bp){
		case 'a': case'A': return 0 ;
		case 'c': case'C': return 1 ;
		case 't': case'T': return 2 ;
		case 'g': case'G': return 3 ;
		default: return 4;
	}
#endif
}

__INLINE__ 
unsigned char agct2pairnum(unsigned char bp)
{
	return agct2num(agct2pair(bp));
}

__INLINE__
unsigned int geneHash3(const unsigned char* bp){
	unsigned char c0= agct2num(bp[0]);
	unsigned char c1= agct2num(bp[1]);
	unsigned char c2= agct2num(bp[2]);
	if((c0|c1|c2 )& 4) return -1;
	return (c2<<4 |(c1<<2) | (c0));
}

__INLINE__
unsigned int geneHash3Next(int h, const unsigned char bp){
	return (h>>2) | (agct2num(bp)<<4);	
}

__INLINE__
unsigned int geneHash8(const unsigned char* bp){
	unsigned char c0= agct2num(bp[0]);
	unsigned char c1= agct2num(bp[1]);
	unsigned char c2= agct2num(bp[2]);
	unsigned char c3= agct2num(bp[3]);
	unsigned char c4= agct2num(bp[4]);
	unsigned char c5= agct2num(bp[5]);
	unsigned char c6= agct2num(bp[6]);
	unsigned char c7= agct2num(bp[7]);
	if((c0|c1|c2|c3|c4|c5|c6|c7) &4 ) return -1;
	return ((c7<<14) |(c6<<12) | (c5<<10) |
			(c4<<8 ) |(c3<<6 ) | (c2<<4 ) |
			(c1<<2 ) |(c0<<0 )  
		   );
}

__INLINE__
unsigned int geneHash8Next(int h, const unsigned char bp){
	return (h>>2) | (agct2num(bp)<<14);	
}

__INLINE__
unsigned int geneHash9(const unsigned char* bp){
	unsigned char c0= agct2num(bp[0]);
	unsigned char c1= agct2num(bp[1]);
	unsigned char c2= agct2num(bp[2]);
	unsigned char c3= agct2num(bp[3]);
	unsigned char c4= agct2num(bp[4]);
	unsigned char c5= agct2num(bp[5]);
	unsigned char c6= agct2num(bp[6]);
	unsigned char c7= agct2num(bp[7]);
	unsigned char c8= agct2num(bp[8]);
	if((c0|c1|c2|c3|c4|c5|c6|c7|c8) &4 ) return -1;
	return ((c8<<16) |(c7<<14) |(c6<<12) |
			(c5<<10) |(c4<<8 ) |(c3<<6 ) |
			(c2<<4 ) |(c1<<2 ) |(c0<<0 )  
		   );
}

__INLINE__
unsigned int geneHash9Next(int h, const unsigned char bp){
	return (h>>2) | (agct2num(bp)<<16);	
}

__INLINE__
unsigned int geneHash11(const unsigned char* bp){
	unsigned char c0= agct2num(bp[0]);
	unsigned char c1= agct2num(bp[1]);
	unsigned char c2= agct2num(bp[2]);
	unsigned char c3= agct2num(bp[3]);
	unsigned char c4= agct2num(bp[4]);
	unsigned char c5= agct2num(bp[5]);
	unsigned char c6= agct2num(bp[6]);
	unsigned char c7= agct2num(bp[7]);
	unsigned char c8= agct2num(bp[8]);
	unsigned char c9= agct2num(bp[9]);
	unsigned char c10= agct2num(bp[10]);
	if((c0|c1|c2|c3|c4|c5|c6|c7|c8|c9|c10) &4 ) return -1;
	return ((c10<<20) |(c9<<18) |
			(c8<<16 ) |(c7<<14) |(c6<<12) |
			(c5<<10 ) |(c4<<8 ) |(c3<<6 ) |
			(c2<<4  ) |(c1<<2 ) |(c0<<0 )  
		   );
}

__INLINE__
unsigned int geneHash11Next(int h, const unsigned char bp){
	return (h>>2) | (agct2num(bp)<<20);	
}


__INLINE__
unsigned int geneHashWm8(const unsigned char* bp){
	return geneHash8(bp-8);
}

//
//__INLINE__
//unsigned int geneHash9(char* bp){
//  return  geneHash9((unsigned char*)bp);
//}
#undef __INLINE__ 
#endif   /* ----- #ifndef UTIL_HEADER__INC  ----- */
