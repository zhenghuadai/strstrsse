#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include "mem.h"
#define ASIZE 256
#define WORD_SIZE 16
char*  Sbndm2(char * text,char *pat,int n, int m) //Backward Nondeterministic Dawg Matching algorithm
{
	int B[ASIZE];
	int i, j, s, d, last;
	if (m > WORD_SIZE)
		error("BNDM");

	/* Pre processing */
	memset(B,0,ASIZE*sizeof(int));
	s=1;
	for (i=m-1; i>=0; i--){
		B[pat[i]] |= s;
		s <<= 1;
	}

	/* Searching phase */
	j=0;
	while (j <= n-m){
		i=m-1; last=m;
		d = ~0;
		while (i>=0 && d!=0) {
			d &= B[text[j+i]];
			i--;
			if (d != 0){
				if (i >= 0)
					last = i+1;
				else
					OUTPUT(j);
			}
			d <<= 1;
		}
		j += last;
	}
	SRET(j);
}
char*  Sbndm(char * text,char *pat) //Backward Nondeterministic Dawg Matching algorithm
{
	int m, n;
	m=strlen(pat);
	n=strlen(text);
	return   Sbndm2(text, pat, n, m);
}