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
using namespace std;
using json = nlohmann::json;

using namespace std;

int main0(int argc, char** argv)
{
    char* fin, *fout;
    if(argc == 1){
        fin = (char*)"strstrtest.testcases.raw";
        fout = (char*)"strstrtest.testcases";
    }else{
        fin = argv[1];
        fout = argv[2];
    }
    char* buf = new char[1024 * 10];
    ifstream in(fin);
    FILE* out = fopen(fout, "a");
    while(!in.eof()){
        in.getline(buf, 1024*10);

        char* pSep = strstr(buf, "\"^^\"");
        if(pSep == NULL){
            continue;
        }

        pSep[0] = '\0';
        char* text = buf;
        char* pat = (pSep + 4); 
        if(pat[strlen(pat)-1] == '\n')
            pat[strlen(pat)-1] = '\0';
        fprintf(out, "{\"%s\", \"%s\", {", text, pat);
        char* p = strstr(text, pat);
        while( p != NULL){
            int idx = p - buf;
            fprintf(out, "%d ", idx);
            p = strstr(p+1, pat);
        }
        fprintf(out, "}},\n");

    }

    fclose(out);
    delete[] buf;
}

int main(int argc, char** argv)
{
    char* fin, *fout;
    if(argc == 1){
        fin = (char*)"strstrtest.testcases.raw";
        fout = (char*)"strstrtest.testcases";
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
        }
        std::string pat =  test["pattern"];
        const char* p = strstr(text.c_str(), pat.c_str());
        vector< int> R;
        while( p != NULL){
            int idx = p - text.c_str();
            R.push_back(idx);
            p = strstr(p+1, pat.c_str());
        }
        test["Result"] = json(R);
        oTests.push_back(test);
    }
    out<<oTests.dump(4);
    out.close();
}
