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
    static unsigned char code[4]={'A','G','C','T'};
    if(n>4) return 'N';
    return code[n];
}

#ifdef __cplusplus
inline
#else
static
#endif
unsigned char agct2num(unsigned char bp){
    switch(bp){
        case 'a': case'A': return 0 ;
        case 'g': case'G': return 1 ;
        case 'c': case'C': return 2 ;
        case 't': case'T': return 3 ;
        default: return 4;
    }
}
// a 97  0110 0001       00
// g 103 0110 0111       01
// c 99  0110 0011       10
// t 116 0111 0100       11
#endif   /* ----- #ifndef UTIL_HEADER__INC  ----- */
