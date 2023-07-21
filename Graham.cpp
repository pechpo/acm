#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn=1e5+5;
int n, id;
struct Vector{ double x, y; };
struct Point{
    double x, y;
    Vector v;
}p[maxn], O;
Vector operator-(const Point &p1, const Point &p2){
    Vector tmp=(Vector){p1.x-p2.x, p1.y-p2.y};
    return tmp;
}
double operator*(const Vector &v1, const Vector &v2){
    return v1.x*v2.y-v2.x*v1.y;
}
double sqr(double x){ return x*x; }
double dis(const Point &p1, const Point &p2){
    return sqrt(sqr(p1.x-p2.x)+sqr(p1.y-p2.y));
}
bool cmp(const Point &p1, const Point &p2){
    double dot=p1.v*p2.v;
    if (dot>0) return true;
    if (dot==0) return dis(p1, O)<dis(p2, O);  //全共线情况
    return false;
}

int s[maxn], cnt; //栈。从零开始存，存点的编号

int main(){
    scanf("%d", &n); id=1;
    for (int i=1; i<=n; ++i){
        scanf("%lf%lf", &p[i].x, &p[i].y);
        if (p[i].y<p[id].y||p[i].y==p[id].y&&p[i].x<p[id].x)
            id=i;
    }
    for (int i=1; i<=n; ++i) p[i].v=p[i]-p[id];
    O=p[id];
    sort(p+1, p+n+1, cmp); int id1, id2;
    for (int i=1; i<=n; ++i){
        while (cnt>=2){
            id1=s[cnt-1]; id2=s[cnt-2];
            if ((p[id1]-p[id2])*(p[i]-p[id1])>0) break;
            --cnt;
        }
        s[cnt++]=i;
    }
    int previd=cnt-1; double ans=0;
    for (int i=0; i<cnt; ++i){
        ans+=dis(p[s[previd]], p[s[i]]);
        previd=i;
    }
    printf("%.2lf", ans);
    return 0;
}