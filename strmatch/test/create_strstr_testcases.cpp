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

using namespace std;

int main(int argc, char** argv)
{
    char* fin, *fout;
    if(argc == 1){
        fin = "strstrtest.testcases.raw";
        fout = "strstrtest.testcases";
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

        pSep[0] = NULL;
        char* text = buf;
        char* pat = (pSep + 4); 
        pat[strlen(pat)-1] = NULL;
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

