#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn=2e4+5;
int n, m, dfn[maxn], low[maxn], time;
vector<int> e[maxn];
int cut[maxn], cnt;

void dfs(int u, int p){  //dfs求割点
    low[u]=dfn[u]=++time;
    int newv=0;
    for (auto v:e[u]){
        if (!dfn[v]){
            ++newv;
            dfs(v, u);
            low[u]=min(low[u], low[v]);
            if (low[v]>=dfn[u]&&p) cut[u]=1;
            continue;
        }
        if (v!=p) low[u]=min(low[u], dfn[v]);
    }
    if (!p&&newv>1) cut[u]=1;
}

int main(){
    scanf("%d%d", &n, &m);
    int x, y;
    for (int i=1; i<=m; ++i){
        scanf("%d%d", &x, &y);
        e[x].push_back(y);
        e[y].push_back(x);
    }
    for (int i=1; i<=n; ++i){
        if (dfn[i]) continue;
        dfs(i, 0);
    }
    for (int i=1; i<=n; ++i)
        if (cut[i]) ++cnt;
    printf("%d\n", cnt);
    for (int i=1; i<=n; ++i)
        if (cut[i]) printf("%d ", i);
    return 0;
}