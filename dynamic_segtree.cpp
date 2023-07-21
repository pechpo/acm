#include <cstdio>
#include <vector>
using namespace std;

const int maxn=4e5+5;
struct Node{
    int lc, rc, v;
}seg[maxn];
int root[maxn], cntn;

void update(int x){
    seg[x].v=0;
    if (seg[x].lc) seg[x].v+=seg[seg[x].lc].v;
    if (seg[x].rc) seg[x].v+=seg[seg[x].rc].v;
}

void insert(int &x, int l, int r, int p){  //x表示点的编号,seg[x]才是点
    seg[++cntn]=seg[x]; x=cntn;  //传旧点编号，建新点
    if (l==r){
        seg[x].v++;
        return;
    }
    int mid=l+r>>1;
    if (p<=mid) insert(seg[x].lc, l, mid, p);
    else insert(seg[x].rc, mid+1, r, p);
    update(x);
}

int query(int x, int l, int r, int L, int R){
    if (l>=L&&r<=R) return seg[x].v;
    int mid=l+r>>1, ans=0;
    if (mid>=L) ans+=query(seg[x].lc, l, mid, L, R);
    if (mid<R) ans+=query(seg[x].rc, mid+1, r, L, R);
    return ans;
}

int n;
inline int get_time(){
    int h, m, s;
    scanf("%d%d%d", &h, &m, &s);
    return h*3600+m*60+s+1;
}
vector<int> pre[maxn];

int main(){
    scanf("%d", &n); int t1, t2, t3, t4;
    for (int i=0; i<n; ++i){
        t1=get_time(), t2=get_time();
        pre[t2].push_back(t1);
    }
    int N=86400, q;
    for (int i=1; i<=86400; ++i){
        root[i]=root[i-1];  //这一步不写相当于继承0号点数据
        for (auto j:pre[i]) insert(root[i], 1, N, j);
    }
    scanf("%d", &q); int ans;
    for (int i=0; i<q; ++i){
        t1=get_time(), t2=get_time();
        t3=get_time(), t4=get_time();
        ans=query(root[t4], 1, N, t1, t2);
        ans-=query(root[t3-1], 1, N, t1, t2);
        printf("%d\n", ans);
    }
    return 0;
}