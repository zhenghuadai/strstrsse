#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdio.h>
int strmat_ac_match(STRING **pattern_ary, int num_patterns, STRING *text,
                    int stats)
{
  int i, M, N, pos, matchcount, matchlen, matchid, total_length;
  char *s, *P, *T;
  MATCHES matchlist, matchtail, newmatch;
  AC_STRUCT *acstruct;

  if (pattern_ary == NULL || num_patterns == 0 || text == NULL ||
      text->sequence == NULL || text->length == 0)
    return 0;

  T = text->sequence;
  N = text->length;

  matchlist = matchtail = NULL;
  matchcount = 0;

  /*
   * Perform the Aho-Corasick preprocessing.
   */
  if ((acstruct = ac_alloc()) == NULL)
    return 0;

  total_length = 0;
  for (i=0; i < num_patterns; i++) {
    P = pattern_ary[i]->sequence;
    M = pattern_ary[i]->length;
    total_length += M;

    if (ac_add_string(acstruct, P, M, i+1) == 0) {
      ac_free(acstruct);
      return 0;
    }
  }
  ac_prep(acstruct);

  /*
   * Perform the matching.
   */
  ac_search_init(acstruct, T, N);
  while ((s = ac_search(acstruct, &matchlen, &matchid)) != NULL) {
    pos = s - T + 1;

    newmatch = alloc_match();
    if (newmatch == NULL) {
      free_matches(matchlist);
      ac_free(acstruct);
      mprintf("Memory Error:  Ran out of memory.\n");
      return 0;
    }
    newmatch->type = SET_EXACT;
    newmatch->lend = pos;
    newmatch->rend = pos + matchlen - 1;
    newmatch->id = matchid;

    if (matchlist == NULL)
      matchlist = matchtail = newmatch;
    else {
      matchtail->next = newmatch;
      matchtail = newmatch;
    }
    matchcount++;
  }

  /*
   * Print the statistics and the matches.
   */
  print_matches(text, NULL, 0, matchlist, matchcount);

  if (stats) {
    mprintf("Statistics:\n");
#ifdef STATS
    mprintf("   Preprocessing:\n");
    mprintf("      Sum of Pattern Sizes:       %d\n", total_length);
    mprintf("      Number of Created Edges:    %d\n",
            acstruct->prep_new_edges);
    mprintf("      Number of Traversed Edges:  %d\n",
            acstruct->prep_old_edges);
    mprintf("      Failure Link Comparisons:   %d\n",
            acstruct->prep_fail_compares);

    mprintf("\n   Searching:\n");
    mprintf("      Text Length:                %d\n", N);
    mprintf("      Number of Compares:         %d\n", acstruct->num_compares);
    mprintf("      Avg. Compares per Position: %.2f\n",
            (float) acstruct->num_compares / (float) N);
    mprintf("\n");
    mprintf("      Tree Edges Traversed:       %d\n",
            acstruct->edges_traversed);
    mprintf("      Fail Links Traversed:       %d\n", acstruct->num_failures);
    mprintf("      Output Link Traversed:      %d\n",
            acstruct->outlinks_traversed);
#else
    mputs("   No statistics available.\n");
#endif
    mputc('\n');
  }

  /*
   * Free everything allocated.
   */
  free_matches(matchlist);
  ac_free(acstruct);

  return 1;
}

