/*
 * =====================================================================================
 *Copyright(C) by Zhenghua Dai. All rights reserved.
 *
 *
 *
 * ==================================
 * ==================================
 *
 *       Filename:  geneindex.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年10月25日 10时50分08秒
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
#include "geneindex.h"
void geneIndex::build3(const char* genome, size_t startIdx, size_t len)
{
    const unsigned char* p =(const unsigned char*) genome;
    int i;
    Uint h = geneHash3(p) >> 2;
    for(i=0,p+=2; i <len;i++, p++){
        //h = ((h << 2) |  agct2num(*(p))) &( 63);
		h = geneHash3Next(h, *p);
        write(h, startIdx+i);
    }
    finish();
}

void geneIndex::build3(const char* genome, size_t startIdx)
{
    const unsigned char* p =(const unsigned char*) genome;
    int i;
    Uint h = geneHash3(p) >> 2;
    for(i=0,p+=2; *p;i++, p++){
		h = geneHash3Next(h, *p);
        write(h, startIdx+i);
    }
    finish();
}


void geneIndex::build9(const char* genome, size_t startIdx, size_t len)
{
    const unsigned char* p =(const unsigned char*) genome;
    int i;
    Uint h = geneHash9(p) >> 2;
    for(i=0,p+=8;i <len;i++, p++){
		h = geneHash9Next(h, *p);
        write(h, startIdx+i);
    }
}
