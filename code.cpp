#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const double eps=1e-9;
const int maxn=5, maxm=5;
int T;
double a[maxn][maxm], b[maxm];

inline bool nzero(double x){ return abs(x)>eps; }

void print_matrix(double (*a)[maxm], int n, int m){
    for (int i=0; i<n; ++i){
        for (int j=0; j<m; ++j)
            printf("%lf ", a[i][j]);
        puts("");
    }
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
    scanf("%d", &T);
    while (T--){
        for (int i=0; i<4; ++i)
            for (int j=0; j<3; ++j)
                scanf("%lf", &a[j][i]);
        for (int i=0; i<4; ++i) b[i]=0;
        int res=gauss(a, 3, 4, b);
        if (res<0) puts("NO");
        if (res==0){
            bool flag=true;
            for (int i=0; i<3; ++i)
                if (b[i]<-eps) flag=false;
            puts(flag?"YES":"NO");
        }
        if (res==1){
            if (nzero(a[0][0])){
                double A=a[0][3]/a[0][2], B=a[1][3]/a[1][2];
                if (a[1][2]>0){
                    double t=min(A, B);
                    puts(t<-eps?"NO":"YES");
                } else {
                    if (A<B) puts("NO");
                    else if (A<0) puts("NO");
                    else puts("YES");
                }
            } else {
                double t=min(a[0][3]/a[0][1], a[1][3]/a[1][2]);
                puts(t<-eps?"NO":"YES");
            }
        }
        if (res>=2) puts("YES");
    }
    return 0;
}