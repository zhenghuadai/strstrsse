#include <string.h>
#include <stdio.h>
#include <stdio.h>
#define ASIZE 256
extern void output(int num);

void preQsBc(char *pat,int m,int qsBc[])
{
   int i;
   for (i=0;i<ASIZE;++i)
      qsBc[i]=m+1;
   for (i=0;i<m;++i)
      qsBc[pat[i]]=m-i;
}

void Sbmhs2(char * textt,char *patt,int n, int m)//SUNDAY算法，又称 quich search 
{
	int j,qsBc[ASIZE];
	unsigned char *text,*pat;
	text=textt;
	pat=patt;

	/* preprocessing */
	preQsBc(pat,m,qsBc);

	/* Searching */
	j=0;
	while (j<=n-m)
	{
		if (memcmp(pat,text+j,m)==0)
			output(j);
		j+=qsBc[text[j+m]]; //shift
	}
}
void Sbmhs(char * textt,char *patt)//SUNDAY算法，又称 quich search 
{
	int m,n;
	m=strlen(patt);
	n=strlen(textt);
	Sbmhs2(textt,patt,n,m);
}
