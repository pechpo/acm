#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

const int maxn=16;
int n, p[20];  //线性基第i位的数
pair<int, int> a[1<<maxn];

bool lins(int x){
    bool flag=false;
    for (int i=n; ~i; --i){
        if (!(x>>i&1)) continue;
        if (!p[i]){
            p[i]=x;
            flag=true;
        }
        x^=p[i];
    }
    return flag;
}

int main(){
    scanf("%d", &n);
    for (int i=0; i<(1<<n)-1; ++i){
        scanf("%d", &a[i].first);
        a[i].second=i+1;
    }
    sort(a, a+(1<<n)-1); int cnt=0;
    long long ans=0;
    for (int i=0; i<(1<<n)-1; ++i){
        if (!lins(a[i].second)) continue;
        ans+=a[i].first; ++cnt;
        if (cnt==n) break;
    }
    printf("%lld\n", ans);
    return 0;
}
