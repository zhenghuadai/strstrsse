#ifndef STRINGMATCH_HEADER__
#define STRINGMATCH_HEADER__
#define MAXPAT 256 //the maximal length of Pattern

#define CHARACTERS 256 //the length of   set of character  
#define ASIZE 256
#define WORD_SIZE 16
#define MAXINT2 2147483648 
#include "stdio.h"
#include "stdlib.h"
char* Sbf		(char * text,char *pat);//brute force 算法 
char* bfstr		(char * text,char *pat);
char* Smp		(char * text,char *pat);//MP算法 
char* Skmp		(char * text,char *pat); //KMP算法

char* Sbm		(char * text,char *pat) ;//bm算法 
char* Sbmh		(char * text,char *pat);// Horspool算法 
char* Sbmhs		(char * text,char *pat);//SUNDAY算法，又称 quich search 
char* Ssmith		(char * text,char *pat);//smith 算法 

char* Sdfa		(char * text,char *pat);//基本的自动机算法 
char* Sbdm		(char * text,char *pat);//Forward Dawg Matching algorithm 
char* Sbndm		(char * text,char *pat);//Forward Dawg Matching algorithm 
char* Sbom		(char * text,char *pat);//BOM算法 
char* Sshiftor	(char * text,char *pat);//shift-or 算法 
char* Sshiftand	(char * text,char *pat);//shift-and 算法 
char* SshiftorW	(char * text,char *pat);//shift-or 算法 

char* Skr		(char * text,char *pat);//KR算法 

char* Sbyh		(char * text,char *pat);//计数算法 
 
char* Sskip		(char * text,char *pat);//跳跃算法 
char* Skmpskip	(char * text,char *pat);// kmp跳跃算法 
char* bfstr		(char * text,char *pat);// gcc 

/*  下面为单模式串精确匹配算法 ，函数名以S开头，第一个参数为目标串，第二个参数为模式串*/
char* Sbf2		(char * text,char *pat, int n, int m);//brute force 算法 
char* bfstr2		(char * text,char *pat, int n, int m);
char* Smp2		(char * text,char *pat, int n, int m);//MP算法 
char* Skmp2		(char * text,char *pat, int n, int m); //KMP算法

char* Sbm2		(char * text,char *pat, int n, int m) ;//bm算法 
char* Sbmh2		(char * text,char *pat, int n, int m);// Horspool算法 
char* Sbmhs2		(char * text,char *pat, int n, int m);//SUNDAY算法，又称 quich search 
char* Ssmith2	(char * text,char *pat, int n, int m);//smith 算法 

char* Sdfa2		(char * text,char *pat, int n, int m);//基本的自动机算法 
char* Sbdm2		(char * text,char *pat, int n, int m);//Forward Dawg Matching algorithm 
char* Sbndm2		(char * text,char *pat, int n, int m);//Forward Dawg Matching algorithm 
char* Sbom2		(char * text,char *pat, int n, int m);//BOM算法 
char* Sshiftor2	(char * text,char *pat, int n, int m);//shift-or 算法 
char* Sshiftand2	(char * text,char *pat, int n, int m);//shift-and 算法 
char* SshiftorW2	(char * text,char *pat, int n, int m);//shift-or 算法 

char* Skr2		(char * text,char *pat, int n, int m);//KR算法 

char* Sbyh2		(char * text,char *pat, int n, int m);//计数算法 
 
char* Sskip2		(char * text,char *pat, int n, int m);//跳跃算法 
char* Skmpskip2	(char * text,char *pat, int n, int m);// kmp跳跃算法 
char* bfstr2		(char * text,char *pat, int n, int m);// gcc 
/* 下面为多模式串精确匹配算法，函数名以M开头*/
void Mac		(char *T,char *Ps[],int s);//AC算法
void Mwm		(char *T,char *Ps[],int s);//WM算法
void acsm		(char *T,char *Ps[],int s);//WM算法
void snortwm		(char *T,char *Ps[],int s);//WM算法
void Msbom		(char *T,char *Ps[],int s);//SBOM算法 
void Mshiftor		(char *T,char *Ps[],int s);//shift-0r算法 



#endif
