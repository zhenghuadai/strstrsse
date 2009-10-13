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
#include <list>
#include "mMatch.h"
#define CHAR_SET 256
using namespace std;
namespace dmMatch{

class acNode
{
	public:
		int patID;
		acNode* go[256];
		acNode* failure;
	public:
		acNode(){memset(this, 0, sizeof(acNode));}
		int isMatched(){ return patID != -1;}
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
		list<acNodeP> nodeList;
	public:
		mAc();
		mAc(char** pat, int n);
		virtual int search(char* txt, int n){};
		virtual int search(char* txt);
	protected:
		virtual void init();
	private:	
		acNodeP makeNode() { acNodeP newNode= new acNode(); nodeList.push_back(newNode); return newNode;};
};

};
