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
#include "dmutil.h"
class iobuffer
{
    public:
        enum{ bufSize = 1024*64};
    public:
        iobuffer(){ memset(this, 0, sizeof(iobuffer));init();}
    public:
        void write(int h, Uint idx);
    public:
        void init();
        void distroy();
        void fwrite(int fileNo);
    protected:
        void finish();
    protected:
        FILE* fpin;
        FILE* fpDataBase;
        FILE* fpLog;
        Uint* memBuffer; 
        int* buffer[64];
        int curIdx[64];
        char* fnDataBase;

};
#endif   /* ----- #ifndef BUFFER_HEADER__INC  ----- */
