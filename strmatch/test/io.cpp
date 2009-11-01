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
#include <string.h>
#include "io.h"
using namespace std;
#define EQ5(d, a0, a1, a2, a3, a4) ( (d==a0) || (d==a1) ||(d==a2) ||(d==a3) ||(d==a4) )
template<CASE_TYPE case_type>
Pattern_fasta* loadGene_fasta(char *pfname)
{
    int psubstep=0,buffcounts;
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
        if( EQ5(temp2, 'A', 'G','C','T','N')){
            psub[psubstep++]=temp2 + case_num<case_type>::low_case;
        }else if(EQ5(temp2, 'a', 'g','c','t','n')){
            psub[psubstep++]=temp2 - case_num<case_type>::upper_case;
        }
    }
    psub[psubstep]=0;
    pat_fasta->str = psub;
    pat_fasta->len= psubstep;
    return pat_fasta;

}

template Pattern_fasta* loadGene_fasta<NORMAL_CASE>(char *pfname);
template Pattern_fasta* loadGene_fasta<LOWER_CASE >(char *pfname);
template Pattern_fasta* loadGene_fasta<UPPER_CASE >(char *pfname);

    template<CASE_TYPE case_type>
int   loadGenePattern_Fasta(char *pfname, list<Pattern_fasta>* patts)
{
    int psubstep=0;
    //      unsigned int temp;
    char buff[256];
    char temp2;
    int patno=0;
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
            psubstep=0;
        }else {
            psubstep=0;
            buff[psubstep++]=temp2;
        }

        //! str 
        while(((temp2=fgetc(pf))!='\n') &&(temp2 != EOF)){
            if( EQ5(temp2, 'A', 'G','C','T','N')){
                buff[psubstep++]=temp2 + case_num<case_type>::low_case;
            }else if(EQ5(temp2, 'a', 'g','c','t','n')){
                buff[psubstep++]=temp2 - case_num<case_type>::upper_case;
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

template int loadGenePattern_Fasta<NORMAL_CASE>(char *pfname, list<Pattern_fasta>* patts);
template int loadGenePattern_Fasta<LOWER_CASE >(char *pfname, list<Pattern_fasta>* patts);
template int loadGenePattern_Fasta<UPPER_CASE >(char *pfname, list<Pattern_fasta>* patts);

char** transList1(list<Pattern_fasta>* tList)
{
    int len = tList->size();
    char** patternList = (char**) malloc(len *sizeof(char*));
    int i;
    list<Pattern_fasta>::iterator it;
    for(it=tList->begin(), i=0; it!=tList->end(); it++, i++){
        patternList[i] = (*it).str;
    }
    return patternList;
}

Pattern_fasta* transList2(list<Pattern_fasta>* tList)
{
    int len = tList->size();
    Pattern_fasta* patternList = (Pattern_fasta*) malloc(len *sizeof(Pattern_fasta*));
    int i;
    list<Pattern_fasta>::iterator it;
    for(it=tList->begin(), i=0; it!=tList->end(); it++, i++){
        patternList[i] = (*it);
    }
    return patternList;
}
