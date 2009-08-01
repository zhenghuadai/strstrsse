#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#define ASIZE 256

//extern void *calloc(int num_elems,int elem_size);

/* data structure of Graph */
struct _graph{
   int vertexNumber,
       edgeNumber,
       vertexCounter,
       initial,
       *terminal,
       *target,
       *suffixLink,
       *length,
       *position,
       *shift;};

typedef struct _graph *Graph;
typedef int boolean;

/* return a new data structure for a graph with v vertices and e edges */
Graph newGraph(int v,int e)
{
    Graph g;
    g=(Graph)calloc(1,sizeof(struct _graph));
    if (g==NULL)
       error("newgraph");
    g->vertexNumber=v;
    g->edgeNumber=e;
    g->initial=0;
    g->vertexCounter=1;
    return(g);
}

/* return a new data structure for an automaton with v vertices and e edges */ 
Graph newAutomaton(int v,int e)
{
    Graph aut;
    aut=newGraph(v,e);
    aut->target=(int *)calloc(e,sizeof(int));
    if (aut->target==NULL)
       error("newAutomaton");
    aut->terminal=(int *)calloc(v,sizeof(int));
    if (aut->terminal==NULL)
       error("newAutomaton");
    return(aut);
}

/* return a new  vertex of graph g */
int newVertex(Graph g)
{
    if (g!=NULL && g->vertexCounter<=g->vertexNumber)
       return(g->vertexCounter++);
    error("newvertex");
}

/* return the initial vertex of graph g */
int getInitial(Graph g)
{
    if (g!=NULL)
       return(g->initial);
    error("getinitial");
}

/* return true if vertex v is terminal in graph g */
boolean isTerminal(Graph g,int v)
{
    if (g!=NULL && g->terminal!=NULL && v<g->vertexNumber)
       return(g->terminal[v]);
    error("isterminal");
}

/* set vertex v to be terminal in graph g */
void setTerminal(Graph g,int v)
{
    if (g!=NULL && g->terminal!=NULL && v<g->vertexNumber)
       g->terminal[v]=1;
    else 
       error("setterminal");
}

/* return the target of edge from vertex v labelled by character c in graph g */
int getTarget(Graph g,int v,unsigned char c)
{
    if (g!=NULL && g->target!=NULL && v<g->vertexNumber && v*c<g->edgeNumber)
       return(g->target[v*(g->edgeNumber/g->vertexNumber)+c]);
    error("getTarget");
}

/* add the edge from vertex v to vertex t labelled by character c in graph g */
void setTarget(Graph g,int v,unsigned char c,int t)
{
     if (g!=NULL && g->target!=NULL && v<g->vertexNumber && v*c<g->edgeNumber && t<g->vertexNumber)
        g->target[v*(g->edgeNumber/g->vertexNumber)+c]=t;
     else 
        error("setTarget");
}

/* copy all the characteristics of vertex source to vertex target in graph g */
void copyVertex(Graph g,int target,int source)
{
   if (g!=NULL && target<g->vertexNumber && source<g->vertexNumber)
   {
      if (g->target!=NULL)
         memcpy(g->target+target*(g->edgeNumber/g->vertexNumber),g->target+source*(g->edgeNumber/g->vertexNumber),(g->edgeNumber/g->vertexNumber)*sizeof(int));
      if (g->shift!=NULL)
         memcpy(g->shift+target*(g->edgeNumber/g->vertexNumber),g->shift+source*(g->edgeNumber/g->vertexNumber),(g->edgeNumber/g->vertexNumber)*sizeof(int));
      if (g->terminal!=NULL)
         g->terminal[target]=g->terminal[source];
      if (g->suffixLink!=NULL)
         g->suffixLink[target]=g->suffixLink[source];
      if (g->length!=NULL)
         g->length[target]=g->length[source];
      if (g->position!=NULL)
         g->position[target]=g->position[source];
    }
    else 
      error("copyvertex");
}

void  preAut(char *pat,int m,Graph aut)
{
    int i,state,target,oldTarget;
    for (state=getInitial(aut),i=0;i<m;++i)
    {
       oldTarget=getTarget(aut,state,pat[i]);
//printf("%d\n",oldTarget);
       target=newVertex(aut);
       setTarget(aut,state,pat[i],target);
       copyVertex(aut,target,oldTarget);
       state=target;
    }
    setTerminal(aut,state);
}

void  Sdfa2(char *text,char *pat,int n, int m) //基本的自动机算法 
{
	int j,state;
	Graph aut;


	/* preprocessing */
	aut=newAutomaton(m+1,(m+1)*ASIZE);
	preAut(pat,m,aut);

	/* searching */
	for(state=getInitial(aut),j=0;j<n;++j)
	{
		state=getTarget(aut,state,text[j]);
		if (isTerminal(aut,state))
			OUTPUT(j-m+1);
	}
}
void  Sdfa(char *text,char *pat) //基本的自动机算法 
{
	int m,n;
	m=strlen(pat);
	n=strlen(text);
	Sdfa2(text, pat, n ,m);
}

