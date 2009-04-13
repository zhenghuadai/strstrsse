#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include"global.h"
/* //�ĺ���Ϊǰ��MP�㷨�к�����Ϊ���Ը��Ƶ���
void preMp(char *x, int m, int mpNext[]) {
   int i, j;

   i = 0;
   j = mpNext[0] = -1;
   while (i < m) {
      while (j > -1 && x[i] != x[j])
         j = mpNext[j];
      mpNext[++i] = ++j;
   }
}
//�ú���Ϊǰ��KMP�㷨���Ӻ�����Ϊ���Ը��Ƶ���
void preKmp(char *x, int m, int kmpNext[]) {
   int i, j;

   i = 0;
   j = kmpNext[0] = -1;
   while (i < m) {
      while (j > -1 && x[i] != x[j])
         j = kmpNext[j];
      i++;
      j++;
      if (x[i] == x[j])
         kmpNext[i] = kmpNext[j];
      else
         kmpNext[i] = j;
   }
}
*/
//KMP Skip Search algorithm
int attempt(char *y, char *x, int m, int start, int wall) {
   int k;

   k = wall - start;
   while (k < m && x[k] == y[k + start])
      ++k;
   return(k);
}


void Skmpskip(char *textt,char *patt) {
   int i, j, k, kmpStart, per, start, wall,m,n;
   unsigned char * text,*pat;
   text=textt;
   pat=patt;
   m=strlen(pat);
   n=strlen(text);
   int kmpNext[m], list[m], mpNext[m],
       z[ASIZE];

   /* Preprocessing */
   preMp(pat, m, mpNext);
   preKmp(pat, m, kmpNext);
   memset(z, -1, ASIZE*sizeof(int));
   memset(list, -1, m*sizeof(int));
   z[pat[0]] = 0;
   for (i = 1; i < m; ++i) {
      list[i] = z[pat[i]];
      z[pat[i]] = i;
   }

   /* Searching */
   wall = 0;
   per = m - kmpNext[m];
   i = j = -1;
   do {
      j += m;
   } while (j < n && z[text[j]] < 0);
   if (j >= n)
     return;
   i = z[text[j]];
   start = j - i;
   while (start <= n - m) {
      if (start > wall)
         wall = start;
      k = attempt(text, pat, m, start, wall);
      wall = start + k;
      if (k == m) {
         output(start);
         i -= per;
      }
      else
         i = list[i];
      if (i < 0) {
         do {
            j += m;
         } while (j < n && z[text[j]] < 0);
         if (j >= n)
            return;
         i = z[text[j]];
      }
      kmpStart = start + k - kmpNext[k];
      k = kmpNext[k];
      start = j - i;
      while (start < kmpStart ||
             (kmpStart < start && start < wall)) {
         if (start < kmpStart) {
            i = list[i];
            if (i < 0) {
               do {
                  j += m;
               } while (j < n && z[text[j]] < 0);
               if (j >= n)
                  return;
               i = z[text[j]];
            }
            start = j - i;
         }
         else {
            kmpStart += (k - mpNext[k]);
            k = mpNext[k];
         }
      }
   }
}