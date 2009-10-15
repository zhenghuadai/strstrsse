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

//#include "mAc.h"
namespace dmMatch{
template<int CHAR_SET>
mAcBase<CHAR_SET>::mAcBase(char** pat, int n) : mMatch(pat, n)
{
    stateNum=0;
	this->compile();
}

template<int CHAR_SET>
void mAcBase<CHAR_SET>::compile()
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
		curNode->patID=i;
	}

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
        }

    }

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

template<int CHAR_SET>
int mAcBase<CHAR_SET>::search(char* txt)
{
    unsigned char* p = (Uchar*) txt;	
    acNodeP state=pRoot;
    for(;*p; p++){
        state = nextState(state, *p); // state= state->go[*p]; 
        if(state-> isMatched()) {
            int ret = report(state->patID, p-(unsigned char*)txt);
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
            int ret = report(state->patID, p-(unsigned char*)txt);
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
