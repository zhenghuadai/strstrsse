#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdio.h>
//¼ÆÊýËã·¨
#include"match.h"
void SbyhSearch(unsigned char *text,int m,int n,int  ch[]); 
void Sbyh2(char *textt,char *patt,int n ,int m)
{
int i,j;
unsigned char *text,*pat;
text=textt;
pat=patt;
int ch[ASIZE];
for(i=0;i<ASIZE;i++)
ch[i]=-1;
for(i=0;i<m;i++)
{
    ch[pat[i]]=i;
}
/*search*/
 SbyhSearch(text,m,n,ch);
}
void Sbyh(char *textt,char *patt)
{
int m, n;
m=strlen(patt);
n=strlen(textt);
Sbyh2(textt, patt, n, m);
}
void SbyhSearch(unsigned char *text,int m,int n,int ch[]){
	int j,pos;
	int  count[2*m],yu;

	  for(j=0;j<2*m;j++) {
	  	count[j]=0;
	  }
	yu=2*m; 
        for(j=0;j<m;j++)
       if((ch[text[j]]!=-1)&&(j-ch[text[j]]>0) )
          count[j-ch[text[j]]]++;
	for(j=m;j<n;j++){
		if(ch[text[j]]!=-1)	
			   count[(j-ch[text[j]])%yu]++;
		
	if(count[(j-m)%yu]==(m))
	    {
	    	  //OUTPUT(j-m);
			  OUTPUT3(text, j-m, ch);
	    }
	    	  count[(j-m)%yu]=0;
	}	
}




