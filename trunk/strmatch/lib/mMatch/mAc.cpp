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
#include <stdio.h>
#include <stdlib.h>
#include <queue>

#include "mAc.h"
namespace dmMatch{

mAc::mAc(char** pat, int n) : mMatch(pat, n)
{
	this->init();
}

void mAc::init()
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

int mAc::search(char* txt)
{
    unsigned char* p = (Uchar*) txt;	
    acNodeP state=pRoot;
    for(;*p; p++){
        state = state->go[*p];
        if(state-> isMatched()) {
            int ret = report(state->patID, p-(unsigned char*)txt);
        }
    }
    return 0;
}

}
