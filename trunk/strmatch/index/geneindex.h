/*
 * =====================================================================================
 *Copyright(C) by Zhenghua Dai. All rights reserved.
 *
 *
 *
 * =====================================================================================
 * =====================================================================================
 *
 *       Filename:  geneindex.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年10月22日 20时20分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhenghua Dai (Zhenghua Dai), djx.zhenghua@gmail.com
 *        Company:  dzh
 *
 * =====================================================================================
 */

#ifndef  GENEINDEX_HEADER__INC
#define  GENEINDEX_HEADER__INC
#include <stdio.h>
#include <stdlib.h>
#include "index.h"
class geneIndex:public index
{
    public:
        geneIndex(){}
        geneIndex(char* fn):index(fn){}
    public:
        void build3();
        void build9();
        void build3(const char* genome, size_t startIdx, size_t len);
        void build3(const char* genome, size_t startIdx);
        void build9(const char* genome, size_t startIdx=0, size_t len=0);
    private:
};
#endif   /* ----- #ifndef GENEINDEX_HEADER__INC  ----- */
