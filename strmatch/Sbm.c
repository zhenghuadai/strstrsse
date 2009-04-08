#include <string.h>
#include <stdio.h>
#include <stdio.h>
#define XSIZE 100
#define ASIZE 256
#define MAX(a,b) (a>b)?a:b
extern void output(int num);
void preBmBc(char *pat, int m, int bmBc[]) {
   int i;
 
   for (i = 0; i < ASIZE; ++i)
      bmBc[i] = m;
   for (i = 0; i < m - 1; ++i)
      bmBc[pat[i]] = m - i - 1;
}
 
 
void suffipates(char *pat, int m, int *suff) {
   int f, g, i;
 
   suff[m - 1] = m;
   g = m - 1;
   for (i = m - 2; i >= 0; --i) {
      if (i > g && suff[i + m - 1 - f] < i - g)
         suff[i] = suff[i + m - 1 - f];
      else {
         if (i < g)
            g = i;
         f = i;
         while (g >= 0 && pat[g] == pat[g + m - 1 - f])
            --g;
         suff[i] = f - g;
      }
   }
}
 
void preBmGs(char *pat, int m, int bmGs[]) {
   int i, j, suff[XSIZE];
 
   suffipates(pat, m, suff);
 
   for (i = 0; i < m; ++i)
      bmGs[i] = m;
   j = 0;
   for (i = m - 1; i >= -1; --i)
      if (i == -1 || suff[i] == i + 1)
         for (; j < m - 1 - i; ++j)
            if (bmGs[j] == m)
               bmGs[j] = m - 1 - i;
   for (i = 0; i <= m - 2; ++i)
      bmGs[m - 1 - suff[i]] = m - 1 - i;
}
 
 
void Sbm(char *textt, char *patt) {
   int i, j, bmGs[XSIZE], bmBc[ASIZE];
   int m,n;
   unsigned char *text,*pat;
   text=textt;
   pat=patt;
   m=strlen(pat);
   n=strlen(text);
//   printf("n lenth of bm:%d,m:%d,",n,m);
   
   /* Preprocessing */
   preBmGs(pat, m, bmGs);
   preBmBc(pat, m, bmBc);
   /* Searching */
   j = 0;
   while (j <= n - m) {
      for (i = m - 1; (i >= 0) && (pat[i] == text[i + j]); --i);
      if (i < 0) {
         output(j);
         j += bmGs[0];
      }
      else
         j += MAX(bmGs[i], bmBc[text[i + j]] - m + 1 + i);
   }
}
  
