#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdio.h>
void preAfr(unsigned char *sgoto)
{
	char  sw[4][4];
	int i,j,k,temp;
	sw[0][0]=0;
	for(i=0;i<27;i++)
	   for(j=0;j<27;j++)
		   for(k=0;k<8;k++)
		   {
			   index=i*(27*8)+j*8+k;
		           sw[0][1]=i%3-1;temp=i/3;sw[0][2]=temp%3-1;temp=temp/3;sw[0][3]=temp%3;			   
		   }
		
		
	
}
void AfourR(char * Text,char * Pat,int kerrs)
{
	unsigned char *sgoto;
	unsigned char SC[strlen(Text)][strlen(Pat)];
	int i,j,m,n,state;
	sgoto=(char *)malloc(27*27*8*2*sizeof(unsigned char));
	m=strlen(Text);
	n=strlen(Pat);
	preAfr(sgoto);
	init(SC);
	for(j=0;j<n/3;j++)
		for(i=0;i<m/3;i++)
		{/* get the input state*/
			
			state=sgoto(state);
			
			/* process out state */
		}
}
