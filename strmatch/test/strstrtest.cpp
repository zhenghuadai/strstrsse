/*
 * =====================================================================================
 *
 *       Filename:  strstrtest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/04/2015 11:39:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <vector>
#include <stack>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "match.h"
#include "report.h"
#include <string.h>

using namespace std;

class Testcase{
    public:
    string text;
    string patten;
    vector<int> matched;
};

class Algorithm{
    public:
    typedef char* (* strstr_t)(char * text,char * pat);
    typedef char* (* strstr_t2)(char * text,char * pat,int n, int m);
    strstr_t strstr;
    strstr_t2 strstr2;
    string name;

};

class Teststrstr{
    private:
    vector<Algorithm> alogrithms = {
        {bfstr       , bfstr2    ,"bfstr       "},
        {Smp         , Smp2      ,"Smp         "},
        {Skmp        , Skmp2     ,"Skmp        "},
        {Sbm         , Sbm2      ,"Sbm         "},
        {Sbmh        , Sbmh2     ,"Sbmh        "},
        {Sbmhs       , Sbmhs2    ,"Sbmhs       "},
        {Ssmith      , Ssmith2   ,"Ssmith      "},
        {Sdfa        , Sdfa2     ,"Sdfa        "},
        {Sbdm        , Sbdm2     ,"Sbdm        "},
        {Sbndm       , Sbndm2    ,"Sbndm       "},
        {Sbom        , Sbom2     ,"Sbom        "},
        {Sshiftor    , Sshiftor2 ,"Sshiftor    "},
        {Sshiftand   , Sshiftand2,"Sshiftand   "},
        {Skr         , Skr2      ,"Skr         "},
        {Sbyh        , Sbyh2     ,"Sbyh        "},
        {Sskip       , Sskip2    ,"Sskip       "},
        {Skmpskip    , Skmpskip2 ,"Skmpskip    "},
        {bfstr       , bfstr2    ,"bfstr       "},
        {lstrstr     , nullptr   ,"lstrstr     "},
#ifdef SSE4
        {strstrsse42 , nullptr   ,"strstrsse42 "},
        {strstrsse42a , nullptr  ,"strstrsse42a"},
#endif
        {strstrsse   , nullptr   ,"strstrsse   "}
    };
    vector<Testcase> testcases;
    public:
    Teststrstr(){
		setReportFunc(test_report);
    }

    void readTestcases(char* filename);
    void run();
    private:
    static vector<int> tmpResult;

    static int test_report(const char* text, int idx, const char* pat)
    {
        (void) text;
        (void) pat;
        (void) idx;
        tmpResult.push_back(idx);
        return SEARCH_CONTINUE;
    }
};

vector<int> Teststrstr::tmpResult;
void Teststrstr::run()
{
    for(auto func : alogrithms){
        bool passed = true;
        for(auto onetest :testcases){
            tmpResult.clear();
            func.strstr((char*)onetest.text.c_str(), (char*)onetest.patten.c_str());

            passed = true;
            if(tmpResult.size() != onetest.matched.size()){
                passed = false;
            }else{
                for(size_t i = 0; i<tmpResult.size(); i++){
                    if(tmpResult[i] != onetest.matched[i]){
                        passed = false;
                        break;
                    }
                }
            }
            if(passed){
                printf(".");
            }else{
                printf("\n%s:%s:%s ", func.name.c_str(), onetest.text.c_str(), onetest.patten.c_str());
                printf("["); for(size_t i = 0; i<tmpResult.size(); i++){printf("%d ", tmpResult[i]);} printf("] ");
                printf(" expect["); for(size_t i = 0; i<onetest.matched.size(); i++){printf("%d ", onetest.matched[i]);} printf("]");
                break;
            }
        }
        cout<<(passed?"pass ":"failed ") << func.name <<endl; 
    }
}

void Teststrstr::readTestcases( char* fn)
{
    char* buf = new char[1024 * 10];
    ifstream in(fn);
    while(!in.eof()){
        in.getline(buf, 1024*10);
        char* pSep0 = strstr(buf, "{\"");
        if(pSep0 == NULL ){
            continue;
        }
        char* pSep1 = strstr(pSep0 + 1, "\", \"");
        if(pSep1 == NULL ){
            continue;
        }
        char* pSep2 = strstr(pSep1 + 1, "\", {");
        if( pSep2 == NULL){
            continue;
        }

        pSep0 += 2;
        pSep1[0] = 0;
        pSep2[0] = 0;
        char* text = pSep0;
        char* pat = (pSep1 + 4); 
        char* p = pSep2 + 4; 
        Testcase t = {string(text), string(pat), {}};

        while( *p != 0){
            if( (*p) >= '0' && (*p) <='9') {
                int idx = atoi(p);
                t.matched.push_back(idx);
                p = strstr(p, " ");
                if(p == NULL) break;
                p ++;
            }else{
                p ++;
            }
        }

        testcases.push_back(t);
    }
    delete[] buf;
}

int main()
{
    Teststrstr t;
    t.readTestcases("strstrtest.testcases");
    t.run();
}
