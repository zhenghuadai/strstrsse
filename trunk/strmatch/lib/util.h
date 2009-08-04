#ifndef UTILL_match
#define UTILL_match
typedef struct 
{
    unsigned long long u64;
    struct{
        unsigned int low;
        unsigned int high;
    };
} _U64;
char * Getsubjectfromfile(char *pfname);
int  Getpatternfromfile(char *pfname,char **patts);
void Mtime(_U64 * readr);
double Mdifftime(_U64 start,_U64 end);
//int output(int);
int output(char* text, int i, char* pat);
int  outputs(int whichp,int addr);
#define STOP 1
#define CONTINUE 0
#define OUTPUT(x) if( output(text, x, pat) == STOP ) return ;
#define OUTPUT3(text, x , pat) if( output(text, x, pat) == STOP ) return ;
#endif
