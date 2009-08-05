#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#define ASIZE 256
#define MAX(a,b) (a>b)?a:b


char*  Ssmith2(char * textt,char *patt,int n, int m)//smith Ëã·¨ 
{
	int j,bmBc[ASIZE],qsBc[ASIZE];
	unsigned char * text,*pat;
	text=textt;
	pat=patt;


	/* preprocessing */
	preBmBc(pat,m,bmBc);
	preQsBc(pat,m,qsBc);

	/* searching */
	j=0;
	while (j<=n-m)
	{
		if (memcmp(pat,text+j,m)==0)
			OUTPUT(j);
		j+=MAX(bmBc[text[j+m-1]],qsBc[text[j+m]]);
	}
	SRET(j);
}
char*  Ssmith(char * textt,char *patt)//smith Ëã·¨ 
{
	int m,n;
	m=strlen(patt);
	n=strlen(textt);
	return 	Ssmith2(textt, patt, n ,m);
}
