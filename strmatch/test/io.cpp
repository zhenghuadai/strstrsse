/*
 * =====================================================================================
 *Copyright(C) by Zhenghua Dai. All rights reserved.
 *
 *
 *
 * =====================================================================================
 * =====================================================================================
 *
 *       Filename:  io.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2009年10月16日 22时03分07秒
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
#include <unistd.h>
#include <fcntl.h>
#include "dmutil.h"
#include <list>
using namespace std;
Pattern_fasta* loadGeneFasta(char *pfname)
{
    int psubstep=0,buffcounts;
    unsigned int temp;
    char * psub;
    char temp2;
    FILE *pf;	
    struct stat filestat;
    if((pf=fopen(pfname,"r"))==NULL)
    {
        printf("cannot open input string");	
        exit(0);
    }
    buffcounts=stat(pfname,&filestat);
    buffcounts=filestat.st_size;

    /*	//获取文件长度 elementcounts*/
    if (( psub=(char *) malloc(sizeof(char) *(buffcounts+1)))==NULL)
    {
        printf("failure mallocaa      ");
        exit(0);

    }

    Pattern_fasta* pat_fasta = new Pattern_fasta;
    pat_fasta->str = pat_fasta->name = NULL;
    pat_fasta->len = 0;
    
    temp2=fgetc(pf);
    if(temp2 == '>'){
        while(((temp2=fgetc(pf))!='\n') &&(temp2 != EOF)){
            psub[psubstep++]=temp2;
        }
        psub[psubstep]=0;
        char* name = (char*) malloc(psubstep+1);
        strcpy(name, psub);
        pat_fasta->name = name;
    }

    psubstep=0;
    while((temp2=fgetc(pf))!=EOF)
    {
        if( (temp2=='A')||(temp2=='G')||
                (temp2=='C')||(temp2=='T')||
                (temp2=='a')||(temp2=='g')||
                (temp2=='c')||(temp2=='t')||
                (temp2=='n')||(temp2=='N'))
        {
            psub[psubstep++]=temp2;
        }
    }
    psub[psubstep]=0;
    pat_fasta->str = psub;
    pat_fasta->len= psubstep;
    return pat_fasta;

}

int   loadGenePatternFasta(char *pfname, list<Pattern_fasta>* patts)
{
    int psubstep=0,buffcounts;
    //      unsigned int temp;
    char buff[256];
    char * psub;
    char temp2;
    int patno=0,i;
    FILE *pf;	
    char* name = 0;
    char* str = 0;
    if((pf=fopen(pfname,"r"))==NULL)
    {
        printf("cannot open input string");	
        exit(0);
    }

    while((temp2=fgetc(pf))!=EOF)
    {
        if(temp2 == '>'){ //! name
            while(((temp2=fgetc(pf))!='\n') &&(temp2 != EOF)){
                buff[psubstep++]=temp2;
            }
            buff[psubstep]=0;
            name = (char*) malloc(psubstep+1);
            strcpy(name, buff);
        }

        //! str 
        psubstep=0;
        while(((temp2=fgetc(pf))!='\n') &&(temp2 != EOF)){
            if( (temp2=='A')||(temp2=='G')||
                    (temp2=='C')||(temp2=='T')||
                    (temp2=='a')||(temp2=='g')||
                    (temp2=='c')||(temp2=='t')||
                    (temp2=='n')||(temp2=='N'))
            {
                buff[psubstep++]=temp2;
            }
        }
        buff[psubstep]=0;
        str= (char*) malloc(psubstep+1);
        strcpy(str, buff);

        Pattern_fasta pat_fasta;
        pat_fasta.name = name;
        pat_fasta.str = str;
        pat_fasta.len = psubstep;
        patts->push_back(pat_fasta);
        patno ++;
        name = 0;
        str = 0;
    }
    return patno;

}


