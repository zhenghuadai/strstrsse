/*
 * =====================================================================================
 *
 *       Filename:  mAc.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/13/2009 12:23:55 PM
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
#include <queue>

#include "mAc.h"
namespace dmMatch{
#if defined(__GNUC__)
# 	define nasm0(op) __asm__( #op)
#else      /* -----  not  defined(__GNUC__)----- */
# 	define nasm0(op) __asm op 
#endif     /* -----  not  defined(__GNUC__)----- */

    static inline unsigned long long getrdtsc(){
        nasm0(rdtsc);
    }
    unsigned long long mMatch::startTime()
    {
        unsigned long long  tTimeStart = getrdtsc(); 
        mTimeStart = tTimeStart;
        return tTimeStart;
    };
    unsigned long long mMatch::endTime()
    {
        unsigned long long  tTimeEnd = getrdtsc();
        mTimeEnd = tTimeEnd;
        return tTimeEnd;
    };
}
