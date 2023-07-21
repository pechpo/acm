#include <cstdio>
#include <cstring>
using namespace std;

const int maxn=1e6+5;
char s1[maxn], s2[maxn];
int n, m, next[maxn];

int main(){
    scanf("%s%s", s1, s2);
    n=strlen(s1), m=strlen(s2);
    next[0]=-1; int j=-1;
    for (int i=1; i<m; ++i){
        while (~j&&s2[i]!=s2[j+1]) j=next[j];
        if (s2[i]==s2[j+1]) ++j;
        next[i]=j;
    } j=-1;
    for (int i=0; i<n; ++i){
        while (~j&&s1[i]!=s2[j+1]) j=next[j];
        if (s1[i]==s2[j+1]) ++j;
        if (j==m-1) printf("%d\n", i-j+1);
    }
    for (int i=0; i<m; ++i) printf("%d ", next[i]+1);
    return 0;
}