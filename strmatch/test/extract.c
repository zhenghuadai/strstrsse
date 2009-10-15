#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

char * Getsubjectfromfile(char *pfname)
{
    int psubstep=0,buffcounts;
    //      unsigned int temp;
    char * psub;
    char temp2;
    FILE *pf;	
    struct stat filestat;
    if((pf=fopen(pfname,"r"))==NULL)
    {
        printf("cannot open input string");	
        exit(0);
    }
    buffcounts=stat(pfname,&filestat);
    buffcounts=filestat.st_size;

    /*	//获取文件长度 elementcounts*/
    if (( psub=(char *) malloc(sizeof(char) *(buffcounts+1)))==NULL)
    {
        printf("failure mallocaa      ");

    }

    //  printf("succuss malloc");
    while((temp2=fgetc(pf))!=EOF)
    {
        //		temp=(unsigned int )temp2;
        //                     if(((temp>=97)&&(temp<=122))||((temp>=65)&&(temp<=90)))
        if((temp2=='\0'))continue;
        {psub[psubstep]=temp2;
            psubstep++;
        }
    }
    psub[psubstep]='\0';
    return psub;

}

int   Getpatternfromfile(char *pfname,char **patts)
{
    int psubstep=0,buffcounts;
    //      unsigned int temp;
    char buff[256];
    char * psub;
    char temp2;
    int patno=0,i;
    FILE *pf;	
    if((pf=fopen(pfname,"r"))==NULL)
    {
        printf("cannot open input string");	
        exit(0);
    }

    while((temp2=fgetc(pf))!=EOF)
    {
        if(temp2=='\n')
        {
            buff[psubstep]='\0';
            psub=(char *)malloc(psubstep*sizeof(char));
            for(i=0;i<=psubstep;i++)
            {
                psub[i]=buff[i];
            }
            patts[patno++]=psub;
            psubstep=0;
            continue;
        }
        else
        {
            buff[psubstep]=temp2;
            psubstep++;
        }
    }
    return patno;

}


char* GetGenesubjectfromfile(char *pfname)
{
    int psubstep=0,buffcounts;
    unsigned int temp;
    char * psub;
    char temp2;
    FILE *pf;	
    struct stat filestat;
    if((pf=fopen(pfname,"r"))==NULL)
    {
        printf("cannot open input string");	
        exit(0);
    }
    buffcounts=stat(pfname,&filestat);
    buffcounts=filestat.st_size;

    /*	//获取文件长度 elementcounts*/
    if (( psub=(char *) malloc(sizeof(char) *(buffcounts+1)))==NULL)
    {
        printf("failure mallocaa      ");
        exit(0);

    }

    //  printf("succuss malloc");
    while((temp2=fgetc(pf))!=EOF)
    {
        if((temp2=='A')||(temp2=='G')||(temp2=='C')||(temp2=='T')||(temp2=='a')||(temp2=='g')||(temp2=='c')||(temp2=='t'))
        {
            psub[psubstep]=temp2;
            psubstep++;
        }
    }
    psub[psubstep]=0;
    return psub;

}

int   GetGenepatternfromfile(char *pfname,char **patts)
{
    int psubstep=0,buffcounts;
    //      unsigned int temp;
    char buff[256];
    char * psub;
    char temp2;
    int patno=0,i;
    FILE *pf;	
    if((pf=fopen(pfname,"r"))==NULL)
    {
        printf("cannot open input string");	
        exit(0);
    }

    while((temp2=fgetc(pf))!=EOF)
    {
        if(temp2=='\n')
        {
            buff[psubstep]='\0';
            psub=(char *)malloc(psubstep*sizeof(char));
            for(i=0;i<=psubstep;i++)
            {
                psub[i]=buff[i];
            }
            patts[patno++]=psub;
            psubstep=0;
            continue;
        }
        else
        {
            if((temp2=='A')||(temp2=='G')||(temp2=='C')||(temp2=='T')||(temp2=='a')||(temp2=='g')||(temp2=='c')||(temp2=='t'))
                buff[psubstep++]=temp2;
        }
    }
    return patno;

}


