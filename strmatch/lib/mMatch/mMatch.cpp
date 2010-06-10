/*
 * =====================================================================================
 *     Copyright(C) by Zhenghua Dai. All rights reserved.
 *
 *
 *
 * -------------------------------------------------------------------------------------
 *
 *       Filename:  mMatch.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年10月13日 18时55分33秒
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
#include "mMatch.h"
namespace dmMatch{

void mMatch::setPatterns(char** pat, int n)
{
    this->mPatterns = pat;
    this->mPatNum = n;
	mPatLen =(int*) malloc( n* sizeof(int)) ;
	for(int i=0;i<n;i++) mPatLen[i] = strlen(pat[i]);
}


}
