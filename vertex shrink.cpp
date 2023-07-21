#include <queue>
#include <cstdio>
#include <vector>
using namespace std;

const int maxn=1e4+5;
int n, m, w[maxn], dfn[maxn], low[maxn], time;
vector<int> e[maxn];
int stack[maxn], stack_l, in_stack[maxn];

int scc_id[maxn], scc_cnt;
int w2[maxn], indeg[maxn];
vector<int> e2[maxn];
queue<int> q;
int f[maxn];

void dfs(int u){  //dfs求强连通分量
    low[u]=dfn[u]=++time;
    in_stack[u]=1;
    stack[stack_l++]=u;
    for (auto v:e[u]){
        if (!dfn[v]){
            dfs(v);
            low[u]=min(low[u], low[v]);
            continue;
        }
        if (in_stack[v])
            low[u]=min(low[u], dfn[v]);
    }
    if (dfn[u]==low[u]){
        ++scc_cnt;
        int v;
        while (true){
            v=stack[--stack_l];
            in_stack[v]=0;
            w2[scc_cnt]+=w[v];
            scc_id[v]=scc_cnt;
            if (v==u) break;
        }
    }
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i=1; i<=n; ++i)
        scanf("%d", &w[i]);
    int x, y;
    for (int i=1; i<=m; ++i){
        scanf("%d%d", &x, &y);
        e[x].push_back(y);
    }
    for (int i=1; i<=n; ++i){
        if (dfn[i]) continue;
        dfs(i);
    }
    for (int u=1; u<=n; ++u)  //建缩点图
        for (auto v:e[u])
        if (scc_id[u]!=scc_id[v]){
            e2[scc_id[u]].push_back(scc_id[v]);
            indeg[scc_id[v]]++;
        }
    for (int i=1; i<=scc_cnt; ++i)  //拓扑排序
        if (!indeg[i]) q.push(i);
    int u, ans=0;
    while (!q.empty()){  //DAG上DP
        u=q.front();
        q.pop();
        f[u]+=w2[u];
        ans=max(ans, f[u]);
        for (auto v:e2[u]){
            f[v]=max(f[v], f[u]);
            --indeg[v];
            if (!indeg[v]) q.push(v);
        }
    }
    printf("%d\n", ans);
    return 0;
}