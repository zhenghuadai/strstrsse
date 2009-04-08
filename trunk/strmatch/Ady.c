#include <string.h>
#include <stdio.h>
#include <stdio.h>
#define MAXNUM 100 

int MIN(int a,int b,int c)
{
	int temp1,temp2;

	temp1=a;
	if(b<c)
		temp2=b;
	else 
		temp2=c;
	if(temp2<temp1)
		temp1=temp2;
	return(temp1);
}
	

void preEd(char *x,char *y,long m,long n,int dsw[][MAXNUM])
{
	long i,j;

	for(i=0;i<m+1;i++)
		dsw[i][0]=i;
	for(j=0;j<n+1;j++)
		dsw[0][j]=0;
	
	for(i=1;i<=m;i++)
		for(j=1;j<=n;j++)
			if(x[i-1]==y[j-1])
				dsw[i][j]=dsw[i-1][j-1];
			else
				dsw[i][j]=MIN(dsw[i-1][j-1],dsw[i-1][j],dsw[i][j-1])+1;
}

void Ady(char *Text,char *Pattern,int kerr)
{
	int dsw[MAXNUM][MAXNUM];
	long m,n;
	long j;

	m=strlen(Pattern);
	n=strlen(Text);
	
	preEd(Pattern,Text,m,n,dsw);

	for(j=1;j<=n;j++)
		if(dsw[m][j]<=kerr)
		{
			printf("one success at the position %d!\n",j-1);
			printf("the edit distance is %d\n",dsw[m][j]);
		}
}

