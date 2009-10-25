/*
 * =====================================================================================
 *Copyright(C) by Zhenghua Dai. All rights reserved.
 *
 *
 *
 * =====================================
 * =====================================
 *
 *       Filename:  index.h
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

#ifndef  INDEX_HEADER__INC
#define  INDEX_HEADER__INC

#include <stdio.h>
#include <stdlib.h>
#include "dmutil.h"
#include "buffer.h"
class index:public iobuffer
{
    public:
        index(){}
        index(char* fn):iobuffer(fn){}
    public:
};
#endif   /* ----- #ifndef INDEX_HEADER__INC  ----- */
