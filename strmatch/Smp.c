#include <string.h>
#include <stdio.h>
#include <stdio.h>
#define XSIZE 100
extern void output(int num);

void  preMp(char *pat,int m,int mpNext[])
{
  int i,j;
  i=0;
  j=mpNext[0]=-1;
  while (i<m)
  {
    while (j>-1 && pat[i]!=pat[j])
      j=mpNext[j];
    mpNext[++i]=++j;
  }
}

void  Smp2(char * text,char *pat, int n, int m)//MP�㷨
{
   int i,j,mpNext[XSIZE];

  
   /* preprocessing */
   preMp(pat,m,mpNext);

   /* searching */
   i=j=0;
   while(j<n)
   {
       while (i>-1 && pat[i]!=text[j])
          i=mpNext[i];
       i++;  j++;
       if (i>=m)
       {
          output(j-i);
          i=mpNext[i];
       }
   }
} 
void  Smp(char * text,char *pat)//MP�㷨
{
   int m,n;
   m=strlen(pat);
   n=strlen(text);
   Smp2(text, pat, n, m);
}