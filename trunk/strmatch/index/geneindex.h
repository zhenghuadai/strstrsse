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
#include <stdio.h>
#include <stdlib.h>

class geneIndex:public index
{
    public:
        geneIndex(){}
    public:
        void build3();
        void build9();
};
