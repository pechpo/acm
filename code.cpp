#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn=1e5+5;
int n, vis[maxn];
struct mypair{
    double t;
    int from, to;
};
struct mycmp{
    bool operator()(const mypair &a, const mypair &b){
        return a.t>b.t;
    }
};
priority_queue<mypair, vector<mypair>, mycmp> q;
struct point{
    int v, p;
}P[maxn];
bool cmp(const point &a, const point &b){
    return a.p<b.p||a.p==b.p&&a.v>b.v;
}
struct node{
    int nxt, pre;
}a[maxn];

int main(){
    scanf("%d", &n);
    for (int i=1; i<=n; ++i)
        scanf("%d%d", &P[i].p, &P[i].v);
    sort(P+1, P+n+1, cmp);
    a[0].nxt=1; a[1].pre=0;
    a[n].nxt=n+1; a[n+1].pre=n;
    for (int i=1; i<n; ++i){
        a[i].nxt=i+1;
        a[i+1].pre=i;
        if (P[i].p==P[i+1].p&&P[i].v==P[i+1].v) q.push((mypair){0, i, i+1});
        if (P[i].v<=P[i+1].v) continue;
        q.push((mypair){1.0*(P[i+1].p-P[i].p)/(P[i].v-P[i+1].v), i, i+1});
    }
    while (!q.empty()){
        while (!q.empty()&&vis[q.top().to]) q.pop();  //不能追及已经消失的点
        if (q.empty()) break;
        double t=q.top().t;
        int id=q.top().from;
        q.pop();
        vis[id]=1;
        int pre=a[id].pre, nxt=a[id].nxt;
        a[pre].nxt=nxt; a[nxt].pre=pre;
        if (P[pre].p==P[nxt].p&&P[pre].v==P[nxt].v) q.push((mypair){0, pre, nxt});
        if (P[pre].v<=P[nxt].v) continue;
        q.push((mypair){1.0*(P[nxt].p-P[pre].p)/(P[nxt].v-P[pre].v), pre, nxt});
    }
    int cnt=0, ans=0;
    for (int i=1; i<=n; ++i){
        if (vis[i]!=0) cnt++;
        else ans=max(ans, cnt), cnt=0;
    }
    printf("%d\n", ans+1);
    return 0;
}