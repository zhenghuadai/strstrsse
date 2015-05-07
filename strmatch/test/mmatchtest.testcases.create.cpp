/*
 * =====================================================================================
 *
 *       Filename:  create_strstr_testcases.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/05/2015 01:19:22 AM
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
#include <string.h>
#include "json.hpp"
#include "dmutil.h"
#include "io.h"

using namespace std;
using json = nlohmann::json;
struct int2{
    int v0, v1;
    int2(int v0, int v1):v0(v0),v1(v1){}
};
typedef unsigned long long u64;
int main(int argc, char** argv)
{
    char* fin, *fout;
    if(argc == 1){
        fin = (char*)"mmatchtest.testcases.raw";
        fout = (char*)"mmatchtest.testcases";
    }else{
        fin = argv[1];
        fout = argv[2];
    }
    ifstream in(fin);
    json oTests;
    {
        ifstream in2(fout);
        in2.seekg(0, ios_base::end);
        if(in2.tellg() > 10){
            in2.seekg(0, ios_base::beg);
            oTests = json::parse(in2);
        }
        in2.close();
    }
    ofstream out(fout);
    json tests = json::parse(in); 
    in.close();
    for (auto test: tests) {
        std::string text ;
        if(test.find("text") != test.end()){
            text = test["text"].get<string>(); 
        }else if(test.find("textfile") != test.end()){
            std::string textfilename = test["textfile"];
            ifstream textfile(textfilename);
            istreambuf_iterator<char> beg(textfile), end;
            text.assign(beg, end);
            textfile.close();
        }else if(test.find("fastafile") != test.end()){
            std::string textfilename = test["fastafile"];
            Pattern_fasta* genome = loadGeneFastaU((char*)textfilename.c_str());
            text.assign(genome->str);
            free(genome->str);
            if(genome->name) free(genome->name);
            free(genome);
        }

         u64 patId = 0;
         vector<map<string, int>> R;

         vector<string> patterns;
        if(test.find("patterns") != test.end()){
            patterns = test["patterns"].get<vector<string>>();
        }else if (test.find("fasta_patterns_file") != test.end()){
            std::string patfilename = test["patternsfile"];
            list<Pattern_fasta>* pattsList= new list<Pattern_fasta>;
            int ps=loadGenePatternFastaU((char*)patfilename.c_str(),  pattsList);
            for(list<Pattern_fasta>::iterator it=pattsList->begin(); it!=pattsList->end(); it++){
                patterns.push_back(string(it->str));
                if(it->name != nullptr) free(it->name);
                if(it->str != nullptr) free(it->str);
            }
            delete pattsList;
        }
        
         for(std::string pat: patterns){
             const char* p = strstr(text.c_str(), pat.c_str());
             while( p != NULL){
                 u64 idx = p - text.c_str();
                 map<string,int> m; m["pat"] = patId; m["pos"] =  idx + pat.size() -1 ;
                 R.push_back(m);
//                 R.push_back(( patId << 32) | idx);
                 p = strstr(p+1, pat.c_str());
             }
             patId++;
         }

         json oTest;
         test["Result"] = json(R);
         //out<<test.dump(4)<< ","<<endl;
         oTests.push_back(test);
    }

    out<<oTests.dump(4);
    out.close();

}
