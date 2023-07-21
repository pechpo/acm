//http://codeforces.com/problemset/problem/1648/B 调和级数+向后更新+差分
//根据执行到第i个数要不要加d[i]，差分有两种不同的写法，不要混淆。
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn=2e6+5;
int T;
int cnt[maxn], a[maxn], d[maxn];

int main(){
    scanf("%d", &T); int n=0, c=0;
    while (T--){
        for (int i=0; i<=2*c; ++i) d[i]=0;
        scanf("%d%d", &n, &c);
        for (int i=1; i<=n; ++i) scanf("%d", &a[i]);
        sort(a+1, a+n+1);
        int cnt=0; bool flag=true;
        n=unique(a+1, a+n+1)-(a+1);
        for (int i=1; i<=n; ++i){
            for (int j=1; j<=i&&a[j]<=c/a[i]; ++j){
                d[a[i]*a[j]]++;
                d[(a[i]+1)*a[j]]--;
                if (j!=i){
                    d[a[i]*a[j]]++;
                    d[a[i]*(a[j]+1)]--;
                }
            }
            for (int j=a[i-1]+1; j<=a[i]; ++j)
                cnt+=d[j];
            if (i!=cnt){
                flag=false;
                break;
            }
        }
        if (!flag){
            puts("No");
            continue;
        }
        puts("Yes");
    }
    return 0;
}