struct Edge{
    int v, id, a, b;
};
vector<Edge> E[maxn], E_rev[maxn];
//用vector存邻接表 灵活,虽然慢了点
//E[i]表示结点i所连的结点

const Maxn=10, Maxm=10;
int fir[Maxn];  //内部指标是边编号
int nxt[Maxm], a[Maxm], to[Maxm];
int cnte;
void addedge2(int u, int v, int _a){
    //printf("%d %d %d\n", u, v, _a);
    ++cnte;
    nxt[cnte]=fir[u]; fir[u]=cnte;
    a[cnte]=_a; to[cnte]=v;
}
//用链表存邻接表 快一些