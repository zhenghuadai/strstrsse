#ifndef GLOBAL_match
#define GLOBAL_match
#include "match.h"
typedef struct 
{
    unsigned long long u64;
    struct{
        unsigned int low;
        unsigned int high;
    };
} _U64;
char * Pat;//the patten string
#ifndef MAXPATS
#define MAXPATS 16384
#endif
char * Patts[MAXPATS];
int ps;
char * Text;// the subjiect string
char * occurrence[MAXPATS];//the matching address
int occurrenceint[MAXPATS];//the relative matching address
int occurnum;//the whole matching number
#ifdef __cplusplus 
extern "C"{
#endif
char * Getsubjectfromfile(char *pfname);
int  Getpatternfromfile(char *pfname,char **patts);
char * GetGenesubjectfromfile(char *pfname);
int  GetGenepatternfromfile(char *pfname,char **patts);
void Mtime(_U64 * readr);
double Mdifftime(_U64 start,_U64 end);
#ifdef __cplusplus 
}
#endif
int output(int);
int  outputs(int whichp,int addr);
#define OUTPUT(x) if( output(x) == STOP ) return ;
#endif
