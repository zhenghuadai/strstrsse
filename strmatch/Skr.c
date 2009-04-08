#include <string.h>
#include <stdio.h>
#include <stdio.h>
#define REHASH(a, b, h) ((((h) - (a)*d) << 1) + (b)) 
//Karp-Rabin algorithm
void Skr(char *text, char *pat) {
   int d, hx, hy, i, j,m,n;
   m=strlen(pat);
   n=strlen(text);
   /* Preprocessing */
   /* computes d = 2^(m-1) with
      the left-shift operator */
   for (d = i = 1; i < m; ++i)
      d = (d<<1);

   for (hy = hx = i = 0; i < m; ++i) {
      hx = ((hx<<1) + pat[i]);
      hy = ((hy<<1) + text[i]);
   }

   /* Searching */
   j = 0;
   while (j <= n-m) {
      if (hx == hy && memcmp(pat, text + j, m) == 0)
         output(j);
      hy = REHASH(text[j], text[j + m], hy);
      ++j;
   }

}
