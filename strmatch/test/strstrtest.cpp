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
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

class Testcase{
    public:
    string text;
    string pattern;
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
            func.strstr((char*)onetest.text.c_str(), (char*)onetest.pattern.c_str());

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
                printf("\n%s:%s:%s ", func.name.c_str(), onetest.text.c_str(), onetest.pattern.c_str());
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
    ifstream in(fn);
    json tests = json::parse(in); 
    in.close();
    for (auto test: tests) {
        std::string text ;
        Testcase t;
        if(test.find("text") != test.end()){
            t.text = test["text"].get<string>(); 
        }else if(test.find("textfile") != test.end()){
            std::string textfilename = test["textfile"];
            ifstream textfile(textfilename);
            istreambuf_iterator<char> beg(textfile), end;
            t.text.assign(beg, end);
            textfile.close();
        }
        t.pattern =  test["pattern"].get<string>();
        t.matched= test["Result"].get<vector<int>>();
        testcases.push_back(t);
    }
   
}

int main()
{
    Teststrstr t;
    t.readTestcases((char*)"strstrtest.testcases");
    t.run();
}
