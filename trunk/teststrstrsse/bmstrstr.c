#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#if 0
char *qsearch2(const char *str, int slen, const char *patt, int plen)
{
	const char *s, *p, *tx = str;
	static int td[128],c=0;
	/*************预处理*****************************/
	for ( ++plen; c < 128; ++c) //建立表
		td[c] = plen ;
	--plen;          //复原

	for (p=patt; *p; p++) //初始化表
		td[*p] = plen - (p - patt);//m-(p-patt)即失配时模式串右移的步数

	/***************模式匹配开始*********************/
	while ( (s=tx+plen-1) <= str+slen-1) {
		for (p = patt+plen-1; *p == *s; --s)
			--p;
		if (*p == 0)  // 找到并返回
			return (char*)tx;
		tx += td[tx[plen]]; // 模式右移
	}
	return NULL;
} 

char *qsearch(const char *str, const char *patt)
{
	int slen = strlen(str);
	int plen = strlen(patt);
return 	qsearch2(str,slen,patt,plen);
}
#endif

#if 1
#define ASIZE 256
void preBmBc(char *pat, int m, int bmBc[]) {
	int i;

	for (i = 0; i < ASIZE; ++i)
		bmBc[i] = m;
	for (i = 0; i < m - 1; ++i)
		bmBc[pat[i]] = m - i - 1;
}

char* Sbmh(char * textt,char *patt) // HorspoolËã·¨ 
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
			return text +j;
		j+=bmBc[c];
	}
}

char *qsearch2(const char *textt, int slen, const char *patt, int plen)
{
		int m,n;
	int j,bmBc[ASIZE];
	unsigned char c;
	unsigned char * text,*pat;
	text=textt;
	pat=patt;
	n = slen;
	m = plen;
	/* preprocessing */
	preBmBc(pat,m,bmBc);
	/* searching */
	j=0;
	while (j<=n-m)
	{
		c=text[j+m-1];
		if (pat[m-1]==c && memcmp(pat,text+j,m-1)==0)
			return text +j;
		j+=bmBc[c];
	}

}

char *qsearch(const char *str, const char *patt)
{
	int slen = strlen(str);
	int plen = strlen(patt);
	return 	qsearch2(str,slen,patt,plen);
}
#endif
