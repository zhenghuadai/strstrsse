#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#define ASIZE 256
#define UNDEFINED -1


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

int newVertex(Graph g);
Graph newAutomaton(int v,int e);
int getInitial(Graph g);
int getTarget(Graph g,int v,unsigned char c);
void setTarget(Graph g,int v,unsigned char c,int t);
void copyVertex(Graph g,int target,int source);
void setTerminal(Graph g,int v);

/* returns a new data structure for a suffix automaton with v vertices and e edges */
Graph newSuffixAutomaton(int v, int e) 
{
   Graph aut;

   aut=newAutomaton(v,e);
   memset(aut->target, UNDEFINED, e*sizeof(int));
   aut->suffixLink = (int *)calloc(v, sizeof(int));
   if (aut->suffixLink == NULL)
      error("newSuffixAutomaton");
   aut->length = (int *)calloc(v, sizeof(int));
   if (aut->length == NULL)
      error("newSuffixAutomaton");
   aut->position = (int *)calloc(v, sizeof(int));
   if (aut->position == NULL)
      error("newSuffixAutomaton");
   aut->shift = (int *)calloc(e, sizeof(int));
   if (aut->shift == NULL)
      error("newSuffixAutomaton");
   return(aut);
}

/* returns the suffix link of vertex v in graph g */
int getSuffixLink(Graph g, int v) 
{
   if (g != NULL && g->suffixLink != NULL &&
       v < g->vertexNumber)
      return(g->suffixLink[v]);
   error("getSuffixLink");
   return -1; //Make the compiler happy
}


/* set the suffix link of vertex v to vertex s in graph g */
void setSuffixLink(Graph g, int v, int s) 
{
   if (g != NULL && g->suffixLink != NULL &&
       v < g->vertexNumber && s < g->vertexNumber)
      g->suffixLink[v] = s;
   else
      error("setSuffixLink");
}


/* returns the length of vertex v in graph g */
int getLength(Graph g, int v) 
{
   if (g != NULL && g->length != NULL &&
       v < g->vertexNumber)
      return(g->length[v]);
   error("getLength");
   return -1; //Make the compiler happy
}


/* set the length of vertex v to integer ell in graph g */
void setLength(Graph g, int v, int ell) 
{
   if (g != NULL && g->length != NULL &&
       v < g->vertexNumber)
      g->length[v] = ell;
   else
      error("setLength");
}

/* returns the position of vertex v in graph g */
int getPosition(Graph g, int v) {
   if (g != NULL && g->position != NULL &&
       v < g->vertexNumber)
      return(g->position[v]);
   error("getPosition");
   return -1; //Make the compiler happy
}


/* set the length of vertex v to integer ell in graph g */
void setPosition(Graph g, int v, int p) {
   if (g != NULL && g->position != NULL &&
       v < g->vertexNumber)
      g->position[v] = p;
   else
      error("setPosition");
}


/* returns the shift of the edge from vertex v
   labelled by character c in graph g */
int getShift(Graph g, int v, unsigned char c) {
   if (g != NULL && g->shift != NULL &&
       v < g->vertexNumber && v*c < g->edgeNumber)
      return(g->shift[v*(g->edgeNumber/g->vertexNumber) +
             c]);
   error("getShift");
   return -1; //Make the compiler happy
}


/* set the shift of the edge from vertex v
   labelled by character c to integer s in graph g */
void setShift(Graph g, int v, unsigned char c, int s) {
   if (g != NULL && g->shift != NULL &&
       v < g->vertexNumber && v*c <= g->edgeNumber)
      g->shift[v*(g->edgeNumber/g->vertexNumber) + c] = s;
   else
      error("setShift");
}


void buildSuffixAutomaton(char *pat, int m, Graph aut) {
   int i, art, init, last, p, q, r;
   char c;
  
   init = getInitial(aut);
   art = newVertex(aut);
   setSuffixLink(aut, init, art);
   last = init;
   for (i = 0; i < m; ++i) {
      c = pat[i];
      p = last;
      q = newVertex(aut);
      setLength(aut, q, getLength(aut, p) + 1);
      setPosition(aut, q, getPosition(aut, p) + 1);
      while (p != init &&
             getTarget(aut, p, c) == UNDEFINED) {
         setTarget(aut, p, c, q);
         setShift(aut, p, c, getPosition(aut, q) -
                             getPosition(aut, p) - 1);
         p = getSuffixLink(aut, p);
      }
      if (getTarget(aut, p, c) == UNDEFINED) {
         setTarget(aut, init, c, q);
         setShift(aut, init, c,
                  getPosition(aut, q) -
                  getPosition(aut, init) - 1);
         setSuffixLink(aut, q, init);
      }
      else
         if (getLength(aut, p) + 1 ==
             getLength(aut, getTarget(aut, p, c)))
            setSuffixLink(aut, q, getTarget(aut, p, c));
         else {
            r = newVertex(aut);
            copyVertex(aut, r, getTarget(aut, p, c));
            setLength(aut, r, getLength(aut, p) + 1);
            setSuffixLink(aut, getTarget(aut, p, c), r);
            setSuffixLink(aut, q, r);
            while (p != art &&
                   getLength(aut, getTarget(aut, p, c)) >=
                   getLength(aut, r)) {
               setShift(aut, p, c,
                        getPosition(aut,
                                    getTarget(aut, p, c)) -
                        getPosition(aut, p) - 1);
               setTarget(aut, p, c, r);
               p = getSuffixLink(aut, p);
            }
         }
      last = q;
   }
   setTerminal(aut, last);
   while (last != init) {
      last = getSuffixLink(aut, last);
      setTerminal(aut, last);
   }
}


char* Sbdm2(char * text,char *pat, int n, int m) //Forward Dawg Matching algorithm 
{
   int j,init,ell,state;
   Graph aut;


   /* preprocessing */
   aut=newSuffixAutomaton(2*(m+2),2*(m+2)*ASIZE);
   buildSuffixAutomaton(pat,m,aut);
   init=getInitial(aut);

   /* searching */
   ell=0;
   state=init;
   for (j=0;j<n;++j)
   {
       if (getTarget(aut,state,text[j])!=UNDEFINED)
       {
          ++ell;
          state=getTarget(aut,state,text[j]);
       }
       else
       {
          while (state!=init && getTarget(aut,state,text[j])==UNDEFINED)
                state=getSuffixLink(aut,state);
          if (getTarget(aut,state,text[j])!=UNDEFINED)
          {
             ell=getLength(aut,state)+1;
             state=getTarget(aut,state,text[j]);
          }
          else 
          {
             ell=0;
             state=init;
          }
        }
        if (ell==m)
           OUTPUT(j-m+1);
   }
   SRET(j-m+1);
}

char* Sbdm(char * text,char *pat) //Forward Dawg Matching algorithm 
{
	int m,n;
	m=strlen(pat);
	n=strlen(text);
	return Sbdm2(text, pat, n, m);
}
