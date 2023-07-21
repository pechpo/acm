#include <cstdio>
#include <cstring>
using namespace std;

typedef long long LL;
const LL maxn=4e5+5;
LL n, m, p;
LL seg[maxn], tag1[maxn], tag2[maxn]; //tag1乘 tag2加

void pushdown(LL id, LL mul){
    if (mul>1){
        tag1[id<<1]*=tag1[id]; tag1[id<<1]%=p;
        tag1[id<<1^1]*=tag1[id]; tag1[id<<1^1]%=p;
        tag2[id<<1]=(tag2[id<<1]*tag1[id]+tag2[id])%p;
        tag2[id<<1^1]=(tag2[id<<1^1]*tag1[id]+tag2[id])%p;
    }
    seg[id]=(seg[id]*tag1[id]+tag2[id]*mul)%p;
    tag1[id]=1; tag2[id]=0;
}

void modify(LL op, LL id, LL l, LL r, LL L, LL R, LL k){
    if (l>r) return;
    pushdown(id, r-l+1);
    if (l>R||r<L) return;
    if (l>=L&&r<=R){
        if (op==1) tag1[id]=k;
        else tag2[id]=k;
        pushdown(id, r-l+1);
        return;
    }
    LL mid=l+r>>1;
    modify(op, id<<1, l, mid, L, R, k);
    modify(op, id<<1^1, mid+1, r, L, R, k);
    seg[id]=(seg[id<<1]+seg[id<<1^1])%p;
}

LL query(LL id, LL l, LL r, LL L, LL R){
    if (l>r) return 0;
    if (l>R||r<L) return 0;
    pushdown(id, r-l+1);
    if (l>=L&&r<=R) return seg[id];
    LL mid=l+r>>1;
    return (query(id<<1, l, mid, L, R)
        +query(id<<1^1, mid+1, r, L, R))%p;
}

int main(){
    scanf("%lld%lld%lld", &n, &m, &p);
    for (int i=1; i<=4*n; ++i) tag1[i]=1;
    LL tmp;
    for (LL i=1; i<=n; ++i){
        scanf("%lld", &tmp);
        modify(2, 1, 1, n, i, i, tmp);
    }
    LL op, x, y, k;
    for (LL i=1; i<=m; ++i){
        scanf("%lld%lld%lld", &op, &x, &y);
        if (op<=2){
            scanf("%lld", &k);
            modify(op, 1, 1, n, x, y, k);
        } else printf("%lld\n", query(1, 1, n, x, y));
    }
    return 0;
}