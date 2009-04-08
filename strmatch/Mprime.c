#include <string.h>
#include <stdio.h>
#include <stdio.h>
#define SHIFTSIZE 32768
#define MAXLENGTH 100 
#define Bchar 2
#include "global.h"

void Mwm(char *Tt,char *Patts[],int s)
{
    char prePOINTER[5][MAXLENGTH];
    long preSHIFT[SHIFTSIZE],preHASH[SHIFTSIZE],preFIX[s],preFIND[s];
    long i,px,qx;
    long m,textm,htext,shiftext,prefixtext;
    long pstart,pend;
    long lengthP;
    unsigned char * T;//dzh emend at 2004.10.22
    _U64 sta1,end1;
    double ela;
    T=Tt;
    prePoint(Patts,s,prePOINTER);
     
    textm=strlen(T);
    i=m-1;
    Mtime(&sta1);
    while(i<textm)
    {
    }
    Mtime(&end1);
    ela=Mdifftime(sta1,end1);
    printf("%20.15f,,,,",ela);
}
