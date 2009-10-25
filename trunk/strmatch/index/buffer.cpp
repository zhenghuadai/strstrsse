/*
 * =====================================================================================
 *Copyright(C) by Zhenghua Dai. All rights reserved.
 *
 *
 *
 * ==================================
 * ==================================
 *
 *       Filename:  buffer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年10月25日 12时50分35秒
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
#include "buffer.h"
#include <unistd.h>
void iobuffer::init()
{
    memBuffer = (Uint*) malloc(sizeof(Uint) * 64 * bufSize);    
}

void iobuffer::fwrite(int fileNo)
{
    FILE* fp;
    char fname[512];
    int lastN;
    sprintf(fname,".%s.%d.index", fnInput, fileNo);
    int curlen = curIdx[fileNo] < bufSize? curIdx[fileNo]:bufSize;
    if(access(fname, 0)== -1) 
        fwriteHeader(fname);
    fp = fopen(fname, "r+");
    //! write data
    fseek(fp, 0,SEEK_END);
    ::fwrite((void*)&memBuffer[bufSize*fileNo],  curlen*sizeof(Uint), 1, fp);
    fseek(fp, 0,SEEK_SET);
    //! update num
    fread(&lastN, 4, 1, fp);
    lastN += curlen;
    fseek(fp, 0,SEEK_SET);
    ::fwrite(&lastN, 4, 1, fp);
    fclose(fp);
    curIdx[fileNo] = 0;
}

void iobuffer::write(int h, size_t idx)
{
    memBuffer[bufSize*h + curIdx[h]] = idx;
    curIdx[h] ++;
    if(curIdx[h] == bufSize)
        fwrite(h);
}

void iobuffer::fwriteHeader(char* fn)
{
    FILE* fp= fopen(fn, "w");
    for(int i=0;i<128;i++)
        fputc(0,fp);
    fclose(fp);
}

void iobuffer::finish()
{
    for(int i=0;i< 64;i++){
        if(curIdx[i]>0) 
            fwrite(i);
    }
}
