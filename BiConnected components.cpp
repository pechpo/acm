#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn=5e5+5;
int n, m, dfn[maxn], low[maxn], time;
vector<int> e[maxn];
int stack[maxn], len;
vector<vector<int>> bcc_arr;

void dfs(int u, int p){  //dfs求双连通分量
    low[u]=dfn[u]=++time;
    stack[len++]=u;
    int newv=0;
    for (auto v:e[u]){
        if (!dfn[v]){
            ++newv;
            dfs(v, u);
            low[u]=min(low[u], low[v]);
            if (low[v]>=dfn[u]){  //当前点是割点/树根，则结算前方双连通分量
                bcc_arr.push_back(vector<int>());
                while (stack[len]!=v)  //注意以v而非u为界限
                    bcc_arr.back().push_back(stack[--len]);
                bcc_arr.back().push_back(u);
            }
            continue;
        }
        if (v!=p) low[u]=min(low[u], dfn[v]);
    }
    if (!p&&!newv) bcc_arr.push_back(vector<int>{stack[--len]});
    else if (!p) --len;  //考虑树根，无孩子的情况特判一下，并回收栈中数据
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
    printf("%d\n", bcc_arr.size());
    for (auto bcc:bcc_arr){
        printf("%d ", bcc.size());
        for (auto x:bcc)
            printf("%d ", x);
        puts("");
    }
    return 0;
}