#include <cstdio>
#include <queue>
#include <vector>
#include <utility>
using namespace std;

typedef long long LL;
const LL maxn=1e4+5, INF=1e18;
LL n, m, k, key[17], dis[maxn], d[17][17], vis[maxn];
vector<pair<LL,LL>> e[maxn];
LL f[17][1<<17];

priority_queue<pair<LL,LL>> q;
void dijkstra(LL s){
    for (LL i=1; i<=n; ++i) dis[i]=INF, vis[i]=0;
    while (!q.empty()) q.pop();
    dis[s]=0;
    q.push({0, s}); LL u, v, w;
    for (LL i=1; i<=n; ++i){
        while (!q.empty()&&vis[q.top().second]) q.pop();
        if (q.empty()) break;
        u=q.top().second; vis[u]=1;
        for (auto j:e[u]){
            v=j.first; w=j.second;
            if (dis[u]+w<dis[v]){
                dis[v]=dis[u]+w;
                q.push({-dis[v], v});
            }
        }
    }
}

int main(){
    scanf("%lld%lld%lld", &n, &m, &k);
    for (LL i=0; i<=k; ++i) scanf("%lld", &key[i]);
    LL u, v, w;
    for (LL i=0; i<m; ++i){
        scanf("%lld%lld%lld", &u, &v, &w);
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    }
    for (LL i=0; i<=k; ++i){
        dijkstra(key[i]);
        for (LL j=0; j<=k; ++j)
            d[i][j]=dis[key[j]];
    }
    for (LL i=0; i<17; ++i)
        for (LL j=0; j<(1<<17); ++j)
            f[i][j]=INF;
    f[0][1]=0;
    for (LL S=2; S<(1<<(k+1)); ++S){
        for (LL i=1; i<=k; ++i){
            LL S1=S^(1<<i);
            for (LL j=0; j<=k; ++j)
                f[i][S]=min(f[i][S], f[j][S1]+d[i][j]);
        }
    }
    LL ans=INF;
    for (LL i=1; i<=k; ++i)
        ans=min(ans, f[i][(1<<(k+1))-1]+d[i][0]);
    if (ans>=INF) puts("-1");
    else printf("%lld\n", ans);
    return 0;
}