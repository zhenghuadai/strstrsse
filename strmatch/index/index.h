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
class index//:public OutBuffer6b
{
    public:
        index(){}
        //index(char* fn):OutBuffer6b(fn){}
        index(char* fn){outBuffer.setFnInput(fn);}
    public:
	protected:
		OutBuffer6b outBuffer6b;
		OutBuffer2<> outBuffer;
};
#endif   /* ----- #ifndef INDEX_HEADER__INC  ----- */
