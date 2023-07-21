#include <cstdio>
#include <vector>
using namespace std;

const int maxn=1e5+5;
int n, rt=1, first[maxn];
vector<int> e[maxn], c[maxn];
int vis[maxn], dep[maxn], m;

int Log[maxn*2], st[maxn*2][20];
void init(){
    for (int i=2; i<maxn*2; ++i)
        Log[i]=Log[i/2]+1;
}

void dfs(int u){
    vis[u]=1;
    st[++m][0]=u;  //euler sequence
    first[u]=m;
    for (auto v:e[u]){
        if (vis[v]) continue;
        c[u].push_back(v);
        dep[v]=dep[u]+1; dfs(v);
        st[++m][0]=u;
    }
}

int main(){
    init();
    scanf("%d", &n);
    int a, b, u1, u2;
    for (int i=1; i<n; ++i){
        scanf("%d%d", &a, &b);
        e[a].push_back(b); e[b].push_back(a);
    }
    dfs(rt);
    for (int j=1; j<20; ++j)
        for (int i=1; i<2*n-(1<<j)+1; ++i){
            u1=st[i][j-1]; u2=st[i+(1<<j-1)][j-1];
            st[i][j]=(dep[u1]<dep[u2]?u1:u2);
        }
    int T, lca, g; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &a, &b);
        if (first[a]>first[b]) swap(a, b);
        g=Log[first[b]-first[a]+1];
        u1=st[first[a]][g], u2=st[first[b]-(1<<g)+1][g];
        lca=(dep[u1]<dep[u2]?u1:u2);
        printf("%d\n", dep[a]+dep[b]-2*dep[lca]);
    }
    return 0;
}