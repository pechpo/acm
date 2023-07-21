#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn=5e5+5, maxm=2e6+5;
int n, m;
int cnte=1, fir[maxn];
struct Edge{  //因为要访问反向边，只能用传统方法
    int to, nxt;
}e[maxm*2];
void addEdge(int x, int y){
    e[++cnte]=(Edge){y, fir[x]};
    fir[x]=cnte;
}

int dfn[maxn], low[maxn], time;
int stack[maxn], len;
vector<vector<int>> bcc_arr;
void dfs(int u, int in_eid){
    dfn[u]=low[u]=++time;
    stack[len++]=u;
    int v;
    for (int eid=fir[u]; eid; eid=e[eid].nxt){
        v=e[eid].to;
        if (!dfn[v]){
            dfs(v, eid);
            low[u]=min(low[u], low[v]);
            continue;
        }
        if (eid!=(in_eid^1))
            low[u]=min(low[u], dfn[v]);
    }
    if (dfn[u]==low[u]){
        bcc_arr.push_back(vector<int>());
        while (stack[len]!=u)
            bcc_arr.back().push_back(stack[--len]);
    }
}

int main(){
    scanf("%d%d", &n, &m);
    int x, y;
    for (int i=0; i<m; ++i){
        scanf("%d%d", &x, &y);
        addEdge(x, y);
        addEdge(y, x);
    }
    for (int i=1; i<=n; ++i)
        if (!dfn[i]) dfs(i, 0);
    printf("%d\n", bcc_arr.size());
    for (auto &bcc:bcc_arr){
        printf("%d ", bcc.size());
        for (auto x:bcc)
            printf("%d ", x);
        puts("");
    }
    return 0;
}