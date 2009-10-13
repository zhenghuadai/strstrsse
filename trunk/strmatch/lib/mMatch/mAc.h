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
//#define CHAR_SET 256
using namespace std;
namespace dmMatch{

template<int CHAR_SET>
class acNode
{
	public:
		int patID;
		acNode* go[CHAR_SET];
		acNode* failure;
	public:
		acNode(){memset(this, 0, sizeof(acNode)); patID=-1;}
		int isMatched(){ return patID != -1;}
};

template<int CHAR_SET>
class acNodeShort
{
	public:
		I16 patID;
		U16 failure;
		U16 go[CHAR_SET];
	public:
		acNodeShort(){memset(this, 0, sizeof(acNodeShort)); patID=-1;}
		int isMatched(){ return patID != -1;}
};


template<int CHAR_SET>
class AcNodeStore
{
    public:
        typedef acNode<CHAR_SET>* acNodeP;
	public:
		acNodeP p_NodeList;//! root is the first element
		int nodeNum;
		int type;
};

template<int CHAR_SET=256>
class mAc:public mMatch
{
    public:
        typedef acNode<CHAR_SET>* acNodeP;
    private:
        acNodeP pRoot;
        AcNodeStore<CHAR_SET> acNodeStore;
        list<acNodeP> nodeList;
    public:
        mAc();
        mAc(char** pat, int n);
        virtual int search(char* txt, int n){};
        virtual int search(char* txt);
    protected:
        virtual void init();
    private:	
        acNodeP makeNode() { acNodeP newNode= new acNode<CHAR_SET>(); nodeList.push_back(newNode); return newNode;};
};

};
