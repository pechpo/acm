#include <cctype>
#include <cstdio>

void get(int &x){
    char ch;
    for (; !isdigit(ch=getchar()); );
    for (x=ch-'0'; isdigit(ch=getchar()); x=x*10+ch-'0');
}