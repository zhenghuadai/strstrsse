#include <string.h>
#include <stdio.h>
#include <stdio.h>
extern void output(int num);

void Sprime(char *text,char *pat)
{
  int m,n;
  int i,j;
  int prime[100]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59};
  m=strlen(pat);
  n=strlen(text);

  /* searching */
  for(j=0;j<=n-m;++j)
  {
     for (i=0;i<m&&pat[i]==text[i+j];++i);
     if (i>=m)
      output(j);
  }  
  
}
