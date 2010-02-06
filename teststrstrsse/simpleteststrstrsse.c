#define REPORT(i) return i
#include "strstrsse.c"
#include "string.h"
typedef char* (*strstr_t)(char* , char*); 
	static void
check (int value, int ref , int number)
{
	int thing = value == ref;
	printf("%0x %0x\n", value ,ref);
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
	check(strstr_alg("abcd", "z") , NULL, 1);    /* Not found. */
	check(strstr_alg("abcd", "abx") , NULL, 2);  /* Dead end. */
	(void) strcpy(one, "abcd");
	check(strstr_alg(one, "c") , one+2, 3);  /* Basic test. */
	check(strstr_alg(one, "bc") , one+1, 4); /* Multichar. */
	check(strstr_alg(one, "d") , one+3, 5);  /* End of string. */
	check(strstr_alg(one, "cd") , one+2, 6); /* Tail of string. */
	check(strstr_alg(one, "abc") , one, 7);  /* Beginning. */
	check(strstr_alg(one, "abcd") , one, 8); /* Exact match. */
	check(strstr_alg(one, "abcde") , NULL, 9);   /* Too long. */
	check(strstr_alg(one, "de") , NULL, 10); /* Past end. */
	check(strstr_alg(one, "") , one, 11);    /* Finding empty. */
	(void) strcpy(one, "ababa");
	check(strstr_alg(one, "ba") , one+1, 12);    /* Finding first. */
	(void) strcpy(one, "");
	check(strstr_alg(one, "b") , NULL, 13);  /* Empty string. */
	check(strstr_alg(one, "") , one, 14);    /* Empty in empty string. */
	check(strstr_alg(one, "bca") , one+2, 15);   /* False start. */
	(void) strcpy(one, "bbbcabbca");
	check(strstr_alg(one, "bbca") , one+1, 16);  /* With overlap. */
}


int main()
{

	test_strstr(strstrsse);
}
