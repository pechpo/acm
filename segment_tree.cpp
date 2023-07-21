#include <cstdio>
using namespace std;

const int maxn=4e5+5;
int n, m;
int seg[maxn], tag[maxn];

void pushdown(int id, int mul){
    if (mul>1){
        tag[id<<1]+=tag[id];
        tag[id<<1^1]+=tag[id];
    }
    seg[id]+=tag[id]*mul;
    tag[id]=0;
}

void modify(int id, int l, int r, int L, int R, int k){
    if (l>r) return;
    pushdown(id, r-l+1);
    if (l>R||r<L) return;
    if (l>=L&&r<=R){
        tag[id]+=k;
        pushdown(id, r-l+1);
        return;
    }
    int mid=l+r>>1;
    modify(id<<1, l, mid, L, R, k);
    modify(id<<1^1, mid+1, r, L, R, k);
    seg[id]=seg[id<<1]+seg[id<<1^1];  
    //上面这行调用了id*2+0/1结点的seg值，所以要注意更新这个值，
    //即便那个结点对应的区间已经脱离查询区间，也有可能有标记
}

int query(int id, int l, int r, int L, int R){
    if (l>r) return 0;
    if (l>R||r<L) return 0;
    pushdown(id, r-l+1);
    if (l>=L&&r<=R) return seg[id];
    int mid=l+r>>1;
    return query(id<<1, l, mid, L, R)
        +query(id<<1^1, mid+1, r, L, R);
}

int main(){
    scanf("%d%d", &n, &m);
    int tmp;
    for (int i=1; i<=n; ++i){
        scanf("%d", &tmp);
        modify(1, 1, n, i, i, tmp);
    }
    int op, x, y, k;
    for (int i=1; i<=m; ++i){
        scanf("%d%d%d", &op, &x, &y);
        if (op==1){
            scanf("%d", &k);
            modify(1, 1, n, x, y, k);
        } else printf("%d\n", query(1, 1, n, x, y));
    }
    return 0;
}