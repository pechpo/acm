#include<cstdio>
using namespace std;

const int mod = 9901, maxn=205;
int f[maxn][maxn], F[maxn][maxn];
int n, k;

int main()
{
    scanf("%d%d", &n, &k);
    f[1][1] = F[1][1] = 1;
    for (int j = 2; j <= k; j++)
        F[1][j] = 1;
    for (int i = 3; i <= n; i++){
        for (int j = 2; j <= k; j++){
            for (int k = 1; k < i; k++){
                f[i][j] += f[k][j-1] * F[i-k-1][j-2]*2;
                f[i][j] += f[k][j-1] * f[i-k-1][j-1];
                f[i][j]%=mod;
            }
            F[i][j] = (F[i][j-1] + f[i][j]) % mod;
        }
    }
    printf("%d\n", f[n][k]);
    return 0;
}