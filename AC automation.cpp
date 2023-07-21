#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int maxn=2e5+5, maxl=2e6+5;
int rt=0, n, c[maxn][26], fail[maxn], cnt;
char *s[maxn], S[maxl];
int appear[maxn];
vector<int> str[maxn];  //结点对应的接受子串

void insert(char *s, int i){
    int n=strlen(s), p=rt;
    for (int i=0; i<n; ++i){
        int x=s[i]-'a';
        if (!c[p][x]) c[p][x]=++cnt;
        p=c[p][x];
    }
    str[p].push_back(i);
}

void build(){
    queue<int> q;
    q.push(rt);
    while (!q.empty()){
        int u=q.front(); q.pop();
        for (int i=0; i<26; ++i)
            if (c[u][i]){  //fail边
                fail[c[u][i]]=(u==rt?rt:c[fail[u]][i]);
                q.push(c[u][i]);
            } else c[u][i]=c[fail[u]][i];  //trie图边
    }
}

void deal(char *s){
    int n=strlen(s), p=rt;
    for (int i=0; i<n; ++i){
        int x=s[i]-'a';
        int q=p=c[p][x];
        while (q){
            for (auto i:str[q]) appear[i]++;
            q=fail[q];
        }
    }
}

void init(){
    cnt=0;
    memset(c, 0, sizeof(c));
    memset(fail, 0, sizeof(fail));
    memset(appear, 0, sizeof(appear));
    for (int i=0; i<maxn; ++i) str[i].swap({});
}

int main(){
    scanf("%d", &n);
    for (int i=0; i<n; ++i){
        scanf("%s", S);
        s[i]=(char*)malloc(strlen(S)+1);
        strcpy(s[i], S);
        insert(s[i], i);
    }
    scanf("%s", S);
    build();
    deal(S);
    for (int i=0; i<n; ++i)
        printf("%d\n", appear[i]);
    return 0;
}