#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

char * Getsubjectfromfile(char *pfname)
{ /* Getsubjectfromfile total:   2988  1.6591  1804  2.3857     1  0.6944 */
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
                      if((temp2=='\t')||(temp2=='\n'))continue;
			{psub[psubstep]=temp2;
		  psubstep++;
			}
	}
psub[psubstep]=0;
return psub;
}
