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
#include <iostream>

#include "mMatch.h"
namespace dmMatch{

#define mAcBase_DEFINITION_HEADER( type ) template<int CHAR_SET, StoreType ST> type mAcBase<CHAR_SET, ST>

mAcBase_DEFINITION_HEADER():: mAcBase(char** pat, int n) //: mMatch(pat, n)
{
    initAc(pat,n);
}

mAcBase_DEFINITION_HEADER(void ):: initAc(char** pat, int n)
{
    initAc(pat, n , (mAlgtype) 0);
}

mAcBase_DEFINITION_HEADER()::mAcBase(char** pat, int n, mAlgtype t) //: mMatch(pat, n)
{
    initAc(pat, n, t);
}

mAcBase_DEFINITION_HEADER(void)::initAc(char** pat, int n, mAlgtype t) 
{
    setPatterns(pat, n);
    type = t;
	acNodesPool.type()=t;
    acNodesPool.setMaxStateNum(charNum() + 1); // the root takes 1
    if((type==geneAC)||(type==geneACWid) ||(type==geneACDep)){
        debprintf("build Trie...\n");
        buildGeneTrie();
        debprintf("build Trie complete\n");
        debprintf("build Failure...\n");
        buildFailure();
        debprintf("build Failure complete\n");
        debprintf("build DFA...\n");
        convert2DFA();
        debprintf("build DFA complete\n");
    }else {
        compile();
    }
    reLocate();
    debprintf("build complete\n");
    //printf("#states num: %d\n", mStateNum);
}

mAcBase_DEFINITION_HEADER(void)::compile()
{
    buildNFA();
    convert2DFA();
}

mAcBase_DEFINITION_HEADER(void)::buildNFA()
{
    buildTrie();
    buildFailure();
}

mAcBase_DEFINITION_HEADER(void)::buildTrie()
{
    pRoot()= makeNode();	
    for(int i=0;i<mPatNum; i++){
        acNodeP curNode = pRoot();
        char* p = mPatterns[i];
        while( *p && (curNode->go[(int)*p]!=NULL)){ curNode=curNode->go[(int)*p]; p++; }
        for(; *p; p++){
            Uchar c=*p;
            curNode-> go[c] = makeNode();
            curNode = curNode->go[c];
        }
        curNode->addPattern(i);
    }

}

mAcBase_DEFINITION_HEADER(void)::buildGeneTrie()
{
    pRoot()= makeNode();	
    for(int i=0;i<mPatNum; i++){
        acNodeP curNode = pRoot();
        unsigned char* p =(unsigned char*) mPatterns[i];
        //int n = strlen((const char *)p);
        while( *p && (curNode->go[agct2num4(*p)]!=NULL)){ 
            curNode=curNode->go[agct2num4(*p)]; p++; }
        for(; *p; p++){
            Uchar c=agct2num4(*p);
            curNode-> go[c] = makeNode();
            curNode = curNode->go[c];
        }
        curNode->addPattern(i);
    }

}


mAcBase_DEFINITION_HEADER(void)::buildFailure()
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
            while(dst -> go[i] == NULL){ 
                dst = dst->failure;
            }
            curNode->failure = dst->go[i];
            if(dst->go[i]->isMatched()){
                curNode->addPattern(dst->go[i]);
            }
        }

    }
}

mAcBase_DEFINITION_HEADER(void)::convert2DFA()
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

template<typename T>
T top( queue<T>& q){return q.front();} 

template<typename T>
T top( stack<T>& q){return q.top();} 

    template<int CHAR_SET, typename idxT,  class travalT>
void reoderacNode(AcNodeStore<CHAR_SET, StoreArray>& ac, acNode<CHAR_SET>* nodes, int** patIDList, int* patMatchList)
{
    int curState=0;
    int mStateNum = ac.mStateNum;
    typename mAcBase<CHAR_SET>::acNodeP* Map2= new typename mAcBase<CHAR_SET>::acNodeP [mStateNum];
    travalT Queue;
    (void)patIDList;
    (void)patMatchList;
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
    ASSERT(mStateNum== curState);
    for(int s=0;s<mStateNum;s++){
        for(int i=0;i< CHAR_SET; i++) {
            nodes[s].go[i] = nodes + MapIndex(Map2[s]->go[i] ); 
        }
        nodes[s].failure = nodes + MapIndex( Map2[s]-> failure);
        nodes[s].patIDList= Map2[s] ->patIDList;
        nodes[s].patIDArray = Map2[s] -> patIDArray;
        nodes[s].mMatchNum= Map2[s] -> mMatchNum;
    }

    delete Map;
    delete Map2;
}

    template<int CHAR_SET>
void AcNodeStore<CHAR_SET, StoreArray>::trans2WidthFirst()
{
    acNodeP tmpNodeList = (acNodeP)MMalloc(mStateNum* sizeof(acNodeT)); 
    reoderacNode <CHAR_SET, Uint, queue<typename mAcBase<CHAR_SET>::acNodeP> >(*this, tmpNodeList ,NULL , NULL);
    clean(nodeList);
    nodeList = tmpNodeList;
    pRoot()= nodeList;
}

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
    //#define MapIndex(a) Map[a - ac.pRoot()]
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
    ASSERT(mStateNum== curState);
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


#define mAcD_DEFINITION_HEADER( type ) template<int CHAR_SET, typename idxT> type mAcD<CHAR_SET, idxT >
mAcD_DEFINITION_HEADER(void)::transWidthFrom(mAcBase<CHAR_SET>& ac)
{
    mStateNum = ac.mStateNum();
    mallocMem(mStateNum);
    patMatchList = (int*) MMalloc( ac. patMatchListLen()* sizeof(int));
    transNode2Short<CHAR_SET, idxT, queue<typename mAcBase<CHAR_SET>::acNodeP> >(ac, nodes, patIDList, patMatchList);
    pRoot() = 0;
}

mAcD_DEFINITION_HEADER(void)::transDepthFrom(mAcBase<CHAR_SET>& ac)
{
    mStateNum = ac.mStateNum();
    mallocMem(mStateNum);
    patMatchList = (int*) MMalloc( ac. patMatchListLen()* sizeof(int));
    transNode2Short<CHAR_SET,idxT, stack<typename mAcBase<CHAR_SET>::acNodeP> >(ac, nodes, patIDList, patMatchList);
    pRoot() = 0;
}

#define Ac_DEFINITION_HEADER( type ) template<class Acautomaton,  UseBadChar_T USE_BAD_CHAR> type Ac<Acautomaton,  USE_BAD_CHAR>

Ac_DEFINITION_HEADER(template<geneCodeFunc geneCode> int)::searchGene(acNodeP& state, char* txt)
{
#if 1
    unsigned char* p = (Uchar*) txt;	                                      
    for(;*p; p++){                                                            
        Uchar c = geneCode(*p);                                               
        if(USE_BAD_CHAR){if(c >=CHAR_SET){state= pRoot(); continue;}}         
        state = nextState(state, c);                                          
        if(isMatched(state)) {                                                
            int ret = reportList(matchedList(state), (char*)p - txt);         
            (void)ret;
        }                                                                     
    }                                                                         
    return 0;
#else
#endif
}

Ac_DEFINITION_HEADER( template<geneCodeFunc geneCode> int)::searchGene(acNodeP& state, char* txt, int n)
{
    unsigned char* p = (Uchar*) txt;	                                       
    for(; p<(unsigned char*)txt + n; p++){                                     
        Uchar c = geneCode(*p);                                                
        if(USE_BAD_CHAR){if(c >=CHAR_SET){state= pRoot(); continue;}}          
        state = nextState(state, c);                                           
        if(isMatched(state)) {                                              
            int ret = reportList(matchedList(state), (char*)p - txt);          
            (void)ret;
        }                                                                      
    }                                                                          
    return 0;
}


Ac_DEFINITION_HEADER(int)::search(acNodeP& state, char* txt)
{
    unsigned char* p = (Uchar*) txt;	                                   
    for(;*p; p++){                                                         
        Uchar c = (*p);                                                    
        if(USE_BAD_CHAR){if(c >=CHAR_SET){state= pRoot(); continue;}}      
        state = nextState(state, c);                                       
        if(isMatched(state)) {                                          
            int ret = reportList(matchedList(state), (char*)p - txt);      
            (void)ret;
        }                                                                  
    }                                                                      
    return 0;
}

Ac_DEFINITION_HEADER(int)::search(acNodeP& state, char* txt, int n)
{
    unsigned char* p = (Uchar*) txt;	                                    
    for(; p<(unsigned char*)txt + n; p++){                                  
        Uchar c = (*p);                                                     
        if(USE_BAD_CHAR){if(c>= CHAR_SET){state= pRoot(); continue;}}       
        state = nextState(state, c);                                        
        if(isMatched(state)) {                                           
            int ret = reportList(matchedList(state), (char*)p - txt);       
            (void)ret;
        }                                                                   
    }                                                                       
    return 0;
}



Ac_DEFINITION_HEADER(int)::searchGene(char* txt)
{
    acNodeP state=pRoot();
    return searchGene<agct2num>(state, txt);
}

Ac_DEFINITION_HEADER(int)::searchGene(char* txt, int n)
{
    acNodeP state=pRoot();
    return searchGene<agct2num>(state, txt, n);
}

Ac_DEFINITION_HEADER(int)::searchGene_(char* txt)
{
    acNodeP state=pRoot();
    return searchGene<agct2pairnum>(state, txt);
}

Ac_DEFINITION_HEADER(int)::searchGene_(char* txt, int n)
{
    acNodeP state=pRoot();
    return searchGene<agct2pairnum>(state, txt, n);
}


Ac_DEFINITION_HEADER(int)::searchGeneC(char* txt)
{
    acNodeP state=pCur();
    int ret=searchGene<agct2num>(state, txt);
    pCur()=state;
    return ret; 
}

Ac_DEFINITION_HEADER(int)::searchGeneC(char* txt, int n)
{
    acNodeP state=pCur();
    int ret=searchGene<agct2num>(state, txt, n);
    pCur()=state;
    return  ret; 
}


Ac_DEFINITION_HEADER(int)::searchC(char* txt)
{
    acNodeP state=pCur();
    int ret=search(state, txt);
    pCur()=state;
    return  ret; 
}

Ac_DEFINITION_HEADER(int)::searchC(char* txt, int n)
{
    acNodeP state=pCur();
    int ret=search(state, txt, n);
    pCur()=state;
    return  ret; 
}

Ac_DEFINITION_HEADER(int)::search(char* txt)
{
    acNodeP state=pRoot();
    int ret=search(state, txt);
    return  ret; 
}

Ac_DEFINITION_HEADER(int)::search(char* txt, int n)
{
    acNodeP state=pRoot();
    int ret=search(state, txt,n);
    pCur()=state;
    return  ret; 
}















}
#endif
