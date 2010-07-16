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

#define mAcBase_DEFINITION_HEADER( type ) template<int CHAR_SET, StoreType ST, UseBadChar_T USE_BAD_CHAR> type mAcBase<CHAR_SET, ST, USE_BAD_CHAR>

mAcBase_DEFINITION_HEADER():: mAcBase(char** pat, int n) : mMatch(pat, n)
{
    type = mAC;
    acNodesPool.setMaxStateNum(charNum());
	acNodesPool.type()=type;
	this->compile();
    reLocate();
}

mAcBase_DEFINITION_HEADER()::mAcBase(char** pat, int n, mAlgtype t) : mMatch(pat, n)
{
    type = t;
	acNodesPool.type()=t;
    acNodesPool.setMaxStateNum(charNum());
    if((type==geneAC)||(type==geneACWid) ||(type==geneACDep)){
        printf("build Trie...\n");
        buildGeneTrie();
        printf("build Trie complete\n");
        printf("build Failure...\n");
        buildFailure();
        printf("build Failure complete\n");
        printf("build DFA...\n");
        convert2DFA();
        printf("build DFA complete\n");
    }else {
        compile();
    }
    reLocate();
    printf("build complete\n");
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
        while( *p && (curNode->go[*p]!=NULL)){ curNode=curNode->go[*p]; p++; }
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
        int n = strlen((const char *)p);
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
            while(dst -> go[i] == NULL) dst = dst->failure;
            curNode->failure = dst->go[i];
            if(dst->go[i]->isMatched())
                curNode->addPattern(dst->go[i]);
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


    template<typename NodeT , typename acNodeT, typename matchListT, NodeT (*nextState)( acNodeT*, NodeT, Uchar), int (*isMatched)(matchListT**, NodeT), int (*reportMatch)(matchListT**, NodeT , reportFunc , int ) >
int ACsearchGene(acNodeT* acBase, matchListT** matchListBase, NodeT pRoot, reportFunc report, char* txt)
{
    NodeT state=pRoot;
    for(unsigned char* p = (Uchar*) txt;*p; p++){
        Uchar c = agct2num(*p);
        if(c >=acNodeT::char_set){state= pRoot; continue;}
        state = nextState(acBase, state, c); // state= state->go[*p]; 
        if(isMatched((matchListT**)matchListBase, state)) {
            int ret = reportMatch( (matchListT**)matchListBase, state, report, (char*)p -txt);
        }
    }
    return 0;
}

#define SEARCH_GENE_TEMPLATE(state, geneCode) {\
    unsigned char* p = (Uchar*) txt;	                                      \
    for(;*p; p++){                                                            \
        Uchar c = geneCode(*p);                                               \
        if(USE_BAD_CHAR){if(c >=CHAR_SET){state= pRoot(); continue;}}         \
        state = nextState(state, c);                                          \
        if(isMatched(state)) {                                                \
            int ret = reportList(matchedList(state), (char*)p - txt);         \
        }                                                                     \
    }                                                                         \
    return 0;                                                                 \
}

mAcBase_DEFINITION_HEADER(template<geneCodeFunc geneCode> int)::searchGene(acNodeP& state, char* txt)
{
#if 1

SEARCH_GENE_TEMPLATE(state, geneCode);
#else
    return 	ACsearchGene<acNodeP, acNode<CHAR_SET>, int, mAcBase<CHAR_SET,ST>::nextStateT, mAcBase<CHAR_SET,ST>::isMatchedT, mAcBase<CHAR_SET,ST>::reportMatchT>(NULL, NULL, pRoot(), report, txt);
#endif
}

mAcBase_DEFINITION_HEADER( template<geneCodeFunc geneCode> int)::searchGene(acNodeP& state, char* txt, int n)
{
    unsigned char* p = (Uchar*) txt;	
    for(int i=0; i<n; p++,i++){
        Uchar c = geneCode(*p);
        if(USE_BAD_CHAR){if(c >=CHAR_SET){state= pRoot(); continue;}}
        state = nextState(state, c);// state= state->go[*p]; 
        if(state-> isMatched()) {
            int ret = reportList(matchedList(state), (char*)p - txt);
        }
    }
    return 0;
}
//
//mAcBase_DEFINITION_HEADER(int)::searchGene_(acNodeP& state, char* txt)
//{
//#if 1
//    unsigned char* p = (Uchar*) txt;	
//    for(;*p; p++){
//        Uchar c = agct2num(*p);
//        if(USE_BAD_CHAR){if(c >=CHAR_SET){state= pRoot(); continue;}}
//        state = nextState(state, c); // state= state->go[*p]; 
//        if(isMatched(state)) {
//            int ret = reportList(matchedList(state), (char*)p - txt);
//        }
//    }
//    return 0;
//#else
//    return 	ACsearchGene<acNodeP, acNode<CHAR_SET>, int, mAcBase<CHAR_SET,ST>::nextStateT, mAcBase<CHAR_SET,ST>::isMatchedT, mAcBase<CHAR_SET,ST>::reportMatchT>(NULL, NULL, pRoot(), report, txt);
//#endif
//}
//
//mAcBase_DEFINITION_HEADER(int)::searchGene_(acNodeP& state, char* txt, int n)
//{
//    unsigned char* p = (Uchar*) txt;	
//    for(int i=0; i<n; p++,i++){
//        Uchar c = agct2num(*p);
//        if(USE_BAD_CHAR){if(c >=CHAR_SET){state= pRoot(); continue;}}
//        state = nextState(state, c);// state= state->go[*p]; 
//        if(state-> isMatched()) {
//            int ret = reportList(matchedList(state), (char*)p - txt);
//        }
//    }
//    return 0;
//}
//
//
//

mAcBase_DEFINITION_HEADER(int)::searchGene4(acNodeP& state, char* txt)
{
    unsigned char* p = (Uchar*) txt;	
    for(;*p; p++){
        Uchar c = (*p);
        if(USE_BAD_CHAR){if(c >=CHAR_SET){state= pRoot(); continue;}}
        state = nextState(state, c); // state= state->go[*p]; 
        if(state-> isMatched()) {
            int ret = reportList(matchedList(state), (char*)p - txt);
        }
    }
    return 0;
}

mAcBase_DEFINITION_HEADER(int)::searchGene4(acNodeP& state, char* txt, int n)
{
    unsigned char* p = (Uchar*) txt;	
    for(int i=0; i<n; p++,i++){
        Uchar c = (*p);
        if(USE_BAD_CHAR){if(c>= CHAR_SET){state= pRoot(); continue;}}
        state = nextState(state, c);// state= state->go[*p]; 
        if(state-> isMatched()) {
            int ret = reportList(matchedList(state), (char*)p - txt);
        }
    }
    return 0;
}

mAcBase_DEFINITION_HEADER(int)::searchGene(char* txt)
{
    acNodeP state=pRoot();
    return searchGene<agct2num>(state, txt);
}

mAcBase_DEFINITION_HEADER(int)::searchGene(char* txt, int n)
{
    acNodeP state=pRoot();
    return searchGene<agct2num>(state, txt, n);
}

mAcBase_DEFINITION_HEADER(int)::searchGene_(char* txt)
{
    acNodeP state=pRoot();
    return searchGene<agct2pairnum>(state, txt);
}

mAcBase_DEFINITION_HEADER(int)::searchGene_(char* txt, int n)
{
    acNodeP state=pRoot();
    return searchGene<agct2pairnum>(state, txt, n);
}



mAcBase_DEFINITION_HEADER(int)::searchGene4(char* txt)
{
    acNodeP state=pRoot();
    return searchGene4(state, txt);
}

mAcBase_DEFINITION_HEADER(int)::searchGene4(char* txt, int n)
{
    acNodeP state=pRoot();
    return searchGene4(state, txt, n);
}

mAcBase_DEFINITION_HEADER(int)::searchGeneC(char* txt)
{
    acNodeP state=pCur();
    int ret=searchGene<agct2num>(state, txt);
    pCur()=state;
    return ret; 
}

mAcBase_DEFINITION_HEADER(int)::searchGeneC(char* txt, int n)
{
    acNodeP state=pCur();
    int ret=searchGene<agct2num>(state, txt, n);
    pCur()=state;
    return  ret; 
}


mAcBase_DEFINITION_HEADER(int)::searchGene4C(char* txt)
{
    acNodeP state=pCur();
    int ret=searchGene4(state, txt);
    pCur()=state;
    return  ret; 
}

mAcBase_DEFINITION_HEADER(int)::searchGene4C(char* txt, int n)
{
    acNodeP state=pCur();
    int ret=searchGene4(state, txt, n);
    pCur()=state;
    return  ret; 
}





mAcBase_DEFINITION_HEADER(int)::search(char* txt)
{
    printf("search...\n");
    unsigned char* p = (Uchar*) txt;	
    acNodeP state=pRoot();
    for(;*p; p++){
        state = nextState(state, *p); // state= state->go[*p]; 
        if(state-> isMatched()) {
            int ret = reportList(matchedList(state), (char*)p - txt);
        }
    }
    return 0;
}

mAcBase_DEFINITION_HEADER(int)::search(char* txt, int n)
{
    unsigned char* p = (Uchar*) txt;	
    acNodeP state=pRoot();
    for(; p<(unsigned char*)txt + n; p++){
        state = nextState(state, *p);// state= state->go[*p]; 
        if(state-> isMatched()) {
            int ret = reportList(matchedList(state), (char*)p - txt);
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

    template<int CHAR_SET, typename idxT,  class travalT>
void reoderacNode(AcNodeStore<CHAR_SET, StoreArray>& ac, acNode<CHAR_SET>* nodes, int** patIDList, int* patMatchList)
{
    int curState=0;
    int mStateNum = ac.mStateNum;
    typename mAcBase<CHAR_SET>::acNodeP* Map2= new typename mAcBase<CHAR_SET>::acNodeP [mStateNum];
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
    for(int s=0;s<mStateNum;s++){
        for(int i=0;i< CHAR_SET; i++) {
            nodes[s].go[i] = nodes + MapIndex(Map2[s]->go[i] ); 
        }
        nodes[s].failure = nodes + MapIndex( Map2[s]-> failure);
        nodes[s].patIDList= Map2[s] ->patIDList;
        nodes[s].patIDArray = Map2[s] -> patIDArray;
        nodes[s].mMatchNum= Map2[s] -> mMatchNum;
    }

    delete Map2;
}

template<int CHAR_SET>
void AcNodeStore<CHAR_SET, StoreArray>::trans2WidthFirst()
{
    acNodeP tmpNodeList = (acNodeP)mMalloc(mStateNum* sizeof(acNodeT)); 
	reoderacNode <CHAR_SET, Uint, queue<typename mAcBase<CHAR_SET>::acNodeP> >(*this, tmpNodeList ,NULL , NULL);
    clean(nodeList);
    nodeList = tmpNodeList;
    pRoot()= nodeList;
}

#define mAcD_DEFINITION_HEADER( type ) template<int CHAR_SET, typename idxT, UseBadChar_T USE_BAD_CHAR> type mAcD<CHAR_SET, idxT, USE_BAD_CHAR>
mAcD_DEFINITION_HEADER(void)::transWidthFrom(mAcBase<CHAR_SET>& ac)
{
    mStateNum = ac.mStateNum();
    mallocMem(mStateNum);
    patMatchList = (int*) mMalloc( ac. patMatchListLen()* sizeof(int));
    transNode2Short<CHAR_SET, idxT, queue<typename mAcBase<CHAR_SET>::acNodeP> >(ac, nodes, patIDList, patMatchList);
    pRoot() = 0;
}

mAcD_DEFINITION_HEADER(void)::transDepthFrom(mAcBase<CHAR_SET>& ac)
{
    mStateNum = ac.mStateNum();
    mallocMem(mStateNum);
    patMatchList = (int*) mMalloc( ac. patMatchListLen()* sizeof(int));
    transNode2Short<CHAR_SET,idxT, stack<typename mAcBase<CHAR_SET>::acNodeP> >(ac, nodes, patIDList, patMatchList);
    pRoot() = 0;
}

mAcD_DEFINITION_HEADER(int)
::search(char* txt, int n)
{
    return 0;
}

mAcD_DEFINITION_HEADER(int)
::search(char* txt)
{

    return 0;
}

mAcD_DEFINITION_HEADER(int)
::searchGene(char* txt, int n)
{
    return 0;
}

mAcD_DEFINITION_HEADER(int)
::searchGene(char* txt)
{
#if 1
    unsigned char* p = (Uchar*) txt;	
    acNodeP state=pRoot();
    for(;*p; p++){
        Uchar c = agct2num(*p);
        if(c >=CHAR_SET){state= pRoot(); continue;}
        state = nextState(state, c); 
        if( isMatched(state)) {
            int ret = reportList(matchedList(state), (char*)p - txt);
        }
    }
    return 0;
#else
    return 	ACsearchGene<acNodeP, acNodeShort<CHAR_SET,idxT>, int, mAcD<CHAR_SET,idxT>::nextStateT, mAcD<CHAR_SET,idxT>::isMatchedT, mAcD<CHAR_SET,idxT>::reportMatchT>(nodes, patIDList,pRoot(), report, txt);
#endif

}

mAcD_DEFINITION_HEADER(int)::searchGene4(char* txt, int n)
{

    return 0;
}

mAcD_DEFINITION_HEADER(int)::searchGene4(char* txt)
{

    return 0;
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
