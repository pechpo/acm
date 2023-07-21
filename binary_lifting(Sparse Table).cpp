#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn=1005;
int T;
int n, st[maxn][11], Log[maxn], q;

int main(){
    for (int i=2; i<maxn; ++i) Log[i]=Log[i/2]+1;
    scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        for (int i=1; i<=n; ++i) scanf("%d", &st[i][0]);
        for (int j=1; j<11; ++j)
            for (int i=1; i<=n-(1<<j)+1; ++i)
                st[i][j]=max(st[i][j-1], st[i+(1<<j-1)][j-1]);
        scanf("%d", &q); int l, r, g, ans=0;
        for (int i=0; i<q; ++i){
            scanf("%d%d", &l, &r); g=Log[r-l+1];
            ans=max(st[l][g], st[r-(1<<g)+1][g]);  //O(1)
            printf("%d\n", ans);
        }
    }
    return 0;
}