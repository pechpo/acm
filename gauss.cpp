#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const double eps=1e-9;
const int maxn=105, maxm=105;
int T, n, m;
double a[maxn][maxm], b[maxm];

inline bool nzero(double x){ return abs(x)>eps; }

void print_matrix(double (*a)[maxm], int n, int m){
    for (int i=0; i<n; ++i){
        for (int j=0; j<m; ++j)
            printf("%lf ", a[i][j]);
        puts("");
    }
    puts("");
}

int gauss(double (*a)[maxm], int n, int m, double *b){  //高斯消元，m的最后一列是b
    int cnt=0;  //第一个未处理的行
    for (int i=0; i<m-1; ++i){  //第一个未处理的列
        int pos=-1;
        for (int j=cnt; j<n; ++j)
            if (pos==-1&&nzero(a[j][i])) pos=j;
        if (pos==-1) continue;  //寻找非零行
        for (int j=0; j<m; ++j)
            swap(a[cnt][j], a[pos][j]);
        for (int j=cnt+1; j<n; ++j){  //此行减去第cnt行
            double coef=a[j][i]/a[cnt][i];
            for (int k=0; k<m; ++k)
                a[j][k]-=coef*a[cnt][k];
        }
        //print_matrix(a, n, m);
        cnt++;
    }
    cnt=0;  //非零行数目
    for (int i=0; i<n; ++i){
        bool flag=false;
        for (int j=0; j<m-1; ++j)
            if (nzero(a[i][j])) flag=true;
        if (!flag&&nzero(a[i][m-1])) return -1;  //无解
        cnt+=flag;
    }
    for (int i=n-1; i>=0; --i){  //反向求解
        int pos=-1;
        for (int j=0; j<m-1; ++j)
            if (pos==-1&&nzero(a[i][j])) pos=j;
        if (pos==-1) continue;  //寻找非零行
        double coef=a[i][pos];
        for (int j=0; j<m; ++j) a[i][j]/=coef;  //把首个系数化成1
        for (int j=0; j<i; ++j){
            coef=a[j][pos];
            for (int k=0; k<m; ++k)
                a[j][k]-=coef*a[i][k];
        }
        b[pos]=a[i][m-1];
        //print_matrix(a, n, m);
    }
    return n-cnt;  //零行数目，即自由元数目
}

int main(){
    scanf("%d", &n);
    for (int i=0; i<n; ++i)
        for (int j=0; j<n+1; ++j)
            scanf("%lf", &a[i][j]);
    int res=gauss(a, n, n+1, b);
    if (res>0){
        puts("0");
        return 0;
    }
    if (res<0){
        puts("-1");
        return 0;
    }
    for (int i=0; i<n; ++i)
        printf("x%d=%.2lf\n", i+1, b[i]);
    return 0;
}