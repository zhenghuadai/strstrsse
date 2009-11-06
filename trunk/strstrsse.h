
#ifndef  STRSTRSSE_INC
#define  STRSTRSSE_INC

typedef int (*reportFunc)(int);
char *lstrstr (const char* , const char* );
char *lstrstrsse (const char* , const char* );
void setReportFunc(reportFunc rf);

#define SEARCH_STOP 1
#define SEARCH_CONTINUE 0
#define SEARCH_THE_FIRST ((reportFunc) 1)
#define SEARCH_ALL ((reportFunc) 2)


#endif   /* ----- #ifndef STRSTRSSE_INC  ----- */
