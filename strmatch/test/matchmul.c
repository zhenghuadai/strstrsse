#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include "match.h"
#include "global.h"
#include<stdio.h>
int main(int argc,char *argv[])
{
    /*  读入目标串和模式串 初始化 */ 
    int i ;
    static int stats_flag=0;
    char *subjfname,*quryfname;
    double elapsed_time;
    void (* matchalg[5])(char * text,char * pat[],int num);
    char * matchalgstr[5];
    int boolmatch[5];
    FILE *fp;

    _U64 startrdt,endrdt;

    for(i=0;i<5;i++)
        matchalg[i]=NULL;
    matchalg[0]=acsm;
    matchalgstr[0]="ACsm";
    matchalg[1]=snortwm;
    matchalgstr[1]="snortwm";
    matchalg[2]=Mac;
    matchalgstr[2]="ac";
    matchalg[3]=Mwm;
    matchalgstr[3]="WM";

    for(i=0;i<5;i++)
    {
        boolmatch[i]=1;
    }
    if((fp=fopen("boolmatchmul","r"))==NULL)
    {
        printf("err");
    }
    else
    {
        for(i=0;i<5;i++)
            fscanf(fp,"%d",&boolmatch[i]);

        fclose(fp);
    }	


    Patts[0]="Natasha";
    Patts[1]="ocean";
    Patts[2]="romantic";
    Patts[3]="shape";
    Patts[4]="still";
    ps=5;
    Text="Till today, the lantern ncichpc  festival is still held each year ncichpc around the country. Lanterns of various shapes and sizes ncichpc are hung in the streets, attracting countless visitors. Children will hold self-made or bought lanterns to stroll with on the streets, extremely excite";
    if(argc==1)
    {
        quryfname="input/patterns";
        subjfname="input/subject";
    }
    else
    {
        quryfname=argv[2];
        subjfname=argv[1];
    }

    ps=Getpatternfromfile(quryfname,Patts);
    Text=Getsubjectfromfile(subjfname);
    /*subjfname=Text;
      fp=fopen("temp","r");
      while(*subjfname!='\0')
      {fprintf(fp,"%c",*subjfname);
      subjfname++;
      }*/
    //printf("%s\n",Pat);
    occurnum=0;
    //printf("%s,",Text);
    printf("\n");
    /*for(i=0;i<ps;i++)
      {
      printf("%s,",Patts[i]);
      }
      printf("\n");*/
    //Mwm(Text,Patts,ps);
    //Mac(Text,Patts,ps);
    printf("\n%d ok\n",strlen(Text));
    /*
       if((fp=fopen("mulresult","r"))==NULL)
       {
       printf("open result file err");
       exit(0);
       }
       fprintf(fp,"***********************************************\n");
       fprintf(fp,"length of Text:%d\nnum of pattern:%d\n ",strlen(Text),ps);
       */
    /* 调用串匹配函数 */
    for(i=0;i<5;i++)
    {

        if(matchalg[i]&& boolmatch[i])
        {
            Mtime( &startrdt );
            matchalg[i](Text,Patts,ps);
            Mtime( &endrdt );
            elapsed_time= Mdifftime( startrdt, endrdt );
            printf("\nalgorithm %s takes\t %20.15f seconds.\n",matchalgstr[i], elapsed_time );
            //  fprintf(fp,"%20.15f seconds:algorithm %s takes \n ", elapsed_time, matchalgstr[i]);
        }
    }
    //fclose(fp);

    /* 输出结果 */ 
    for(i=0;i<occurnum;i++)
        printf("%d,",occurrenceint[i]);
    /*printf("\nzqd's algorithm takes %20.15f seconds.\n", elapsed_time );
      Mtime( &startrdt );

      strmat_ac_match(Patts, ps, Text, stats_flag);
      Mtime( &endrdt );
      elapsed_time= Mdifftime( startrdt, endrdt );
      printf("\n algorithm takes %20.15f seconds.\n", elapsed_time );
      */	 

}
