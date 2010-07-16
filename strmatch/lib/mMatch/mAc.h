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
#ifndef __MAC_HEADER__
#define __MAC_HEADER__
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include "mMatch.h"
#include <new>
//#define CHAR_SET 256
namespace dmMatch{

typedef list<int> listID_t;

/*
 * =====================================================================================
 *        Class:  acNode
 *  Description:  
 * =====================================================================================
 */
template<int CHAR_SET>
class acNode
{
public:
	acNode* go[CHAR_SET];
	acNode* failure;
	union{
		list<int>* patIDList;
		int patID;
	};
	int* patIDArray;
	int mMatchNum;
public:
	acNode(){memset(this, 0, sizeof(acNode*)*CHAR_SET); }
	void adjust(SSize bytes){ 
        for(int i=0;i<CHAR_SET;i++){
            if(go[i]!=0) go[i] =(acNode*) ( ((char*)go[i]) + bytes); 
        }  
        if(failure!= NULL) failure = (acNode*)(((char*)failure)+bytes);
    }
	~acNode(){}
	//int isMatched(){ return patIDList != NULL;}
	int isMatched(){return patMatchNum()!= 0;}
	//! when compile
	void addPattern(int i){if(!patIDList){patIDList= new list<int>(); patIDList->push_back(i);}  mMatchNum++;}

	void addPattern(acNode* node){
		if(!patIDList) patIDList = new list<int>();
		for(typename list<int>::iterator i= node->patIDList->begin(); i!= node->patIDList->end(); i++) 
			patIDList->push_back(*i); 
		mMatchNum += node->mMatchNum;
	}
	//! when search
	void copyPatListTo(list<int>* dst){
		if(patIDList ==NULL) return;
		for(typename list<int>::iterator i= patIDList->begin(); i!= patIDList->end(); i++)  dst->push_back(*i);
	}
	int transPatList2Array(int* pstart){
		if(patMatchNum()==0) return 0;
		int k=1;
		pstart[0] = patMatchNum();
		for(typename list<int>::iterator i=patIDList->begin(); i!= patIDList->end(); i++,k++){ 
			pstart[k] = *i;
		}
		delete patIDList;
		patIDList = 0;
		patIDArray = pstart;
		return k;
	}
	int patMatchNum(){return mMatchNum;}

};
typedef enum {
	StoreList, StoreArray
}StoreType;

/*
 * =====================================================================================
 *        Class:  AcNodeStore
 *  Description:  
 *              this is abstract class, 
 *              there is two specialized class: StoreList and StoreArray
 * =====================================================================================
 */
template<int CHAR_SET, StoreType ST>
class AcNodeStore
{
public:
	typedef acNode<CHAR_SET>* acNodeP;
public:
	acNodeP nodeList;//! root is the first element
	acNodeP mRoot;
	int mStateNum;
	//int type;
public:
	//!interface
	int computeMatchListLen();
	void transPatList2Array();
	void reLocate();
	acNodeP makeNode();
};

/*
 * =====================================================================================
 *        Class:  AcNodeStore<.., StoreList>
 *  Description:  
 * =====================================================================================
 */
template<int CHAR_SET>
class AcNodeStore<CHAR_SET, StoreList>
{
public:
	typedef acNode<CHAR_SET>* acNodeP;
public:
	list<acNodeP> nodeList;//! root is the first element
	acNodeP mRoot;
	int mStateNum;
	int mMaxStateNum;
	int *patMatchList;
	int patMatchListLen;
	int mType;
public:
	AcNodeStore():mRoot(0), mStateNum(0), mMaxStateNum(0),patMatchList(0),patMatchListLen(0),mType(mAC){};
	~AcNodeStore(){ this -> clean(nodeList); delete patMatchList;}
	void setMaxStateNum(int n){mMaxStateNum = n;}
public:
	acNodeP& pRoot() {return mRoot;}
	int& type(){return mType;}
public:
	void clean(list<acNodeP>& tnodeList)
	{
#if 0
		typename list<acNodeP>::iterator i;
		for(i = nodeList.begin(); i!= nodeList.end(); i++){
			delete *i;
		}
		nodeList.clear();
		pRoot = 0;
#else
		while( ! tnodeList.empty()){
			acNodeP cur = tnodeList.front();
			delete cur;
			tnodeList.pop_front();
		}
		pRoot() = 0;
#endif
	}

	int computeMatchListLen(){
		int nlen=0;
		for(typename list<acNodeP>::iterator i = nodeList.begin(); i!= nodeList.end(); i++){
			if( *i -> isMatched())
				nlen += (( *i-> mMatchNum )+1);
		}
		return nlen;
	}

	void transPatList2Array(){
		int tlen = computeMatchListLen();
		patMatchList = new int [tlen];
		int *pcur=patMatchList;
		for(typename list<acNodeP>::iterator i = nodeList.begin(); i!= nodeList.end(); i++){
			int ret = *i-> transPatList2Array(pcur);
			pcur += ret;
		}
		patMatchListLen = pcur - patMatchList;
	}
	void reLocate(){}
	acNodeP makeNode() {mStateNum++; acNodeP newNode= new acNode<CHAR_SET>(); nodeList.push_back(newNode); return newNode;};

};

/*
 * =====================================================================================
 *        Class:  AcNodeStore<.., StoreArray>
 *  Description:  
 * =====================================================================================
 */
template<int CHAR_SET>
class AcNodeStore<CHAR_SET, StoreArray>:public memBase
{
public:
	typedef acNode<CHAR_SET>* acNodeP;
	typedef acNode<CHAR_SET>  acNodeT;
public:
	acNodeP nodeList;//! root is the first element
	acNodeP mRoot;
	int mStateNum;
	int mMaxStateNum;
	int *patMatchList;
	int patMatchListLen;
	int mType;
public:
	AcNodeStore():mRoot(0), mStateNum(0), mMaxStateNum(0),patMatchList(0),patMatchListLen(0),mType(mAC){};
	~AcNodeStore(){ this -> clean(nodeList);delete patMatchList;}
	void setMaxStateNum(int n){mMaxStateNum = n;}
	void trans2WidthFirst();
public:
	acNodeP& pRoot() {return mRoot;}
	int& type(){return mType;}

public:
	void clean(acNodeP tNodeList){
		for(int i=0;i< mStateNum; i++){
			tNodeList[i].~acNodeT();
		} 
		mFree(tNodeList);
	}
	acNodeP makeNode() {
		if(pRoot()==0) nodeList = (acNodeP)mMalloc(mMaxStateNum * sizeof(acNodeT)); 
		mStateNum++;  acNodeP newNode= new(&nodeList[mStateNum-1]) acNodeT;
		return newNode;
	}

	int computeMatchListLen(){
		int nlen=0;
		for(int i=0;i< mStateNum;i++){ 
			if( nodeList[i] . isMatched())
				nlen += (( nodeList[i]. mMatchNum )+1);
		}
		return nlen;
	}

	void transPatList2Array(){
		int tlen = computeMatchListLen();
		patMatchList = new int [tlen];
		int *pcur=patMatchList;
		for(int i=0;i< mStateNum;i++){ 
			int ret = nodeList[i].transPatList2Array(pcur);
			pcur += ret;
		}
		patMatchListLen = pcur - patMatchList;
	}
	void reLocate(){
		acNodeP tmpNodeList = (acNodeP)mMalloc(mStateNum* sizeof(acNodeT)); 
		memcpy(tmpNodeList, nodeList, mStateNum*sizeof(acNodeT)); 
		for(int i=0;i< mStateNum;i++){ tmpNodeList[i].adjust((SSize)tmpNodeList - (SSize)nodeList);}
		mFree(nodeList); 
		nodeList = tmpNodeList;
		pRoot()=nodeList;
		if((mType == mACWid) ||(mType == geneACWid))
			trans2WidthFirst();
	}

};

typedef enum {
	notUseBadChar=0, 	UseBadChar=1
}UseBadChar_T ;

/*
 * =====================================================================================
 *        Class:  mAcBase
 *  Description:  The graph is implemented with tree
 * =====================================================================================
 */
template<int CHAR_SET=256, StoreType ST=StoreArray, UseBadChar_T USE_BAD_CHAR= UseBadChar>
class mAcBase:public mMatch
{
public:
	typedef acNode<CHAR_SET>* acNodeP;
	typedef acNode<CHAR_SET>  acNodeT;
	enum{char_set = CHAR_SET};

	template<int m, typename T, UseBadChar_T b>
		friend class mAcD;
private:
	AcNodeStore<CHAR_SET, ST> acNodesPool;
	acNodeP m_pCur;
public:
	mAcBase();
	mAcBase(char** pat, int n);
	mAcBase(char** pat, int n, mAlgtype t);
	~mAcBase(){}
	virtual int search(char* txt, int n);
	virtual int search(char* txt);
	virtual int searchGene(char* txt, int n);
	virtual int searchGene(char* txt);
	virtual int searchGene_(char* txt, int n);
	virtual int searchGene_(char* txt);
	virtual int searchGene4(char* txt, int n);
	virtual int searchGene4(char* txt);
	virtual int searchGeneC(char* txt, int n);
	virtual int searchGeneC(char* txt);
	virtual int searchGene4C(char* txt, int n);
	virtual int searchGene4C(char* txt);

    virtual size_t memUsed(){ return memMalloced() + acNodesPool.memMalloced();}
public:
	acNodeP& pRoot(){ return acNodesPool.pRoot();}
	acNodeP& pCur(){ return m_pCur;}
	int mStateNum(){return acNodesPool.mStateNum;}

	int patMatchListLen() {return acNodesPool.patMatchListLen;}
	int* patMatchList(){return acNodesPool.patMatchList;}
	void rewind(){ m_pCur = pRoot();}
protected:
	virtual void compile();
private:	
	static acNodeP nextState(acNodeP cur, Uchar c){ return cur->go[c];}
	static int isMatched(acNodeP state){return (state-> isMatched());} 
	static int* matchedList(acNodeP s){ return s->patIDArray;}

	static acNodeP nextStateT(acNode<CHAR_SET>* base, acNodeP cur, Uchar c){ return cur->go[c];}
	static int isMatchedT(int** base, acNodeP state){return (state-> isMatched());} 
	static int reportMatchT(int** base, acNodeP s, reportFunc rf, int idx ){ return  reportList(matchedList(s), rf,  idx);}
	void buildNFA();
	void buildGeneTrie();
	void buildTrie();
	void buildFailure();
	void convert2DFA();

	template<geneCodeFunc geneCode> int searchGene(acNodeP&, char* txt, int n);
	template<geneCodeFunc geneCode> int searchGene(acNodeP&, char* txt);
	int searchGene4(acNodeP&, char* txt, int n);
	int searchGene4(acNodeP&, char* txt);
	int isBadChar(Uchar c) { return (c >= CHAR_SET);}
private:
	acNodeP makeNode() {return acNodesPool.makeNode(); }
	void reLocate(){ acNodesPool.reLocate(); acNodesPool.transPatList2Array();}

};

template<int CHAR_SET=256, typename idxT=U16>
class acNodeShort
{
public:
	//I16 patID;
	idxT go[CHAR_SET];
public:
	acNodeShort(){memset(this, 0, sizeof(acNodeShort)); }
	idxT get(Uchar c){ return go[c];}
	//int isMatched(){ return patID != -1;}
};

/*
 * =====================================================================================
 *        Class:  mAcD
 *  Description: The graph is implemented with array  
 * =====================================================================================
 */
template<int CHAR_SET=256, typename idxT=U16, UseBadChar_T USE_BAD_CHAR= UseBadChar>
class mAcD:public mMatch
{
public:
	typedef idxT acNodeP;
	typedef acNodeShort<CHAR_SET,idxT> acNodeT;
	enum{char_set = CHAR_SET};
public:
	mAcD(mAcBase<CHAR_SET>& ac,AC_Store_t st= ACWid_First){if(st== ACWid_First) transWidthFrom(ac);else transDepthFrom(ac);}
public:
	virtual int search(char* txt, int n);
	virtual int search(char* txt);
	virtual int searchGene(char* txt, int n);
	virtual int searchGene(char* txt);
	virtual int searchGene4(char* txt, int n);
	virtual int searchGene4(char* txt);
private:
	//! for building DFA (transfer from mAcBase)
	void transDepthFrom(mAcBase<CHAR_SET>& ac);
	void transWidthFrom(mAcBase<CHAR_SET>& ac);
	void mallocMem(int n){ 
		nodes= (acNodeT*)mMalloc(n * sizeof(acNodeT));
		patIDList = (int**)mMalloc( n* sizeof(int*));
		memset(patIDList, 0 , n* sizeof(int*));
	}

	void freeMem(){}
	void rewind(){ m_pCur = pRoot();}
private:
	//! for searching 
	acNodeP nextState(acNodeP cur, Uchar c){ return nodes[cur].get(c);}
	int isMatched(acNodeP state){return (patIDList[state]!=NULL);} 
	int* matchedList(acNodeP s){ return patIDList[s];}
	//! for template
	static acNodeP nextStateT(acNodeT* base, acNodeP cur, Uchar c){ return base[cur].get(c);}
	static int isMatchedT(int** base, acNodeP state){return (base[state] !=NULL);} 
	static int reportMatchT(int** base, acNodeP s, reportFunc rf, int idx ){ return reportList(base[s],rf,idx);}
	acNodeP& pRoot(){return m_pRoot;}
	acNodeP& pCur(){ return m_pCur;}
private:
	acNodeT* nodes;
	acNodeP m_pRoot;
	int** patIDList;
	int mStateNum;
	int* patMatchList;
	acNodeP m_pCur;
};

//! Broad-Storage




}

#include "mAc.hxx"
#endif
