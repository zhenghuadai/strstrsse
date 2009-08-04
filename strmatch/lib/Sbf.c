#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdio.h>

void Sbf2(char *text,char *pat,int n, int m)
{
  int i,j;

//  n=strlen(text);

  /* searching */
  for(j=0;text[j+m]!=0;/*j<=n-m;*/++j)
  {
	  for (i=0;i<m&&pat[i]==text[i+j];++i);
	  if (i>=m){
		 OUTPUT(j);
	  }
  }  

}
void Sbf(char *text,char *pat)
{
	int n,m;
	m=strlen(pat);
	Sbf2(text,pat,n,m);
}
/* Return the offset of one string within another.
   Copyright (C) 1994, 1996, 1997, 2000, 2001 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

/*
 * My personal strstr() implementation that beats most other algorithms.
 * Until someone tells me otherwise, I assume that this is the
 * fastest implementation of strstr() in C.
 * I deliberately chose not to comment it.  You should have at least
 * as much fun trying to understand it, as I had to write it :-).
 *
 * Stephen R. van den Berg, berg@pool.informatik.rwth-aachen.de	*/

#if HAVE_CONFIG_H
# include <config.h>
#endif

#if defined _LIBC || defined HAVE_STRING_H
# include <string.h>
#endif

typedef unsigned chartype;

#undef strstr
	void
bfstr(text, pattern)
	const char *text;
	const char *pattern;
{
	const unsigned char *pj,*pstart, *needle;
	chartype b;
	const unsigned char *rneedle;

	pj = (const unsigned char *) text;
	pstart=pj;
again:
	if ((b = *(needle = (const unsigned char *) pattern)))
	{
		chartype c;
		pj--;		/* possible ANSI violation */

		{
			chartype a;
			do
				if (!(a = *++pj))
					goto ret0;
			while (a != b);
		}

		if (!(c = *++needle))
			goto foundneedle;
		++needle;
		goto jin;

		for (;;)
		{
			{
				chartype a;
				if (0)
					jin:{
						if ((a = *++pj) == c)
							goto crest;
					}
				else
					a = *++pj;
				do
				{
					for (; a != b; a = *++pj)
					{
						if (!a)
							goto ret0;
						if ((a = *++pj) == b)
							break;
						if (!a)
							goto ret0;
					}
				}
				while ((a = *++pj) != c);
			}
crest:
			{
				chartype a;
				{
					const unsigned char *rpj;
					if (*(rpj = pj-- + 1) == (a = *(rneedle = needle)))
						do
						{
							if (!a)
								goto foundneedle;
							if (*++rpj != (a = *++needle))
								break;
							if (!a)
								goto foundneedle;
						}
						while (*++rpj == (a = *++needle));
					needle = rneedle;	/* took the register-poor aproach */
				}
				if (!a)
					break;
			}
		}//endfor
	}
foundneedle:
	{
		int pos;
		pos=pj-pstart;
		OUTPUT3(text, pos, pattern);
	}
	pj++;
	goto again;
ret0:
	return ;
}
	void
bfstr2(text, pattern, n, m)
	const char *text;
	const char *pattern;
	int n;
	int m;
{
	bfstr(text, pattern);
}
