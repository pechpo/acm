#include <bits/stdc++.h>
#include "testlib.h"
 
using namespace std;
 
int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int T = inf.readInt(1, 10, "T");
    inf.readEoln();
    for (int test=0; test<T; ++test){
        string s = inf.readString();
        ensure(s.length() <= 100);
        int m = inf.readInt(1, 10, "m");
        inf.readEoln();
        for (int i=0; i<m; ++i){
            char ch = inf.readChar();
            inf.readSpace();
            int x = inf.readInt(0, 3);
            inf.readEoln();
        }
        int q = inf.readInt(1, 100, "q");
        inf.readEoln();
        for (int i=0; i<q; ++i){
            string s = inf.readToken();
            inf.readSpace();
            ensure(s.length() <= 100);
            char ch = inf.readChar();
            inf.readEoln();
        }
    }
 
    inf.readEof();
}