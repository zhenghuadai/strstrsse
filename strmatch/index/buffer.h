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

#ifndef  BUFFER_HEADER__INC
#define  BUFFER_HEADER__INC

class iobuffer
{
    public:
        iobuffer(){}
    public:
        void write(int h, size_t idx){printf("(%d %d)", h, idx);}

    protected:
        FILE* fpin;
        FILE* fpDataBase;
        FILE* fpLog;

};
#endif   /* ----- #ifndef BUFFER_HEADER__INC  ----- */
