#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

const int maxm=105, maxk=205;
int T, n, m, k;
int fir[maxm], nxt[maxk], to[maxk], cnte, a[maxm], cnt[maxm][243], cnt2[maxm][729];

void addedge(int x, int y){
    nxt[++cnte]=fir[x]; fir[x]=cnte;
    to[cnte]=y;
}

int main(){
    scanf("%d", &T);
    while (T--){
        scanf("%d%d%d", &n, &m, &k);
        int x, y; cnte=0;
        memset(fir, 0, sizeof(fir));
        for (int i=1; i<=k; ++i){
            scanf("%d%d", &x, &y);
            addedge(y, x);  //反向建特征的关系图
        }
        memset(cnt, 0, sizeof(cnt));
        memset(cnt2, 0, sizeof(cnt2));
        for (int i=0; i<n; ++i){
            for (int j=1; j<=m; ++j)
                scanf("%d", &a[j]);  //读取这组特征
            for (int j=1; j<=m; ++j){
                int id=0;
                for (int t=fir[j]; t; t=nxt[t])
                    id=id*3+a[to[t]];  //算相关特征取值id
                cnt[j][id]++;
                id=id*3+a[j];  //包含自身特征取值的id
                cnt2[j][id]++;
            }
        }
        for (int j=1; j<m; ++j)
            scanf("%d", &a[j]);
        double p, ans=-1e9; int best=0;
        for (int i=0; i<3; ++i){
            p=0;
            a[m]=i;
            int id=0;
            for (int j=1; j<=m; ++j){
                id=0;
                for (int t=fir[j]; t; t=nxt[t])
                    id=id*3+a[to[t]];  //算相关特征取值id
                //printf("%d\n", cnt[j][id]);
                p-=log(cnt[j][id]);
                id=id*3+a[j];
                p+=log(cnt2[j][id]);
                //printf("%d %d %d %d\n", i, j, id, cnt2[j][id]);
            }
            //printf("%d %lf\n", i, p);
            if (p>ans) ans=p, best=i;
        }
        printf("%d\n", best);
    }
    return 0;
}