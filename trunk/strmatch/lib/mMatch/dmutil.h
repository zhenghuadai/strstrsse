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

#ifdef __cplusplus
inline
#else
static
#endif
unsigned char num2agct(unsigned char n){
    static unsigned char code[4]={'A','C','T','G'};
    if(n>4) return 'N';
    return code[n];
}

#ifdef __cplusplus
inline
#else
static
#endif
unsigned char agct2num(unsigned char bp){
#if 1
    return ((bp>>1) & 7);
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
// a 97  0110 0001       00
// c 99  0110 0011       01
// t 116 0111 0100       10
// g 103 0110 0111       11
// a 65  0100 0001       00
// c 67  0100 0011       01
// t 84  0101 0100       10
// g 71  0100 0111       11
//
// N 78  0100 1110
#endif   /* ----- #ifndef UTIL_HEADER__INC  ----- */
