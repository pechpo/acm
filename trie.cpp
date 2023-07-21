#include <cstdio>
#include <cstring>
using namespace std;

const int maxn=1e4+5, maxl=55;
char s[maxl];  //其实不用存这个点的对应字符，跳过来或者查询字符串都可获得
int rt=0, n, m, c[maxn*maxl][26], cnt;
int tot[maxn*maxl];

void insert(char *s){
    int n=strlen(s);
    int p=rt, x;
    for (int i=0; i<n; ++i){
        x=s[i]-'a';
        if (!c[p][x]) c[p][x]=++cnt;
        p=c[p][x];
    }
}

int find(char *s){
    int n=strlen(s);
    int p=rt, x;
    for (int i=0; i<n; ++i){
        x=s[i]-'a';
        if (!c[p][x]) return -1;
        p=c[p][x];
    }
    if (tot[p]++) return 1;
    else return 0;
}

int main(){
    scanf("%d", &n);
    for (int i=0; i<n; ++i){
        scanf("%s", s);
        insert(s);
    }
    scanf("%d", &m); int sig;
    for (int i=0; i<m; ++i){
        scanf("%s", s);
        sig=find(s);
        if (sig==-1) puts("WRONG");
        if (sig==0) puts("OK");
        if (sig==1) puts("REPEAT");
    }
    return 0;
}