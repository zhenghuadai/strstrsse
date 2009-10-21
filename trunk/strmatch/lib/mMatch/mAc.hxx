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
template<int CHAR_SET, StoreType ST>
mAcBase<CHAR_SET, ST>::mAcBase(char** pat, int n) : mMatch(pat, n)
{
	this->compile();
}

template<int CHAR_SET, StoreType ST>
mAcBase<CHAR_SET, ST>::mAcBase(char** pat, int n, mAlgtype t) : mMatch(pat, n)
{
    type = t;
    acNodesPool.setMaxStateNum(charNum());
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
    reLocate();
    printf("build complete\n");
	//printf("#states num: %d\n", mStateNum);
}

    template<int CHAR_SET, StoreType ST>
void mAcBase<CHAR_SET, ST>::compile()
{
    buildNFA();
    convertDFA();
}

    template<int CHAR_SET, StoreType ST>
void mAcBase<CHAR_SET, ST>::buildNFA()
{
    buildTrie();
    buildFailure();
}

    template<int CHAR_SET, StoreType ST>
void mAcBase<CHAR_SET, ST>::buildTrie()
{
    pRoot()= makeNode();	
    for(int i=0;i<mPatNum; i++){
        acNodeP curNode = pRoot();
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

    template<int CHAR_SET, StoreType ST>
void mAcBase<CHAR_SET, ST>::buildGeneTrie()
{
    pRoot()= makeNode();	
    for(int i=0;i<mPatNum; i++){
        acNodeP curNode = pRoot();
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


    template<int CHAR_SET, StoreType ST>
void mAcBase<CHAR_SET, ST>::buildFailure()
{
    queue<acNodeP> Queue;
    //! the first level
    for(int i=0;i< CHAR_SET; i++){
        if(pRoot()->go[i] == NULL){
            pRoot()-> go[i] = pRoot();
        }else{
            pRoot()->go[i]->failure= pRoot();
            Queue.push(pRoot()->go[i]);
        }
    }
    pRoot()->failure = pRoot();
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

    template<int CHAR_SET, StoreType ST>
void mAcBase<CHAR_SET, ST>::convertDFA()
{
    if(pRoot() == NULL) return;
    queue<acNodeP> Queue;
    for(int i=0;i< CHAR_SET; i++){
        if(pRoot()->go[i] != pRoot()){
            Queue.push(pRoot()->go[i]);
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


template<typename NodeT , typename acNodeT, typename matchListT, NodeT (*nextState)( acNodeT*, NodeT, Uchar), int (*isMatched)(matchListT**, NodeT), int (*reportMatch)(matchListT**, NodeT , reportFunc , int ) >
int ACsearchGene(acNodeT* acBase, matchListT** matchListBase, NodeT pRoot, reportFunc report, char* txt)
{
    NodeT state=pRoot;
    for(unsigned char* p = (Uchar*) txt;*p; p++){
		Uchar c = agct2num(*p);
		if(c >=4){state= pRoot; continue;}
		state = nextState(acBase, state, c); // state= state->go[*p]; 
		if(isMatched((matchListT**)matchListBase, state)) {
			int ret = reportMatch( (matchListT**)matchListBase, state, report, (char*)p -txt);
		}
	}
	return 0;
}

    template<int CHAR_SET, StoreType ST>
int mAcBase<CHAR_SET, ST>::searchGene(char* txt)
{
#if 0
	unsigned char* p = (Uchar*) txt;	
	acNodeP state=pRoot();
	for(;*p; p++){
		Uchar c = agct2num(*p);
		if(c >=4){state= pRoot(); continue;}
		state = nextState(state, c); // state= state->go[*p]; 
		if(isMatched(state)) {
			int ret = reportList(matchedList(state), (char*)p - txt);
		}
	}
	return 0;
#else
return 	ACsearchGene<acNodeP, acNode<CHAR_SET>, int, mAcBase<CHAR_SET,ST>::nextStateT, mAcBase<CHAR_SET,ST>::isMatchedT, mAcBase<CHAR_SET,ST>::reportMatchT>(NULL, NULL, pRoot(), report, txt);
#endif
}

	template<int CHAR_SET, StoreType ST>
int mAcBase<CHAR_SET, ST>::searchGene(char* txt, int n)
{
	unsigned char* p = (Uchar*) txt;	
	acNodeP state=pRoot();
	for(int i=0; i<n; p++,i++){
		Uchar c = agct2num(*p);
		if(c >=4){state= pRoot(); continue;}
		state = nextState(state, c);// state= state->go[*p]; 
		if(state-> isMatched()) {
			int ret = state->report(report, (char*)p - txt);
		}
	}
	return 0;
}


	template<int CHAR_SET, StoreType ST>
int mAcBase<CHAR_SET, ST>::searchGene4(char* txt)
{
	unsigned char* p = (Uchar*) txt;	
	acNodeP state=pRoot();
	for(;*p; p++){
		Uchar c = (*p);
		if(c >=4){state= pRoot(); continue;}
		state = nextState(state, c); // state= state->go[*p]; 
		if(state-> isMatched()) {
			int ret = state->report(report, (char*)p - txt);
		}
	}
	return 0;
}

	template<int CHAR_SET, StoreType ST>
int mAcBase<CHAR_SET, ST>::searchGene4(char* txt, int n)
{
	unsigned char* p = (Uchar*) txt;	
	acNodeP state=pRoot();
	for(int i=0; i<n; p++,i++){
		Uchar c = (*p);
		if(c >=4){state= pRoot(); continue;}
		state = nextState(state, c);// state= state->go[*p]; 
		if(state-> isMatched()) {
			int ret = state->report(report, (char*)p - txt);
		}
	}
	return 0;
}


	template<int CHAR_SET, StoreType ST>
int mAcBase<CHAR_SET, ST>::search(char* txt)
{
	printf("search...\n");
	unsigned char* p = (Uchar*) txt;	
	acNodeP state=pRoot();
	for(;*p; p++){
		state = nextState(state, *p); // state= state->go[*p]; 
		if(state-> isMatched()) {
			int ret = state->report(report, (char*)p - txt);
		}
	}
	return 0;
}

	template<int CHAR_SET, StoreType ST>
int mAcBase<CHAR_SET, ST>::search(char* txt, int n)
{
	unsigned char* p = (Uchar*) txt;	
	acNodeP state=pRoot();
	for(int i=0; i<n; p++,i++){
		state = nextState(state, *p);// state= state->go[*p]; 
		if(state-> isMatched()) {
			int ret = state->report(report, (char*)p - txt);
		}
	}
	return 0;
}

template<typename T>
T top( queue<T>& q){return q.front();} 

template<typename T>
T top( stack<T>& q){return q.top();} 

	template<int CHAR_SET, typename idxT,  class travalT>
void transNode2Short(mAcBase<CHAR_SET>& ac, acNodeShort<CHAR_SET,idxT>* nodes, int** patIDList, int* patMatchList)
{
	int curState=0;
	int mStateNum = ac.mStateNum();
	typename mAcBase<CHAR_SET>::acNodeP* Map2= new typename mAcBase<CHAR_SET>::acNodeP [mStateNum];
	//queue<typename mAcBase<CHAR_SET>::acNodeP> Queue;
	travalT Queue;
#if 0
	map<unsigned long long, U16> Map;
#define MapIndex(a) Map[(unsigned long long)a]
#else
	idxT* Map = new idxT[mStateNum];
#define MapIndex(a) Map[a - ac.pRoot()]
#endif
	MapIndex(ac.pRoot())= curState;
	Map2[curState]=ac.pRoot();
	for(int i=0; i< CHAR_SET; i++){
		if( ac.pRoot()-> go[i] != ac.pRoot()) 
			Queue.push(ac.pRoot()->go[i]);
	}
	curState++;

	while(!Queue.empty()){
		//typename mAcBase<CHAR_SET>::acNodeP curNode= Queue.top();
		typename mAcBase<CHAR_SET>::acNodeP curNode= top(Queue);
		MapIndex(curNode)= curState;
		Map2[curState]=curNode;
		curState ++;
		Queue.pop();
		for(int i=0; i< CHAR_SET; i++){
			if(( curNode -> go[i] != curNode->failure->go[i]) )
				Queue.push(curNode->go[i]);
		}
	}
	printf(" mStateNum :%d %d\n", mStateNum, curState);
	memcpy(patMatchList, ac.patMatchList(), ac.patMatchListLen()*sizeof(int));
	for(int s=0;s<mStateNum;s++){
		for(int i=0;i< CHAR_SET; i++) {
			nodes[s].go[i] = MapIndex(Map2[s]->go[i] ); 
		}
		if(Map2[s]-> isMatched()){
			patIDList[s] = patMatchList + (Map2[s]->patIDArray - ac.patMatchList());
        }
	}

	delete Map2;
}

	template<int CHAR_SET, typename idxT>
void mAcD<CHAR_SET,idxT>::transWidthFrom(mAcBase<CHAR_SET>& ac)
{
	mStateNum = ac.mStateNum();
	mallocMem(mStateNum);
	patMatchList = (int*) malloc( ac. patMatchListLen()* sizeof(int));
	transNode2Short<CHAR_SET, idxT, queue<typename mAcBase<CHAR_SET>::acNodeP> >(ac, nodes, patIDList, patMatchList);
	pRoot() = 0;
}

	template<int CHAR_SET, typename idxT>
void mAcD<CHAR_SET,idxT>::transDepthFrom(mAcBase<CHAR_SET>& ac)
{
	mStateNum = ac.mStateNum();
	mallocMem(mStateNum);
	patMatchList = (int*) malloc( ac. patMatchListLen()* sizeof(int));
	transNode2Short<CHAR_SET,idxT, stack<typename mAcBase<CHAR_SET>::acNodeP> >(ac, nodes, patIDList, patMatchList);
	pRoot() = 0;
}


	template<int CHAR_SET, typename idxT>
int mAcD<CHAR_SET,idxT>::search(char* txt, int n)
{

}

	template<int CHAR_SET, typename idxT>
int mAcD<CHAR_SET,idxT>::search(char* txt)
{

}

	template<int CHAR_SET, typename idxT>
int mAcD<CHAR_SET,idxT>::searchGene(char* txt, int n)
{
}

	template<int CHAR_SET, typename idxT>
int mAcD<CHAR_SET,idxT>::searchGene(char* txt)
{
#if 0
	unsigned char* p = (Uchar*) txt;	
	acNodeP state=pRoot();
	for(;*p; p++){
		Uchar c = agct2num(*p);
		if(c >=4){state= pRoot(); continue;}
		state = nextState(state, c); // state= state->go[*p]; 
		if( isMatched(state)) {
			int ret = reportList(matchedList(state), (char*)p - txt);
		}
	}
	return 0;
#else
	return 	ACsearchGene<acNodeP, acNodeShort<CHAR_SET,idxT>, int, mAcD<CHAR_SET,idxT>::nextStateT, mAcD<CHAR_SET,idxT>::isMatchedT, mAcD<CHAR_SET,idxT>::reportMatchT>(nodes, patIDList,pRoot(), report, txt);
#endif

}

	template<int CHAR_SET, typename idxT>
int mAcD<CHAR_SET,idxT>::searchGene4(char* txt, int n)
{

}

	template<int CHAR_SET, typename idxT>
int mAcD<CHAR_SET,idxT>::searchGene4(char* txt)
{

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