#include <string.h>
#include <stdio.h>
#include <stdio.h>
#define ASIZE 256
extern void output(int num);

void  Sbmh(char * textt,char *patt) // HorspoolÀ„∑® 
{
  int m,n;
  int j,bmBc[ASIZE];
  unsigned char c;
  unsigned char * text,*pat;
  text=textt;
  pat=patt;
  m=strlen(pat);
  n=strlen(text);

  /* preprocessing */
  preBmBc(pat,m,bmBc);
  /* searching */
  j=0;
  while (j<=n-m)
  {
     c=text[j+m-1];
     if (pat[m-1]==c && memcmp(pat,text+j,m-1)==0)
        output(j);
     j+=bmBc[c];
  }
}
