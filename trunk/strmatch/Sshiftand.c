#include <string.h>
#include <stdio.h>
#include <stdio.h>
 //Shift and algorithm
#include"global.h"
int preSa(char *x, int m, unsigned int S[]) { 
	unsigned int j, lim; 
	int i; 
	for (i = 0; i < ASIZE; ++i) 
		S[i] = 0; 
	for (lim = i = 0, j = 1; i < m; ++i, j <<= 1) { 
		S[x[i]] |= j; 
		lim |= j; 
	} 
	lim = ~(lim>>1); 
	return(lim); 
} 

void Sshiftand2(char *text,char *pat,int n, int m) { 
	unsigned int lim, state; 
	unsigned int S[ASIZE];
	int j; 
	if (m > WORD_SIZE) 
		error("SO: Use pattern size <= word size"); 

	/* Preprocessing */ 
	lim = preSa(pat, m, S); 

	/* Searching */ 
	for (state =~0, j = 0; j < n; ++j) { 
		state = (state<<1) | (~S[text[j]]); 
		if (state < lim) 
			output(j - m + 1); 
	} 
} 

void Sshiftand(char *text,char *pat) 
{
	int m,n;
	m=strlen(pat);
	n=strlen(text); 
	Sshiftand2(text, pat, n, m);
}
