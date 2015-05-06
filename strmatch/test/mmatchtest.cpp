#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include "match.h"
#include "global.h"
#include<stdio.h>
#include "mAc.h"
#include "mWm.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <unordered_map>
using namespace dmMatch;
using namespace std;
using json = nlohmann::json;

static char** gPatList=0;
static char* curText = 0;
class int2{
    public:
        union{
            struct {int v0, v1;};
            long long v;
        };
        int2(int v0, int v1):v0(v0),v1(v1){}
        bool operator == (const int2 o) { return (v0 == o.v0 && v1 == o.v1);}
};

class Testcase{
    public:
        string text;
        vector<string> patterns;
        vector<int2> matched;
        unordered_map<int, bool> resultMap;
        Testcase(string& text):text(text){}
        Testcase(){}
};

class Algorithm{
    public:
        mMatch* mmatch;
        string name;
};
class Testmmatch{
    private:
        vector<Testcase> testcases;
    public:
        Testmmatch(){
            //setReportFunc(test_report);
        }

        void readTestcases(char* filename);
        void run();
    private:
        bool run(Algorithm& func, Testcase& onetest);
        static vector<int2> tmpResult;

        static    int  myreport(int patID, int idx)
        {
            tmpResult.push_back(int2(patID, idx));
            return mMatch::SEARCH_CONTINUE;
        }

};

    template<class T>
void runSearch(T& func, char* Text)
{
    _U64 startrdt,endrdt;
    double elapsed_time;
    printf("mem:%d\n", func.memUsed());
    Mtime( &startrdt );
    func.search(Text);
    Mtime( &endrdt );
    elapsed_time= Mdifftime( startrdt, endrdt );
    printf("\nalgorithm %s takes\t %20.15f seconds.\n","ACD", elapsed_time );
    printf("\n\n");

}

vector<int2> Testmmatch::tmpResult;
bool Testmmatch::run(Algorithm& func, Testcase& onetest)
{
    bool passed = true;
    func.mmatch->setReportFunc(myreport);
    tmpResult.clear();
    func.mmatch->search((char*)onetest.text.c_str());

    passed = true;
    if(tmpResult.size() != onetest.matched.size()){
        passed = false;
    }else{
        for(size_t i = 0; i<tmpResult.size(); i++){
            //if(!(tmpResult[i] == onetest.matched[i])){
            //    passed = false;
            //    break;
            //}
            if(onetest.resultMap.end() == onetest.resultMap.find( (tmpResult[i].v0<< 16 ) | tmpResult[i].v1)){
                passed = false;
            }
        }
    }
    if(passed){
        printf(".");
    }else{
        printf("\n%s:%s:", func.name.c_str(), onetest.text.c_str());
        printf("["); for(size_t i = 0; i<tmpResult.size(); i++){printf("(%d %d)", tmpResult[i].v0, tmpResult[i].v1);} printf("] ");
        printf(" expect["); for(size_t i = 0; i<onetest.matched.size(); i++){printf("(%d %d)", onetest.matched[i].v0, onetest.matched[i].v1);} printf("]");
    }
    return passed;
}

void Testmmatch::run()
{
    bool passed = true;
    for(auto onetest :testcases){
        int ps = onetest.patterns.size();
        char** Patts = new char*[ps];
        for(int i =0; i<ps; i++) Patts[i] = (char*)onetest.patterns[i].c_str();
        Ac<mAcBase<256,StoreArray>, UseBadChar> ac(Patts, ps, mACWid);
        //Ac<mAcD<256, U16 >,  UseBadChar> acD(Patts, ps, mACWid);
        mWm<> wm(Patts, ps);
        //mAcBase<256> ac1(Patts, ps, mACWid);
        //mAcD<> acD1(ac.getAutomaton());

        vector<Algorithm> alogrithms = {
            {&ac, "Ac<mAcBase<256,StoreArray>"}, 
            //{&acD, "Ac<mAcD<256, U16 >,  UseBadChar>"},
            {&wm, "WM"}
            //{&ac1, "mAcBase<256> "},
            //{&acD1, "mAcD<>"}
        };

        for(auto algorithm : alogrithms){
            passed = run(algorithm, onetest);
            cout<<(passed?"pass ":"failed ") << algorithm.name << endl; 
        }
        //Ac<mAcD<256, U16, UseBadChar>, 256, UseBadChar> acD2(ac.getAutomaton(), mACWid);
        delete[] Patts;
    }
}

void Testmmatch::readTestcases( char* fn)
{
    ifstream in(fn);
    json tests = json::parse(in); 
    for (auto test: tests) {
        Testcase t;
        std::string str = (test["text"]);
        t.text = str;
        for(std::string pat: test["patterns"]){
            t.patterns.push_back(pat);
        }
        for(auto r:test["Result"]){
            int patid = r["pat"].get<int>();
            int pos = r["pos"].get<int>();
            t.matched.push_back(int2(patid, pos));
            t.resultMap[(patid<<16) | pos] = true;
        }
        testcases.push_back(t);
    }
}


int main(int argc,char *argv[])
{
    Testmmatch t;
    t.readTestcases("mmatchtest.testcases");
    t.run();
    return 0;
}
