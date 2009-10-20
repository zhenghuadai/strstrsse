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
    public:
        acNode(){memset(this, 0, sizeof(acNode*)*CHAR_SET); }
        void adjust(SSize bytes){ for(int i=0;i<CHAR_SET;i++){if(go[i]!=0) go[i] =(acNode*) ( ((char*)go[i]) + bytes); }  if(failure!= NULL) failure = (acNode*)(((char*)failure)+bytes);}
#if 1
        ~acNode(){if(patIDList) delete patIDList;}
        int isMatched(){ return patIDList != NULL;}
        void addPattern(int i){if(!patIDList){patIDList= new list<int>(); patIDList->push_back(i);} }
        int report(reportFunc reportf, int idx){
        int ret;
        for(typename list<int>::iterator i= patIDList->begin(); i!= patIDList->end(); i++) ret = reportf(*i, idx);
        return ret;
        }
        void addPattern(acNode* node){
            if(!patIDList) patIDList = new list<int>();
            for(typename list<int>::iterator i= node->patIDList->begin(); i!= node->patIDList->end(); i++) 
               patIDList->push_back(*i); 
        }
#else 
        ~acNode(){}
        int isMatched(){ return patID!=0; }
        void addPattern(int i){patID = i;  }
        int report(reportFunc reportf, int idx){
            return  reportf(patID, idx);
        }
        void addPattern(acNode* node){}

#endif

};
typedef enum {
StoreList, StoreArray
}StoreType;

template<int CHAR_SET, StoreType ST>
class AcNodeStore
{
    public:
        typedef acNode<CHAR_SET>* acNodeP;
    public:
        acNodeP nodeList;//! root is the first element
        acNodeP pRoot;
        int mStateNum;
        //int type;
};

template<int CHAR_SET>
class AcNodeStore<CHAR_SET, StoreList>
{
    public:
        typedef acNode<CHAR_SET>* acNodeP;
    public:
        list<acNodeP> nodeList;//! root is the first element
        acNodeP pRoot;
        int mStateNum;
        int mMaxStateNum;
    public:
        AcNodeStore():pRoot(0), mStateNum(0), mMaxStateNum(0){};
        ~AcNodeStore(){ this -> clean(nodeList);}
        void setMaxStateNum(int n){mMaxStateNum = n;}
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
            pRoot = 0;
#endif
        }

        void reLocate(){}
        acNodeP makeNode() {mStateNum++; acNodeP newNode= new acNode<CHAR_SET>(); nodeList.push_back(newNode); return newNode;};

};

template<int CHAR_SET>
class AcNodeStore<CHAR_SET, StoreArray>
{
    public:
        typedef acNode<CHAR_SET>* acNodeP;
        typedef acNode<CHAR_SET>  acNodeT;
    public:
        acNodeP nodeList;//! root is the first element
        acNodeP pRoot;
        int mStateNum;
        int mMaxStateNum;
    public:
        AcNodeStore():pRoot(0), mStateNum(0), mMaxStateNum(0){};
        ~AcNodeStore(){ this -> clean(nodeList);}
        void setMaxStateNum(int n){mMaxStateNum = n;}
    public:
        void clean(acNodeP tNodeList){
            for(int i=0;i< mStateNum; i++){
                tNodeList[i].~acNodeT();
            } 
            free(tNodeList);
        }
        acNodeP makeNode() {
            if(pRoot==0) nodeList = (acNodeP)malloc(mMaxStateNum * sizeof(acNodeT)); 
            mStateNum++;  acNodeP newNode= new(&nodeList[mStateNum-1]) acNodeT;
            return newNode;
        }
        void reLocate(){
            acNodeP tmpNodeList = (acNodeP)malloc(mStateNum* sizeof(acNodeT)); 
            memcpy(tmpNodeList, nodeList, mStateNum*sizeof(acNodeT)); 
            for(int i=0;i< mStateNum;i++){ tmpNodeList[i].adjust((SSize)tmpNodeList - (SSize)nodeList);}
            free(nodeList); 
            nodeList = tmpNodeList;
            pRoot=nodeList;
        }

};

//template<int CHAR_SET=256, StoreType ST=StoreArray>
template<int CHAR_SET=256, StoreType ST=StoreList>
class mAcBase:public mMatch
{
    public:
        typedef acNode<CHAR_SET>* acNodeP;
        typedef acNode<CHAR_SET>  acNodeT;
        enum{char_set = CHAR_SET};

        template<int m>
            friend class mAcD;
    private:
        AcNodeStore<CHAR_SET, ST> acNodesPool;
        acNodeP& pRoot(){ return acNodesPool.pRoot;}
        int mStateNum(){return acNodesPool.mStateNum;}
    public:
        mAcBase();
        mAcBase(char** pat, int n);
        mAcBase(char** pat, int n, mAlgtype t);
        ~mAcBase(){}
        virtual int search(char* txt, int n);
        virtual int search(char* txt);
        virtual int searchGene(char* txt, int n);
        virtual int searchGene(char* txt);
        virtual int searchGene4(char* txt, int n);
        virtual int searchGene4(char* txt);
    protected:
        virtual void compile();
    private:	
        static acNodeP nextState(acNodeP cur, Uchar c){ return cur->go[c];}
        static int isMatched(acNodeP state){return (state-> isMatched());} 
        static acNodeP nextStateT(acNode<CHAR_SET>* base, acNodeP cur, Uchar c){ return cur->go[c];}
        static int isMatchedT(list<int>** base, acNodeP state){return (state-> isMatched());} 
        static int reportMatchT(list<int>** base, acNodeP s, reportFunc rf, int idx ){ return s->report(rf,  idx);}
        void buildNFA();
        void buildGeneTrie();
        void buildTrie();
        void buildFailure();
        void convertDFA();
    private:
        acNodeP makeNode() {return acNodesPool.makeNode(); }
        void reLocate(){ acNodesPool.reLocate(); }

};

template<int CHAR_SET=256>
class acNodeShort
{
    public:
        //I16 patID;
        U16 go[CHAR_SET];
    public:
        acNodeShort(){memset(this, 0, sizeof(acNodeShort)); }
        //int isMatched(){ return patID != -1;}
};

typedef enum {ACDep_First, ACWid_First} AC_Store_t;
//! Depth-Storage 
template<int CHAR_SET=256>
class mAcD:public mMatch
{
    public:
        typedef U16 acNodeP;
        mAcD(mAcBase<CHAR_SET>& ac,AC_Store_t st= ACWid_First){if(st== ACWid_First) transWidthFrom(ac);else transDepthFrom(ac);}
    public:
        virtual int search(char* txt, int n);
        virtual int search(char* txt);
        virtual int searchGene(char* txt, int n);
        virtual int searchGene(char* txt);
        virtual int searchGene4(char* txt, int n);
        virtual int searchGene4(char* txt);
    private:
        void transDepthFrom(mAcBase<CHAR_SET>& ac);
        void transWidthFrom(mAcBase<CHAR_SET>& ac);
        void mallocMem(int n){ 
            nodes= (acNodeShort<CHAR_SET>*)malloc(n * sizeof(acNodeShort<CHAR_SET>));
            patIDList = (list<int>**)malloc( n* sizeof(list<int>*));
        }

        void freeMem(){}
    private:
        //static acNodeP nextState(acNodeP cur, Uchar c){ return cur->go[c];}
        //static int isMatched(acNodeP state){return (state-> isMatched());} 
        static acNodeP nextStateT(acNodeShort<CHAR_SET>* base, acNodeP cur, Uchar c){ return base[cur].go[c];}
        static int isMatchedT(list<int>** base, acNodeP state){return (base[state] !=NULL);} 
        static int reportMatchT(list<int>** base, acNodeP s, reportFunc rf, int idx ){ return 1;}
    private:
        acNodeShort<CHAR_SET>* nodes;
        acNodeP pRoot;
        list<int>** patIDList;
        int mStateNum;
};

//! Broad-Storage




}

#include "mAc.hxx"
#endif
