#ifndef STRINGMATCH_HEADER__
#define STRINGMATCH_HEADER__
#define MAXPAT 256 //the maximal length of Pattern

#define CHARACTERS 256 //the length of   set of character  
#define ASIZE 256
#define WORD_SIZE 16
#define MAXINT2 2147483648 
#define MAXPATS 100
#include "stdio.h"
#include "stdlib.h"

void Sbf		(char * text,char *pat);//brute force �㷨 
void bfstr		(char * text,char *pat);
void Smp		(char * text,char *pat);//MP�㷨 
void Skmp		(char * text,char *pat); //KMP�㷨

void Sbm		(char * text,char *pat) ;//bm�㷨 
void Sbmh		(char * text,char *pat);// Horspool�㷨 
void Sbmhs		(char * text,char *pat);//SUNDAY�㷨���ֳ� quich search 
void Ssmith		(char * text,char *pat);//smith �㷨 

void Sdfa		(char * text,char *pat);//�������Զ����㷨 
void Sbdm		(char * text,char *pat);//Forward Dawg Matching algorithm 
void Sbndm		(char * text,char *pat);//Forward Dawg Matching algorithm 
void Sbom		(char * text,char *pat);//BOM�㷨 
void Sshiftor	(char * text,char *pat);//shift-or �㷨 
void Sshiftand	(char * text,char *pat);//shift-and �㷨 

void Skr		(char * text,char *pat);//KR�㷨 

void Sbyh		(char * text,char *pat);//�����㷨 
 
void Sskip		(char * text,char *pat);//��Ծ�㷨 
void Skmpskip	(char * text,char *pat);// kmp��Ծ�㷨 
void bfstr		(char * text,char *pat);// gcc 

/*  ����Ϊ��ģʽ����ȷƥ���㷨 ����������S��ͷ����һ������ΪĿ�괮���ڶ�������Ϊģʽ��*/
void Sbf2		(char * text,char *pat, int n, int m);//brute force �㷨 
void bfstr2		(char * text,char *pat, int n, int m);
void Smp		(char * text,char *pat, int n, int m);//MP�㷨 
void Skmp		(char * text,char *pat, int n, int m); //KMP�㷨

void Sbm		(char * text,char *pat, int n, int m) ;//bm�㷨 
void Sbmh		(char * text,char *pat, int n, int m);// Horspool�㷨 
void Sbmhs		(char * text,char *pat, int n, int m);//SUNDAY�㷨���ֳ� quich search 
void Ssmith		(char * text,char *pat, int n, int m);//smith �㷨 

void Sdfa		(char * text,char *pat, int n, int m);//�������Զ����㷨 
void Sbdm		(char * text,char *pat, int n, int m);//Forward Dawg Matching algorithm 
void Sbndm		(char * text,char *pat, int n, int m);//Forward Dawg Matching algorithm 
void Sbom		(char * text,char *pat, int n, int m);//BOM�㷨 
void Sshiftor	(char * text,char *pat, int n, int m);//shift-or �㷨 
void Sshiftand	(char * text,char *pat, int n, int m);//shift-and �㷨 

void Skr		(char * text,char *pat, int n, int m);//KR�㷨 

void Sbyh		(char * text,char *pat, int n, int m);//�����㷨 
 
void Sskip		(char * text,char *pat, int n, int m);//��Ծ�㷨 
void Skmpskip	(char * text,char *pat, int n, int m);// kmp��Ծ�㷨 
void bfstr		(char * text,char *pat, int n, int m);// gcc 
/* ����Ϊ��ģʽ����ȷƥ���㷨����������M��ͷ*/
void Mac		(char *T,char *Ps[],int s);//AC�㷨
void Mwm		(char *T,char *Ps[],int s);//WM�㷨
void acsm		(char *T,char *Ps[],int s);//WM�㷨
void snortwm		(char *T,char *Ps[],int s);//WM�㷨
void Msbom		(char *T,char *Ps[],int s);//SBOM�㷨 
void Mshiftor		(char *T,char *Ps[],int s);//shift-0r�㷨 



#endif
