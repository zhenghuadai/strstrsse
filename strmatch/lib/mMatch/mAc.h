/*
 * =====================================================================================
 *
 *       Filename:  mAc.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/13/2009 11:00:06 AM
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

#include "mMatch.h"

namespace dmMatch{

class acNode
{
	public:
		int patID;
		acNode* go[256];
		acNode* failue;
	public:
		acNode(){memset(this, 0, sizeof(acNode));}
};
typedef acNode* acNodeP;

class AcNodeStore
{
	public:
		acNodeP p_NodeList;//! root is the first element
		int nodeNum;
		int type;
};

class mAc:public mMatch
{
	private:
		acNodeP pRoot;
		AcNodeStore acNodeStore;
		List<acNode> nodeList;
	public:
		mAc();
		void init();
	private:	
		acNodeP makeNode() { acNodeP newNode= new acNode(); nodeList.push(newNode); return newNode;};
};



};
