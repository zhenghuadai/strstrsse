/*
 * =====================================================================================
 *
 *       Filename:  teststrstr.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/22/2008 12:27:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhenghua Dai (Zhenghua Dai), djx.zhenghua@gamil.com
 *        Company:  dzh
 *
 * =====================================================================================
 */
#ifndef MAIN_C
#define MAIN_C
#include <stdio.h>
#include <stdlib.h>
#include "rdtsc.h"
size_t strlen_d(const char *str) ;
size_t strlen_l(const char *str); 
size_t rb_strlen(const char *str); 
char *strstrBerg (const char* phaystack, const char* pneedle);
char *strstrToy (const char* phaystack, const char* pneedle);
char *lstrstr (const char* , const char* );
char *lstrstrsse (const char* , const char* );
char *lstrstr5 (const char* , const char* );
char *qsearch(const char* , const char* );
char* strstra(const char *str,char c);
char *qsearch2(const char *str, int slen, const char *patt, int plen);
typedef char* (*strstr_t)(char* , char*); 
	static void
check (int thing, int number)
{
	if (!thing)
	{
		printf("strstr flunked test %d\n",  number);
	}
}


	static void
test_strstr (strstr_t strstr_alg)
{
	char one[7];
	printf("short test ................................\n");
	check(strstr_alg("abcd", "z") == NULL, 1);    /* Not found. */
	check(strstr_alg("abcd", "abx") == NULL, 2);  /* Dead end. */
	(void) strcpy(one, "abcd");
	check(strstr_alg(one, "c") == one+2, 3);  /* Basic test. */
	check(strstr_alg(one, "bc") == one+1, 4); /* Multichar. */
	check(strstr_alg(one, "d") == one+3, 5);  /* End of string. */
	check(strstr_alg(one, "cd") == one+2, 6); /* Tail of string. */
	check(strstr_alg(one, "abc") == one, 7);  /* Beginning. */
	check(strstr_alg(one, "abcd") == one, 8); /* Exact match. */
	check(strstr_alg(one, "abcde") == NULL, 9);   /* Too long. */
	check(strstr_alg(one, "de") == NULL, 10); /* Past end. */
	check(strstr_alg(one, "") == one, 11);    /* Finding empty. */
	(void) strcpy(one, "ababa");
	check(strstr_alg(one, "ba") == one+1, 12);    /* Finding first. */
	(void) strcpy(one, "");
	check(strstr_alg(one, "b") == NULL, 13);  /* Empty string. */
	check(strstr_alg(one, "") == one, 14);    /* Empty in empty string. */
	check(strstr_alg(one, "bca") == one+2, 15);   /* False start. */
	(void) strcpy(one, "bbbcabbca");
	check(strstr_alg(one, "bbca") == one+1, 16);  /* With overlap. */
}

void printstr(char* s)
{
	int i =0;
	printf(":");
	for(i=0;(s[i]) &&(i<10);i++){
		printf("%c",s[i]);
	}
}
void printstrn(char* s)
{
	int i =0;
	printf(":");
	for(i=0;(s[i]) &&(i<10);i++){
		printf("%c",s[i]);
	}
ret:
	printf("\n");

}
#define LOOPS 1
void test1(int argc,char** argv)
{
	FILE* fp;
	char* text;
	char* textm;
	int len = 1024*1024;
	char pattern[64];
	int testlen[20];
	int i;
	int textlen;
	int patlen;
	double t3;
	char* findp;
	textm = (char*) malloc(len+ 64);
	text = (char*)(((unsigned long long) textm ) & ~63)  +2;
	fp = fopen(argv[1],"r");
	if(fp ==NULL) exit(0);
	textlen=	fread(text,1,1024*1024,fp);
	text[textlen] = 0;
	fclose(fp);
	for(i=0;i<20;i++) testlen[i] =i;
	srand(clock());
	for(patlen = 1;patlen < 20; patlen++){
		int randloops = 0;
		int k;
		printf("*************************************\n");
		printf("%the pattern len is %d \n",patlen);
		randloops = rand() % 5 + 1;
		for(k =0;k < randloops;k++){
			int tmpstart = rand()% textlen;	
			while((tmpstart < textlen )&&(text[tmpstart] != ' ') )
				tmpstart ++;
			tmpstart ++;
			if(tmpstart >= textlen) continue;
			for(i=0; i< patlen; i++)
				pattern[i] = text[tmpstart + i];
			pattern[i] =0;
			printf("the pattern is :%s\n",pattern);

			mdtime(0);
			for(i=0;i<LOOPS;i++)
				findp = lstrstrsse(text,pattern);
			t3=	mdtime(1);
			printf("lstrsse   time:%15f :%d", t3,findp - text);
			printstrn(findp);

			mdtime(0);
			for(i=0;i<LOOPS;i++)
				findp = strstr(text,pattern);
			t3=	mdtime(1);
			printf("strstr    time:%15f :%d", t3,findp - text);
			printstrn(findp);
			printf("\n");
		}
	}

}

static void cmpPerf(const char* text, const char* pattern)
{
	char* findp;
	double t3;
	int i;
	int slen, plen;
	findp = strstr(text,pattern);
	findp = lstrstrsse(text,pattern);
	findp = lstrstr(text,pattern);
	findp = strstr(text,pattern);
	findp = strstrBerg(text,pattern);
	findp = strstrToy(text,pattern);

	printf("\n");
	findp = lstrstr(text,pattern);
	mdtime(0);
	for(i=0;i<LOOPS;i++)
		findp = lstrstr(text,pattern);
	t3=	mdtime(1);
	printf("lstrstr   time:%15f :%d", t3,findp - text);
	printstrn(findp);

	findp = lstrstrsse(text,pattern);
	mdtime(0);
	for(i=0;i<LOOPS;i++)
		findp = lstrstrsse(text,pattern);
	t3=	mdtime(1);
	printf("lstrsse   time:%15f :%d", t3,findp - text);
	printstrn(findp);

	findp = strstr(text,pattern);
	mdtime(0);
	for(i=0;i<LOOPS;i++)
		findp = strstr(text,pattern);
	t3=	mdtime(1);
	printf("strstr    time:%15f :%d", t3,findp - text);
	printstrn(findp);

	findp = strstrBerg(text,pattern);
	mdtime(0);
	for(i=0;i<LOOPS;i++)
		findp = strstrBerg(text,pattern);
	t3=	mdtime(1);
	printf("Bstrstr   time:%15f :%d", t3,findp - text);
	printstrn(findp);

	findp = strstrToy(text,pattern);
	mdtime(0);
	for(i=0;i<LOOPS;i++)
		findp = strstrToy(text,pattern);
	t3=	mdtime(1);
	printf("strstrToy time:%15f :%d", t3,findp - text);
	printstrn(findp);

	findp = qsearch(text,pattern);
	mdtime(0);
	for(i=0;i<LOOPS;i++)
		findp = qsearch(text,pattern);
	t3=	mdtime(1);
	printf("strstrBm  time:%15f :%d", t3,findp - text);
	//printstrn(findp);
	printf("\n");

	findp = qsearch2(text,strlen(text),pattern,strlen(pattern));
	slen = strlen(text);
	plen = strlen(pattern);
	mdtime(0);
	for(i=0;i<LOOPS;i++)
		findp = qsearch2(text,slen,pattern,plen);
	t3=	mdtime(1);
	printf("strstrBm2 time:%15f :%d", t3,findp - text);
	//printstrn(findp);
	printf("\n");


}

/**************************************************
 * test performance
 * ************************************************/
void cmpStrlen(const char* text)
{
	int i,len;
	double t3;
	printf("test strlen\n");

	mdtime(0);
	for(i=0;i<LOOPS;i++)
		len = strlen_d(text);
	t3=	mdtime(1);
	printf("strlen(int)  time:%f :%d\n", t3,len);

	mdtime(0);
	for(i=0;i<LOOPS;i++)
		len = strlen(text);
	t3=	mdtime(1);
	printf("strlen       time:%f :%d\n", t3,len);

	mdtime(0);
	for(i=0;i<LOOPS;i++)
		len = strlen_l(text);
	t3=	mdtime(1);
	printf("strlen(long) time:%f :%d\n", t3,len);

	mdtime(0);
	for(i=0;i<LOOPS;i++)
		len = rb_strlen(text);
	t3=	mdtime(1);
	printf("strlen(SSE)  time:%f :%d\n", t3,len);

}
int test2( int argc, char** argv)
{
#include "defaultText.h"
	char text0[] = TEXT; 
	char* patterns[] = {"vulture","emente", "MArs","dog","Z","ABG","do","AGB"};				 
	char* pattern=patterns[0];
	char* findp;
	char* textm;
	char* text;
	double t3;
	int len = 1024*1024;//strlen(text0);
	int i;
	int slen, plen;
	textm = (char*) malloc(len+ 64);
	text = (char*)(((unsigned long long) textm ) & ~63)  ;
	strcpy(text,text0);
	cmpPerf(text, pattern);
	cmpStrlen(text);
}

int testWorse(int len)
{
	char* text;
	char* pattern[]={"AB", "AAB","AAAB", "AAAAB"};
	printf("text len = %d\n",len);
	text = (char*)malloc(len);
	memset(text,'A', len);
	text[len-1] = 0;
	text[len-2] = 'B';
	printf("test AB\n");
	cmpPerf(text,pattern[0]);
	printf("test AAB\n");
	cmpPerf(text,pattern[1]);
	printf("test AAAB\n");
	cmpPerf(text,pattern[2]);
	printf("test AAAAB\n");
	cmpPerf(text,pattern[3]);
}

void testBoundary()
{
	//char* text = (char*)malloc(13);
	//unsigned int len = *(((unsigned int*) text) -2);
	char* text = "1234567812345678mytest";
	char* pat= "est";
	char* findp;
	printf("test boundary.............................\n");
	findp= lstrstrsse(text,pat);
	printstrn(findp);


}
/*******************************************
 *
 * ******************************************/
int test3(int argc, char** argv)
{
#include "defaultText.h"
	char text0[] = TEXT; 
	char* patterns[] = {"vulture","emente", "MArs","dog","Z","ABG","do","AGB"};				 
	char* pattern=patterns[0];
	char* findp;
	char* textm;
	char* text;
	double t3;
	int i;
	int len = 1024*1024;//strlen(text0);
	int slen, plen;
	textm = (char*) malloc(len+ 64);
	text = (char*)(((unsigned long long) textm ) & ~63)  ;
	strcpy(text,text0);

	findp = strstr(text,pattern);
	printf("strstr    %d", findp - text);
	printstrn(findp);
	for(i=0;i<34;i++) 
	{
		int j=0;
		for(j=0;j<i;j++) text[i] = 'a';
		strcpy(text+i,text0);
		mdtime(0);
		findp = lstrstrsse(text,pattern);
		t3=	mdtime(1);
		printf("(%15f :%d:", t3,findp - text);
		printstr(findp);
		printf(")");
		if(i%4 == 0) printf("\n");


	}

	printf("\n");
	testBoundary();
	test_strstr(lstrstrsse);
}

int main( int argc, char** argv)
{
	int len;
	printf("Performance test ................\n");
	test2(argc,argv);
	printf("worse test ................\n");
	testWorse(1024*64);
	testWorse(8);
	testWorse(16);
	testWorse(32);
	testWorse(48);
	printf("functional test ................\n");
	test3(argc,argv);
	//test1(argc,argv);
	return 1;
}
#endif
