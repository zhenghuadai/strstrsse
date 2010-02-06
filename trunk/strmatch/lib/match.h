#ifndef STRINGMATCH_HEADER__
#define STRINGMATCH_HEADER__
#define MAXPAT 256 //the maximal length of Pattern

#define CHARACTERS 256 //the length of   set of character  
#define ASIZE 256
#if __WORDSIZE == 32 
#define WORD_SIZE 32
typedef unsigned int Uword;
#else
#define WORD_SIZE 64
typedef unsigned long long Uword;
#endif

#define MAXINT2 2147483648 
#include "stdio.h"
#include "stdlib.h"
typedef void* (* preSearchFunc)(char* pat, int m);
typedef void* (* search1Func)(char* text, void* pat);
typedef void* (* search2Func)(char* text, char* pat, int n, int m);
typedef void* (* search3Func)(char* text, void* pat, int n, int m);
//! group pre-Search 
void* preSbf      (char* pat, int m);//brute force �㷨 
void* prebfstr    (char* pat, int m);
void* preSmp      (char* pat, int m);//MP�㷨 
void* preSkmp     (char* pat, int m); //KMP�㷨
                                   
void* preSbm      (char* pat, int m) ;//bm�㷨 
void* preSbmh     (char* pat, int m);// Horspool�㷨 
void* preSbmhs    (char* pat, int m);//SUNDAY�㷨���ֳ� quich search 
void* preSsmith   (char* pat, int m);//smith �㷨 
                                   
void* preSdfa     (char* pat, int m);//�������Զ����㷨 
void* preSbdm     (char* pat, int m);//Forward Dawg Matching algorithm 
void* preSbndm    (char* pat, int m);//Forward Dawg Matching algorithm 
void* preSbom     (char* pat, int m);//BOM�㷨 
void* preSshiftor (char* pat, int m);//shift-or �㷨 
void* preSshiftand(char* pat, int m);//shift-and �㷨 
void* preSshiftorW(char* pat, int m);//shift-or �㷨 
                                   
void* preSkr      (char* pat, int m);//KR�㷨 
void* preSbyh     (char* pat, int m);//�����㷨 
void* preSskip    (char* pat, int m);//��Ծ�㷨 
void* preSkmpskip (char* pat, int m);// kmp��Ծ�㷨 
void* prebfstr    (char* pat, int m);// gcc 


//! group 1
char* Sbf        (char* text, char* pat);//brute force �㷨 
char* bfstr      (char* text, char* pat);
char* Smp        (char* text, char* pat);//MP�㷨 
char* Skmp       (char* text, char* pat); //KMP�㷨
                                    
char* Sbm        (char* text, char* pat) ;//bm�㷨 
char* Sbmh       (char* text, char* pat);// Horspool�㷨 
char* Sbmhs      (char* text, char* pat);//SUNDAY�㷨���ֳ� quich search 
char* Ssmith     (char* text, char* pat);//smith �㷨 
                                    
char* Sdfa       (char* text, char* pat);//�������Զ����㷨 
char* Sbdm       (char* text, char* pat);//Forward Dawg Matching algorithm 
char* Sbndm      (char* text, char* pat);//Forward Dawg Matching algorithm 
char* Sbom       (char* text, char* pat);//BOM�㷨 
char* Sshiftor   (char* text, char* pat);//shift-or �㷨 
char* Sshiftand  (char* text, char* pat);//shift-and �㷨 
char* SshiftorW  (char* text, char* pat);//shift-or �㷨 
                                    
char* Skr        (char* text, char* pat);//KR�㷨 
char* Sbyh       (char* text, char* pat);//�����㷨 
char* Sskip      (char* text, char* pat);//��Ծ�㷨 
char* Skmpskip   (char* text, char* pat);// kmp��Ծ�㷨 
char* bfstr      (char* text, char* pat);// gcc 
char* lstrstr    (const char* text, const char* pat);// gcc 
char* strstrsse (const char* text, const char* pat);// gcc 
char* strstrsse42(const char* text, const char* pat);// gcc 

/*  ����Ϊ��ģʽ����ȷƥ���㷨 ����������S��ͷ����һ������ΪĿ�괮���ڶ�������Ϊģʽ��*/
char* Sbf2      (char* text, char* pat, int n, int m);//brute force �㷨 
char* bfstr2    (char* text, char* pat, int n, int m);
char* Smp2      (char* text, char* pat, int n, int m);//MP�㷨 
char* Skmp2     (char* text, char* pat, int n, int m); //KMP�㷨
                                   
char* Sbm2      (char* text, char* pat, int n, int m) ;//bm�㷨 
char* Sbmh2     (char* text, char* pat, int n, int m);// Horspool�㷨 
char* Sbmhs2    (char* text, char* pat, int n, int m);//SUNDAY�㷨���ֳ� quich search 
char* Ssmith2   (char* text, char* pat, int n, int m);//smith �㷨 
                                   
char* Sdfa2     (char* text, char* pat, int n, int m);//�������Զ����㷨 
char* Sbdm2     (char* text, char* pat, int n, int m);//Forward Dawg Matching algorithm 
char* Sbndm2    (char* text, char* pat, int n, int m);//Forward Dawg Matching algorithm 
char* Sbom2     (char* text, char* pat, int n, int m);//BOM�㷨 
char* Sshiftor2 (char* text, char* pat, int n, int m);//shift-or �㷨 
char* Sshiftand2(char* text, char* pat, int n, int m);//shift-and �㷨 
char* SshiftorW2(char* text, char* pat, int n, int m);//shift-or �㷨 
                                   
char* Skr2      (char* text, char* pat, int n, int m);//KR�㷨 
char* Sbyh2     (char* text, char* pat, int n, int m);//�����㷨 
char* Sskip2    (char* text, char* pat, int n, int m);//��Ծ�㷨 
char* Skmpskip2 (char* text, char* pat, int n, int m);// kmp��Ծ�㷨 
char* bfstr2    (char* text, char* pat, int n, int m);// gcc 

/*  ����Ϊ��ģʽ����ȷƥ���㷨 ����������S��ͷ����һ������ΪĿ�괮���ڶ�������Ϊģʽ��*/
char* Sbf3      (char* text, void* pat, int n, int m);//brute force �㷨 
char* bfstr3    (char* text, void* pat, int n, int m);
char* Smp3      (char* text, void* pat, int n, int m);//MP�㷨 
char* Skmp3     (char* text, void* pat, int n, int m); //KMP�㷨
                                   
char* Sbm3      (char* text, void* pat, int n, int m) ;//bm�㷨 
char* Sbmh3     (char* text, void* pat, int n, int m);// Horspool�㷨 
char* Sbmhs3    (char* text, void* pat, int n, int m);//SUNDAY�㷨���ֳ� quich search 
char* Ssmith3   (char* text, void* pat, int n, int m);//smith �㷨 
                                   
char* Sdfa3     (char* text, void* pat, int n, int m);//�������Զ����㷨 
char* Sbdm3     (char* text, void* pat, int n, int m);//Forward Dawg Matching algorithm 
char* Sbndm3    (char* text, void* pat, int n, int m);//Forward Dawg Matching algorithm 
char* Sbom3     (char* text, void* pat, int n, int m);//BOM�㷨 
char* Sshiftor3 (char* text, void* pat, int n, int m);//shift-or �㷨 
char* Sshiftand3(char* text, void* pat, int n, int m);//shift-and �㷨 
char* SshiftorW3(char* text, void* pat, int n, int m);//shift-or �㷨 
                                   
char* Skr3      (char* text, void* pat, int n, int m);//KR�㷨 
char* Sbyh3     (char* text, void* pat, int n, int m);//�����㷨 
char* Sskip3    (char* text, void* pat, int n, int m);//��Ծ�㷨 
char* Skmpskip3 (char* text, void* pat, int n, int m);// kmp��Ծ�㷨 
char* bfstr3    (char* text, void* pat, int n, int m);// gcc 

/* ����Ϊ��ģʽ����ȷƥ���㷨����������M��ͷ*/
void Mac        (char *T,char *Ps[],int s);//AC�㷨
void Mwm        (char *T,char *Ps[],int s);//WM�㷨
void acsm       (char *T,char *Ps[],int s);//WM�㷨
void snortwm    (char *T,char *Ps[],int s);//WM�㷨
void Msbom      (char *T,char *Ps[],int s);//SBOM�㷨 
void Mshiftor   (char *T,char *Ps[],int s);//shift-0r�㷨 



#endif
