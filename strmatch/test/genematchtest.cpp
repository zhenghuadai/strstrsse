#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include "match.h"
#include "global.h"
#include<stdio.h>
#include "mAc.h"
#include "mWm.h"
#include<stdio.h>
#include "dmutil.h"
#include "io.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <unordered_map>
using namespace dmMatch;
using namespace std;
using json = nlohmann::json;

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

    _U64 startrdt,endrdt;
    double elapsed_time;
    Mtime( &startrdt );
    func.mmatch->searchGene((char*)onetest.text.c_str());
    Mtime( &endrdt );
    elapsed_time= Mdifftime( startrdt, endrdt );

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
        printf(".[chars:%zd clock:%10.0f]", onetest.text.size(), elapsed_time);
    }else{
        printf("\n%s:%s:", func.name.c_str(), onetest.text.size()<32? onetest.text.c_str():onetest.text.substr(0,32).c_str());
        printf("["); for(size_t i = 0; i<tmpResult.size(); i++){printf("(%d %d)", tmpResult[i].v0, tmpResult[i].v1);} printf("] ");
        printf(" expect["); for(size_t i = 0; i<onetest.matched.size(); i++){printf("(%d %d)", onetest.matched[i].v0, onetest.matched[i].v1);} printf("]");
    }
    return passed;
}

void Testmmatch::run()
{
    bool passed = true;
    for(auto onetest :testcases){
        cout<<"############################"<<endl;
        int ps = onetest.patterns.size();
        char** Patts = new char*[ps];
        for(int i =0; i<ps; i++) {
            Patts[i] = (char*)onetest.patterns[i].c_str();
        }
        //Ac<AcBase<4,StoreArray>, UseBadChar> ac(Patts, ps, geneACWid);
        Ac<AcBase<4>> ac(Patts, ps, geneACWid);
        Ac<AcBase<4>> ac1(Patts, ps, geneACDep);
        Ac<AcI<4, U16 >,  UseBadChar> acD(Patts, ps, geneACWid);
        //mWm<> wm(Patts, ps);

        vector<Algorithm> alogrithms = {
            {&ac, "Ac<AcBase<4,StoreArray>width"} ,
            {&ac1, "Ac<AcBase<4,StoreArray>depth"} ,
            {&acD, "Ac<AcI<4, U16 >,  UseBadChar>"}
            //{&wm, "WM"}
            //{&ac1, "AcBase<256> "},
            //{&acD1, "AcI<>"}
        };

        for(auto algorithm : alogrithms){
            passed = run(algorithm, onetest);
            cout<<(passed?"pass ":"failed ") << algorithm.name << endl; 
        }
        //Ac<AcI<256, U16, UseBadChar>, 256, UseBadChar> acD2(ac.getAutomaton(), mACWid);
        delete[] Patts;
    }
}

void Testmmatch::readTestcases( char* fn)
{
    ifstream in(fn);
    json tests = json::parse(in); 
    in.close();
    for (auto test: tests) {
        Testcase t;
        if(test.find("text") != test.end()){
            t.text = test["text"].get<string>(); 
        }else if(test.find("fastafile") != test.end()){
            std::string textfilename = test["fastafile"];
            Pattern_fasta* genome = loadGeneFastaU((char*)textfilename.c_str());
            t.text.assign(genome->str);
            free(genome->str);
            if(genome->name) free(genome->name);
            free(genome);
        }

        if(test.find("patterns") != test.end()){
            for(std::string pat: test["patterns"]){
                t.patterns.push_back(pat);
            }
        }else if (test.find("fasta_patterns_file") != test.end()){
            std::string patfilename = test["patternsfile"];
            list<Pattern_fasta>* pattsList= new list<Pattern_fasta>;
            int ps=loadGenePatternFastaU((char*)patfilename.c_str(),  pattsList);
            for(list<Pattern_fasta>::iterator it=pattsList->begin(); it!=pattsList->end(); it++){
                t.patterns.push_back(string(it->str));
                if(it->name != nullptr) free(it->name);
                if(it->str != nullptr) free(it->str);
            }
            delete pattsList;
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
    t.readTestcases((char*)"genematchtest.testcases");
    t.run();
    (void)argc;
    (void)argv;
    return 0;
}
