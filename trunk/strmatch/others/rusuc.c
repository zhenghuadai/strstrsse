#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include<stdio.h>
#include<string.h>
#define MAXNUM 512 
#define MAXLENGTH 100 

int MIN(int a,int b,int c)
{
	int temp;
	if(a<b)
		temp=a;
	else
		temp=b;
	if(c<temp)
		temp=c;
	return(temp);
}

void preCom(char *p,char*q,int evench[4][4])
{
	int i,j;

	for(i=1;i<=3;i++)
		for(j=1;j<=3;j++)
		{
			if(*(p+i-1)!=*(q+j-1))
				evench[i][j]=1;
			else 
				evench[i][j]=0;
		}
}

void trantm(long k,int evench[4][4])
{
	long temp;
        
   	evench[3][3]=k%2;
        temp=k/2;
        evench[3][2]=temp%2;
        temp=temp/2;
        evench[3][1]=temp%2;
        temp=temp/2;
        evench[2][3]=temp%2;
        temp=temp/2;
        evench[2][2]=temp%2;
        temp=temp/2;
        evench[2][1]=temp%2;
        temp=temp/2;
        evench[1][3]=temp%2;
        temp=temp/2;
        evench[1][2]=temp%2;
        temp=temp/2;
        evench[1][1]=temp%2;
}

long trantl(int evench[4][4])
{
	long temp;
	temp=evench[3][3]+evench[3][2]*2+evench[3][1]*4+evench[2][3]*8+evench[2][2]*16+evench[2][1]*32+evench[1][3]*64+evench[1][2]*128+evench[1][1]*256;
	return(temp);
}

void preCD(long preTABLE[][MAXNUM])
{
    long i, j, k,temp;
    long index;
    int dw[4][4],cw[4][4],evench[4][4];
    int dci,dcj,chi,chj;

    dw[0][0]=cw[0][0]=0;
    
    for (i=0;i<27;i++)
	for (j=0;j<27;j++)
	    for (k=0;k<MAXNUM;k++) 
	    {
		index=i*27+j;
		
		cw[0][3]=i%3-1;
		temp=i/3;
		cw[0][2]=temp%3-1;
		temp=temp/3;
		cw[0][1]=temp%3-1;
		
		dw[3][0]=j%3-1;
		temp=j/3;
		dw[2][0]=temp%3-1;
		temp=temp/3;
		dw[1][0]=temp%3-1;

		trantm(k,evench);

		for(dci=1;dci<=3;dci++)
       		   for(dcj=1;dcj<=3;dcj++)
		   {
                      if(evench[dci][dcj]!=0)
              	         dw[dci][dcj]=MIN(1-cw[dci-1][dcj],1,dw[dci][dcj-1]-cw[dci-1][dcj]+1);
		      else
			 dw[dci][dcj]=-cw[dci-1][dcj];
		      cw[dci][dcj]=cw[dci-1][dcj]+dw[dci][dcj]-dw[dci][dcj-1];
		   }
		
		preTABLE[index][k]=(cw[3][1]+1)*243+(cw[3][2]+1)*81+(cw[3][3]+1)*27+(dw[1][3]+1)*9+(dw[2][3]+1)*3+dw[3][3]+1;
	    }
}

void A4Russians(char *Text,char *Pat,int kerr)
{
	long preTABLE[800][MAXNUM];
	char *p,*t;
	int evench[4][4];
	long chvalue,state,tempstate;
	int DW[MAXLENGTH/3+3][MAXLENGTH/3+3],CW[MAXLENGTH/3+3][MAXLENGTH/3+3];
	int SWD[MAXLENGTH][MAXLENGTH],SWC[MAXLENGTH][MAXLENGTH];
	int m,n,checknum;
	int i,j;
	long lastcl,lastrow,temp,remaincl,remainrow;

	m=strlen(Pat);
	n=strlen(Text);
	for(i=1;i<=m/3;i++)
		DW[i][1]=26;
	for(j=1;j<=n/3;j++)
		CW[1][j]=13;
	
	preCD(preTABLE);

	for(i=1;i<m/3+1;i++)
		for(j=1;j<n/3+1;j++)
		{
			p=Pat+3*(i-1);
			t=Text+3*(j-1);
			preCom(p,t,evench);

			chvalue=trantl(evench);
			state=CW[i][j]*27+DW[i][j];
			tempstate=preTABLE[state][chvalue];
		        
			CW[i+1][j]=tempstate/27;
			DW[i][j+1]=tempstate%27;
		}

	for(j=0;j<=n;j++)
		SWC[0][j]=0;
	SWD[0][0]=0;
	for(i=1;i<=m;i++)
		SWD[i][0]=1;
	
	if(n%3!=0)
	{
		lastcl=n/3;
		lastcl=lastcl*3;
	
        	for(i=1;i<m/3+1;i++)
        	{
	        	SWD[(i-1)*3+3][lastcl]=DW[i][lastcl/3+1]%3-1;
		        temp=DW[i][lastcl/3+1]/3;
	        	SWD[(i-1)*3+2][lastcl]=temp%3-1;
	        	temp=temp/3;
	        	SWD[(i-1)*3+1][lastcl]=temp%3-1;
	        }
	
		
		remaincl=n%3;

		for(i=1;i<=m;i++)
			for(j=lastcl+1;j<=lastcl+remaincl;j++)
			{
				if(Pat[i-1]==Text[j-1])
					SWD[i][j]=-SWC[i-1][j];
				else
					SWD[i][j]=MIN(1-SWC[i-1][j],1,SWD[i][j-1]-SWC[i-1][j]+1);
				SWC[i][j]=SWC[i-1][j]+SWD[i][j]-SWD[i][j-1];
			}
	}
	else
	{
		lastcl=n;
                for(i=1;i<m/3+1;i++)
                {
                       SWD[(i-1)*3+3][lastcl]=DW[i][n/3+1]%3-1;
                       temp=DW[i][n/3+1]/3;
                       SWD[(i-1)*3+2][lastcl]=temp%3-1;
                       temp=temp/3;
                       SWD[(i-1)*3+1][lastcl]=temp%3-1;
                }
	}

	if(m%3!=0)
	{
		lastrow=m/3;
		lastrow=lastrow*3;
	}
	else
		lastrow=m;
	
	for(j=1;j<lastcl/3+1;j++)
	{
		SWC[lastrow][(j-1)*3+3]=CW[m/3+1][j]%3-1;
		temp=CW[m/3+1][j]/3;
		SWC[lastrow][(j-1)*3+2]=temp%3-1;
		temp=temp/3;
		SWC[lastrow][(j-1)*3+1]=temp%3-1;
	}

	if(m%3!=0)
	{
		remainrow=m%3;
		for(i=lastrow+1;i<=lastrow+remainrow;i++)
			for(j=1;j<=n;j++)
			{
				if(Pat[i-1]==Text[j-1])
					SWD[i][j]=-SWC[i-1][j];
				else
					SWD[i][j]=MIN(1-SWC[i-1][j],1,SWD[i][j-1]-SWC[i-1][j]+1);
				SWC[i][j]=SWC[i-1][j]+SWD[i][j]-SWD[i][j-1];
			}
	}

	checknum=m;
	for(j=1;j<=n;j++)
	{
		checknum+=SWC[m][j];
		if(checknum<=kerr)
	           printf("at the %dth address of the Text,the Pattern has a %d kerr match with it!\n",j-1,checknum);
	}
}
