#include <string.h>
#include <string.h>
#include "automaton.h"
#include <stdio.h>
#include <stdlib.h>
#include "match.h"
extern void output(int num);
/* struct _cell{
    int element; 
    struct _cell *next;
  };
typedef struct _cell *List;*/
void Sskip(char *textt,char *patt)//ÌøÔ¾Ëã·¨ 
{
   int i, j,m,n;
   unsigned char * text,*pat;
   text=textt;
   pat=patt;
   m=strlen(pat);
   n=strlen(text);
   List ptr, z[ASIZE];
   /* Preprocessing */
   memset(z, 0, ASIZE*sizeof(List));
   for (i = 0; i < m; ++i) {
      ptr = (List)malloc(sizeof(struct _cell));
      if (ptr == NULL)
         error("SKIP");
      ptr->element = i;
      ptr->next = z[pat[i]];
      z[pat[i]] = ptr;
   }
   /* Searching */
   for (j = m - 1; j < n; j += m)
   {
      for (ptr = z[text[j]]; ptr != NULL; ptr = ptr->next)
        {
        if (memcmp(pat, text + j - ptr->element, m) == 0)
         {
            if (j-ptr->element <= n - m)
               output(j - ptr->element);
         }
         else
            continue;
	}
   }
}
