#include <string.h>
#include <stdio.h>
#include <stdio.h>
#define ASIZE 256
#define MAX(a,b) (a>b)?a:b
extern void output(int num);

void  Ssmith(char * textt,char *patt)//smith �㷨 
{
  int m,n;
  int j,bmBc[ASIZE],qsBc[ASIZE];
   unsigned char * text,*pat;
    text=textt;
     pat=patt;
     
  m=strlen(pat);
  n=strlen(text);

  /* preprocessing */
  preBmBc(pat,m,bmBc);
  preQsBc(pat,m,qsBc);
 
  /* searching */
  j=0;
  while (j<=n-m)
  {
    if (memcmp(pat,text+j,m)==0)
      output(j);
    j+=MAX(bmBc[text[j+m-1]],qsBc[text[j+m]]);
  }
}