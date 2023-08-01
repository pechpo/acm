#include <cstdio>
#include <cstring>
using namespace std;

const int maxn=1e5+5;
int T, n, a[maxn], f[maxn][3][3];
char s[maxn];

int main(){
    scanf("%d", &T);
    while (T--){
        scanf("%s", s);
        n=strlen(s);
        for (int i=0; i<n; ++i){
            if (s[i]=='G') a[i]=1;
            if (s[i]=='B') a[i]=2;
        }
        for (int i=0; i<3; ++i)
            for (int j=0; j<3; ++j)
                f[1][i][j]=-1e9;
        f[1][a[0]][a[1]]=0;  //分数
        
    }
}