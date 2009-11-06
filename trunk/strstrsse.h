
#ifndef  STRSTRSSE_INC
#define  STRSTRSSE_INC

typedef int (*reportFunc)(int);
char *lstrstr (const char* , const char* );
char *lstrstrsse (const char* , const char* );

#define SEARCH_STOP 1
#define SEARCH_CONTINUE 0


#endif   /* ----- #ifndef STRSTRSSE_INC  ----- */
