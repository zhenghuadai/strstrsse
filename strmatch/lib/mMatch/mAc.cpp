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

#include "mAc.h"

namespace dmMatch{

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
	acNodeP preRoot = new acNode();
	for(int i=0;i< CHAR_SET; i++){
		preRoot-> go[i] = pRoot;
	}
	pRoot->failure = preRoot;
	Queue.push(pRoot);
//
//	for(int i=0;i< CHAR_SET; i++){
//		if( pRoot -> go[i] == NULL) continue;
//		acNodeP curNode= pRoot-> go[i];
//		pRoot-> failure = pRoot;
//		Queue.push(curNode);
//	}
//
	while(!Queue.empty())
	{
		acNodeP parent= Queue.pop();
		for(int i=0;i<CHAR_SET; i++){
			acNodeP curNode = parent-> go[i];
			if( curNode==NULL) continue;
			Queue.push(curNode);
			acNodeP dst = parent->failure;
			while(dst -> go[i] == NULL) dst = dst->failure;
			curNode->failure = dst->go[i];
		}

	}

	delete preRoot;
	pRoot->failure = pRoot;
}


}
