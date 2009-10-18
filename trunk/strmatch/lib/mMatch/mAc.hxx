/*
 * =====================================================================================
 *
 *       Filename:  mAc.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/13/2009 12:23:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhenghua Dai (Zhenghua Dai), djx.zhenghua@gamil.com
 *        Company:  dzh
 *
 * =====================================================================================
 */
#ifndef __mAC_TEMPLATE_HEADER
#define __mAC_TEMPLATE_HEADER
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <map>

//#include "mAc.h"
namespace dmMatch{
template<int CHAR_SET>
mAcBase<CHAR_SET>::mAcBase(char** pat, int n) : mMatch(pat, n)
{
    stateNum=0;
	this->compile();
}

template<int CHAR_SET>
mAcBase<CHAR_SET>::mAcBase(char** pat, int n, mAlgtype t) : mMatch(pat, n)
{
    type = t;
    stateNum=0;
    if(type==geneAC){
        printf("build Trie...\n");
        buildGeneTrie();
        printf("build Trie complete\n");
        printf("build Failure...\n");
        buildFailure();
        printf("build Failure complete\n");
        printf("build DFA...\n");
        convertDFA();
        printf("build DFA complete\n");
    }else {
        compile();
    }
    printf("build complete\n");
	printf("#states num: %d\n", stateNum);
}

    template<int CHAR_SET>
void mAcBase<CHAR_SET>::compile()
{
    buildNFA();
    convertDFA();
}

    template<int CHAR_SET>
void mAcBase<CHAR_SET>::buildNFA()
{
    buildTrie();
    buildFailure();
}

    template<int CHAR_SET>
void mAcBase<CHAR_SET>::buildTrie()
{
    pRoot= makeNode();	
    for(int i=0;i<mPatNum; i++){
        acNodeP curNode = pRoot;
        char* p = mPatterns[i];
        while( *p && (curNode->go[*p]!=NULL)){ curNode=curNode->go[*p]; p++; }
        for(; *p; p++){
            Uchar c=*p;
            curNode-> go[c] = makeNode();
            curNode = curNode->go[c];
        }
        curNode->addPattern(i);
    }

}

    template<int CHAR_SET>
void mAcBase<CHAR_SET>::buildGeneTrie()
{
    pRoot= makeNode();	
    for(int i=0;i<mPatNum; i++){
        acNodeP curNode = pRoot;
        unsigned char* p =(unsigned char*) mPatterns[i];
        int n = strlen((const char *)p);
        while( *p && (curNode->go[agct2num(*p)]!=NULL)){ curNode=curNode->go[agct2num(*p)]; p++; }
        for(; *p; p++){
            Uchar c=agct2num(*p);
            curNode-> go[c] = makeNode();
            curNode = curNode->go[c];
        }
        curNode->addPattern(i);
    }

}


    template<int CHAR_SET>
void mAcBase<CHAR_SET>::buildFailure()
{
    queue<acNodeP> Queue;
    //! the first level
    for(int i=0;i< CHAR_SET; i++){
        if(pRoot->go[i] == NULL){
            pRoot-> go[i] = pRoot;
        }else{
            pRoot->go[i]->failure= pRoot;
            Queue.push(pRoot->go[i]);
        }
    }
    pRoot->failure = pRoot;
    while(!Queue.empty())
    {
        acNodeP parent= Queue.front();
        Queue.pop();
        for(int i=0;i<CHAR_SET; i++){
            acNodeP curNode = parent-> go[i];
            if( curNode==NULL) continue;
            Queue.push(curNode);
            acNodeP dst = parent->failure;
            while(dst -> go[i] == NULL) dst = dst->failure;
            curNode->failure = dst->go[i];
            if(dst->go[i]->isMatched())
                curNode->addPattern(dst->go[i]);
        }

    }
}

    template<int CHAR_SET>
void mAcBase<CHAR_SET>::convertDFA()
{
    if(pRoot == NULL) return;
    queue<acNodeP> Queue;
    for(int i=0;i< CHAR_SET; i++){
        if(pRoot->go[i] != pRoot){
            Queue.push(pRoot->go[i]);
        }
    }
    while(!Queue.empty()){
        acNodeP curNode= Queue.front();
        Queue.pop();
        for(int i=0;i<CHAR_SET;i++){
            if(curNode->go[i] != NULL){
                Queue.push(curNode->go[i]);
            }else{
                curNode->go[i] = curNode->failure->go[i];
            }
        }
    }
}


template<typename NodeT , NodeT (*nextState)(NodeT, Uchar), int (*isMatched)(NodeT) >
int ACsearchGene(NodeT pRoot, char* txt)
{
    unsigned char* p = (Uchar*) txt;	
    NodeT state=pRoot;
    for(;*p; p++){
		Uchar c = agct2num(*p);
		if(c >=4){state= pRoot; continue;}
		state = nextState(state, c); // state= state->go[*p]; 
		if(isMatched(state)) {
			//int ret = state->report(report, (char*)p - txt);
		}
	}
	return 0;
}

    template<int CHAR_SET>
int mAcBase<CHAR_SET>::searchGene(char* txt)
{
    unsigned char* p = (Uchar*) txt;	
    acNodeP state=pRoot;
    for(;*p; p++){
		Uchar c = agct2num(*p);
		if(c >=4){state= pRoot; continue;}
		state = nextState(state, c); // state= state->go[*p]; 
		if(state-> isMatched()) {
			int ret = state->report(report, (char*)p - txt);
		}
	}
	return 0;
}

	template<int CHAR_SET>
int mAcBase<CHAR_SET>::searchGene(char* txt, int n)
{
	unsigned char* p = (Uchar*) txt;	
	acNodeP state=pRoot;
	for(int i=0; i<n; p++,i++){
		Uchar c = agct2num(*p);
		if(c >=4){state= pRoot; continue;}
		state = nextState(state, c);// state= state->go[*p]; 
		if(state-> isMatched()) {
			int ret = state->report(report, (char*)p - txt);
		}
	}
	return 0;
}


    template<int CHAR_SET>
int mAcBase<CHAR_SET>::searchGene4(char* txt)
{
    unsigned char* p = (Uchar*) txt;	
    acNodeP state=pRoot;
    for(;*p; p++){
		Uchar c = (*p);
		if(c >=4){state= pRoot; continue;}
		state = nextState(state, c); // state= state->go[*p]; 
		if(state-> isMatched()) {
			int ret = state->report(report, (char*)p - txt);
		}
	}
	return 0;
}

	template<int CHAR_SET>
int mAcBase<CHAR_SET>::searchGene4(char* txt, int n)
{
	unsigned char* p = (Uchar*) txt;	
	acNodeP state=pRoot;
	for(int i=0; i<n; p++,i++){
		Uchar c = (*p);
		if(c >=4){state= pRoot; continue;}
		state = nextState(state, c);// state= state->go[*p]; 
		if(state-> isMatched()) {
			int ret = state->report(report, (char*)p - txt);
		}
	}
	return 0;
}


	template<int CHAR_SET>
int mAcBase<CHAR_SET>::search(char* txt)
{
	printf("search...\n");
	unsigned char* p = (Uchar*) txt;	
	acNodeP state=pRoot;
	for(;*p; p++){
		state = nextState(state, *p); // state= state->go[*p]; 
		if(state-> isMatched()) {
			int ret = state->report(report, (char*)p - txt);
		}
	}
	return 0;
}

	template<int CHAR_SET>
int mAcBase<CHAR_SET>::search(char* txt, int n)
{
	unsigned char* p = (Uchar*) txt;	
	acNodeP state=pRoot;
	for(int i=0; i<n; p++,i++){
		state = nextState(state, *p);// state= state->go[*p]; 
		if(state-> isMatched()) {
			int ret = state->report(report, (char*)p - txt);
		}
	}
	return 0;
}


	template<int CHAR_SET>
void mAcBase<CHAR_SET>::clean()
{
	typename list<acNodeP>::iterator i;
	for(i = nodeList.begin(); i!= nodeList.end(); i++){
		delete *i;
	}
	nodeList.clear();
	pRoot = 0;
}



    	template<int CHAR_SET>
void mAcD<CHAR_SET>::transDepthFrom(mAcBase<CHAR_SET>& ac)
{
    int curState=0;
    stateNum = ac.stateNum;
    mallocMem(stateNum);
    typename mAcBase<CHAR_SET>::acNodeP* Map2= new typename mAcBase<CHAR_SET>::acNodeP [stateNum];
    stack<typename mAcBase<CHAR_SET>::acNodeP> Stack;
    Stack.push(ac.pRoot);
    map<typename mAcBase<CHAR_SET>::acNodeP, U16> Map;
    while(!Stack.empty()){
        typename mAcBase<CHAR_SET>::acNodeP curNode= Stack.front();
        Map[curNode]= curState;
        Map2[curState]=curNode;
        curState ++;
        Stack.pop();
        for(int i= CHAR_SET-1; i>=0; i--){
           if( curNode -> go[i] != curNode->failure->go[i])
            Stack.push(curNode->go[i]);
        }
    }
    for(int s=0;s<stateNum;s++){
        for(int i=0;i< CHAR_SET; i++) {
            pRoot[s].go[i] = Map[ Map2[s]->go[i] ]; 
        }
    }
    delete Map2;
}

    template<int CHAR_SET>
void mAcD<CHAR_SET>::transWidthFrom(mAcBase<CHAR_SET>& ac)
{
    int curState=0;
    stateNum = ac.stateNum;
    mallocMem(stateNum);
    typename mAcBase<CHAR_SET>::acNodeP* Map2= new typename mAcBase<CHAR_SET>::acNodeP [stateNum];
    queue<typename mAcBase<CHAR_SET>::acNodeP> Queue;
    Queue.push(ac.pRoot);
    map<typename mAcBase<CHAR_SET>::acNodeP, U16> Map;
    while(!Queue.empty()){
        typename mAcBase<CHAR_SET>::acNodeP curNode= Queue.front();
        Map[curNode]= curState;
        Map2[curState]=curNode;
        curState ++;
        Queue.pop();
        for(int i=0; i< CHAR_SET-1; i++){
           if( curNode -> go[i] != curNode->failure->go[i])
            Queue.push(curNode->go[i]);
        }
    }
    for(int s=0;s<stateNum;s++){
        for(int i=0;i< CHAR_SET; i++) {
            pRoot[s].go[i] = Map[ Map2[s]->go[i] ]; 
        }
    }
    delete Map2;
}


//
//void test_XXXXXXXXXXXXXXX()
//{
//    mAcBase<256>* ac1 = new mAcBase<256>((char**)0, 0);
//    mAcBase<128>* ac2 = new mAcBase<128>((char**)0,0);
//    delete ac1;
//    delete ac2;
//}

}
#endif
