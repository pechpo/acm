#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define double long double
//acosl返回0~pi，asinl返回-pi/2~pi/2。精度不好所以慎用
namespace geo_2d{
const double eps=1e-9, INF=1e9, PI=3.14159265358979323846;
struct V{  //向量及其运算是几何基础，点也可以用向量表示
    double x, y;
    V():x(0),y(0){}
    V(const V &a){ *this=a; }
    V(const double &a, const double &b):x(a),y(b){}
    void read(){ scanf("%Lf%Lf", &x, &y); }
    void print(){ printf("%.9Lf %.9Lf\n", x, y); }  //位数多精度高
    void print_space(){ printf("%.9Lf %.9Lf ", x, y); }
    void print_int(){ printf("%d %d\n", (int)x, (int)y); }
}O;  //三个vector参数abc表示以a为顶点的角bac/cab
inline double sqr(const double &x){ return x*x; }
inline bool zero(const double &x){ return abs(x)<eps; }
inline bool equal(const double &a, const double &b){ return zero(a-b); }
inline bool less(const double &a, const double &b){ return a<b-eps; }
inline bool greater(const double &a, const double &b){ return a>b+eps; }
inline bool cmp1(const V &a, const V &b){ return a.x<b.x; }
inline bool cmp2(const V &a, const V &b){ return a.y<b.y; }
inline bool cmp3(const V &a, const V &b){ return cmp1(a, b)||equal(a.x, b.x)&&cmp2(a, b); }
inline V operator+(const V &a, const V &b){ return V(a.x+b.x, a.y+b.y); }
inline V operator-(const V &a, const V &b){ return V(a.x-b.x, a.y-b.y); }
inline V operator*(const double &x, const V &a){ return V(a.x*x, a.y*x); }
inline V operator*(const V &a, const double &x){ return V(a.x*x, a.y*x); }
inline V operator/(const V &a, const double &x){ return V(a.x/x, a.y/x); }
inline bool operator==(const V &a, const V &b){ return equal(a.x, b.x)&&equal(a.y, b.y);}
inline bool operator!=(const V &a, const V &b){ return !(a==b); }
inline double operator*(const V &a, const V &b){ return a.x*b.x+a.y*b.y; }
inline double operator^(const V &a, const V &b){ return a.x*b.y-a.y*b.x; }
inline double len(const V &a){ return sqrtl(a.x*a.x+a.y*a.y); }
inline double dis(const V &a, const V &b){ return len(a-b); }
inline V mid(const V &a, const V &b){ return V((a.x+b.x)/2, (a.y+b.y)/2); }
inline V c_wise(const V &a){ return V(a.y, -a.x); }
inline V cc_wise(const V &a){ return V(-a.y, a.x); }
inline V unit(const V &a){ return a/len(a); }
inline double S_tri(const V &a, const V &b, const V &c){ return abs((b-a)^(c-a))/2; }
inline double S_iso(const double &l, const double &theta){ return 0.5*l*l*sinl(theta); }
inline bool operator<(const V &a, const V&b){  //二元组排序
    return less(a.x, b.x)||(equal(a.x, b.x)&&less(a.y, b.y));
}
inline double angle(const double &a, const double &b, const double &c){  //余弦定理
    return acosl((sqr(b)+sqr(c)-sqr(a))/(2*b*c));
}
inline double angle(const V &a, const V &b){
    if (zero(a^b)) return 0;
    return acosl(a*b/len(a)/len(b));
}  //0~pi
inline double angle2(const V &a, const V &b){  //-pi~pi，叉乘决定符号，与向量顺序有关
    return (a^b)>=0?angle(a, b):-angle(a, b);
}
inline bool obtuse(const V &a, const V &b, const V &c){ return less((b-a)*(c-a), 0); }
inline bool acute(const V &a, const V &b, const V &c){ return greater((b-a)*(c-a), 0); }
inline bool right(const V &a, const V &b, const V &c){ return zero((b-a)*(c-a)); }
inline V rotate(const V &a, double theta){
    double s=sinl(theta), c=cosl(theta);
    return V(a.x*c-a.y*s, a.x*s+a.y*c);
}
struct L{  //记录单位方向向量+两点，也可以用来表示线段
    V d, a, b;
    double ang;
    L(){}
    L(const V &x1, const V &x2, const V &x3):d(x1),a(x2),b(x3){}
    L(const V &x, const V &y){ *this=L(y-x, x, y); }
};
inline double angle(const L &l){
    if (zero(l.d.x)) return l.d.y>0?PI/2:-PI/2;
    return atan2(l.d.y, l.d.x);
}
inline V project(const V &p, const L &l){
    return l.a+((p-l.a)*unit(l.d))*unit(l.d);
}
inline V reflect(const V &p, const L &l){
    return 2*project(p, l)-p;
}
inline bool on_line(const V &p, const L &l){
    return zero(l.d^(p-l.a));
}
inline bool on_seg(const V &p, const L &l){
    return zero(dis(p, l.a)+dis(p, l.b)-dis(l.a, l.b));
}
inline double dis(const V &p, const L &l){
    return abs((p-l.a)^(p-l.b))/dis(l.a, l.b);
}
inline bool collinear(const V &a, const V &b){ return zero(a^b); }
inline bool orthogonal(const V &a, const V &b){ return zero(a*b); }
inline bool parallel(const L &l1, const L &l2){ return zero(l1.d^l2.d); }
inline bool orthogonal(const L &l1, const L &l2){ return zero(l1.d*l2.d); }
inline bool straddle(const L &l1, const L &l2){  //l1跨立在l2上
    double f1=(l1.a-l2.a)^l2.d;
    double f2=(l1.b-l2.a)^l2.d;
    if (f1*f2<eps) return true;
    else return false;
}
inline bool is_intersect(const L &l1, const L &l2){
    if (greater(min(l1.a.x, l1.b.x), max(l2.a.x, l2.b.x))||
        less(max(l1.a.x, l1.b.x), min(l2.a.x, l2.b.x))||
        greater(min(l1.a.y, l1.b.y), max(l2.a.y, l2.b.y))||
        less(max(l1.a.y, l1.b.y), min(l2.a.y, l2.b.y)))
            return false;
    //以上是快速排斥
    return straddle(l1, l2)&&straddle(l2, l1);
}  //先考虑l1跨立在l2上，再考虑l2跨立在l1上
inline V intersection(const L &l1, const L &l2){
    double k=((l2.a-l1.a)^l2.d)/(l1.d^l2.d);
    return l1.a+k*l1.d;
}
inline L bisector(const V &a, const V &b, const V &c){  //angleBAC
    V d1=(b-a)/len(b-a), d2=(c-a)/len(c-a);
    V d=(d1+d2)/len(d1+d2);
    return L(d, a, a+d);
}
inline L perpendicular(const V &a, const V &b){
    V x=mid(a, b), d=c_wise(b-a);
    return L(d, x, x+d);
}
//为方便操作直接传数组，以O为原点
inline double S_polygen(const V *a, const int &n){
    double res=0;
    for (int i=0; i<n; ++i) res+=(a[i]^a[(i+1)%n]);
    return res/2;
}
inline void read_polygen(V *a, int &n, bool with_n){
    if (with_n) scanf("%d", &n);
    for (int i=0; i<n; ++i) a[i].read();
}
inline bool is_convex(const V *a, const int &n){
    int j, k, d=0, nd; double o;
    for (int i=0; i<n; ++i){
        j=(i+1)%n, k=(i+2)%n;
        o=(a[j]-a[i])^(a[k]-a[j]);
        if (zero(o)) continue;
        nd=less(o, 0)?-1:1;
        if (!d) d=nd;
        else if (d!=nd) return false;
    }
    return true;
}
inline bool in_convex(const V &p, const V *a, const int &n){
    double x; int j, res=0;
    for (int i=0; i<n; ++i){
        j=(i+1)%n;
        if (equal(a[i].y, a[j].y)) continue;
        if (less(max(a[i].y, a[j].y), p.y)) continue;
        if (!less(min(a[i].y, a[j].y), p.y)) continue;
        x=a[i].x+(p.y-a[i].y)/(a[j].y-a[i].y)*(a[j].x-a[i].x);
        if (x<p.x) res^=1;
    }
    return res?true:false;
}
inline bool cmp(const V &a, const V &b){  //极角排序比较函数
    double dot=(a-O)^(b-O);
    if (dot>0) return true;
    if (dot==0) return dis(a, O)<dis(b, O);  //全共线情况
    return false;
}
inline void polar_sort(V *a, const int &n){
    int id=0;
    for (int i=0; i<n; ++i)
        if (less(a[i].y, a[id].y)||
                equal(a[i].y, a[id].y)&&less(a[i].x, a[id].x)) id=i;
    O=a[id];
    sort(a, a+n, cmp);
    int m;  //最后的共线部分要反转
    for (m=n-1; m>0; --m) if (!zero((a[m]-a[0])^(a[n-1]-a[0]))) break;
    reverse(a+m+1, a+n);
    O=V(0, 0);
}
inline void graham(V *a, int &n, bool include_on_edge){
    polar_sort(a, n); int cnt=0, id1, id2;
    int *s=new int[n];
    for (int i=0; i<n; ++i){
        while (cnt>=2){
            id1=s[cnt-1]; id2=s[cnt-2];
            if (include_on_edge){
                if (!less((a[id1]-a[id2])^(a[i]-a[id1]), 0)) break;
            } else if (greater((a[id1]-a[id2])^(a[i]-a[id1]), 0)) break;
            --cnt;
        }
        s[cnt++]=i;
    }
    n=cnt;
    delete s;
    for (int i=0; i<n; ++i) a[i]=a[s[i]];
}
double height(const V &a, const V &b1, const V &b2){
    return S_tri(a, b1, b2)/dis(b1, b2);
}
inline double diameter(const V *a, const int &n){
    double ans=0; int j=0;
    for (int i=0; i<n; ++i){
        while (less(height(a[i], a[j], a[(j+1)%n]), height(a[i], a[(j+1)%n], a[(j+2)%n])))
            j=(j+1)%n;  //不用less会出错：小精度误差导致的错误前进
        ans=max(ans, dis(a[i], a[j]));
        ans=max(ans, dis(a[i], a[(j+1)%n]));
    }
    return ans;
}
double max_dis(V *a, int &n){  //最长距离点对（直径）
    graham(a, n, false);
    return diameter(a, n);
}
inline double area(const V *a, const int &n){
    double ans=0;
    for (int i=0; i<n; ++i) ans+=a[i]^a[(i+1)%n];
    return ans/2;
}
void convex_cut(const V *a, V *b, const int &n, int &m, const L &l){  //半平面割
    V p[2]; int id[2], cnt=0;
    for (int i=0; i<n; ++i){
        if (straddle(L(a[i], a[(i+1)%n]), l)){
            if (on_line(a[(i+1)%n], l)) continue;
            id[cnt]=i;
            p[cnt]=intersection(L(a[i], a[(i+1)%n]), l);
            ++cnt;
        }
    }
    if (cnt<2){  //cut未形成割线
        bool flag=false;
        for (int i=0; i<n; ++i){
            if (greater(l.d^(a[i]-l.a), 0)) flag=true;
            if (less(l.d^(a[i]-l.a), 0)) flag=false;
            b[i]=a[i];
        }
        m=(flag?n:0);
        return;
    }
    if (less(l.d*(p[1]-p[0]), 0)){  //调整方向
        swap(p[0], p[1]);
        swap(id[0], id[1]);
    }
    cnt=0;
    b[cnt++]=p[0]; b[cnt++]=p[1];
    for (int i=(id[1]+1)%n; i!=(id[0]+1)%n; i=(i+1)%n)
        b[cnt++]=a[i];
    m=cnt;
}
double min_dis(V *a, V *b, const int &l, const int &r){  //随着分治进行，对b要按y排序
    if (l+1==r) return INF;
    int m=(l+r)>>1;
    double D=min(min_dis(a, b, l, m), min_dis(a, b, m, r));
    V *c=(V*)malloc(sizeof(V)*(r-l));
    V *d=(V*)malloc(sizeof(V)*(r-l));
    int i=l, j=m, cnt=0;
    while (i<m||j<r){  //归并
        if (j==r||i<m&&b[i].y<b[j].y) c[cnt++]=b[i++];
        else c[cnt++]=b[j++];
    } cnt=0;
    L seperator(a[m], V(a[m].x, a[m].y+1));
    for (i=0; i<r-l; ++i) if (dis(c[i], seperator)<D) d[cnt++]=c[i];
    for (i=0; i<cnt-2; ++i)  //距离分割线在d内的点，按y坐标向后枚举两个
        D=min(D, min(dis(d[i], d[i+1]), dis(d[i], d[i+2])));
    D=min(D, dis(d[cnt-2], d[cnt-1]));
    memcpy(b+l, c, sizeof(V)*(r-l));
    free(c); free(d);
    return D;
}
double min_dis(V *a, const int &n){  //最短距离点对
    sort(a, a+n, cmp1);
    V *b=(V*)malloc(sizeof(V)*n);
    memcpy(b, a, sizeof(V)*n);
    double ans=min_dis(a, b, 0, n);
    free(b);
    return ans;
}
struct C{
    V o;
    double r;
    C(const V &o1, double r1):o(o1), r(r1){}
    C(double a=0, double b=0, double c=0):o(a, b), r(c){}
    void read(){
        o.read();
        scanf("%Lf", &r);
    }
    void print(){
        printf("%.9Lf %.9Lf %.9Lf\n", o.x, o.y, r);
    }
};
inline bool in_cir(const V &p, const C &c){ return less(dis(c.o, p), c.r); }
inline bool on_cir(const V &p, const C &c){ return equal(dis(c.o, p), c.r); }
inline bool out_cir(const V &p, const C &c){ return greater(dis(c.o, p), c.r); }
inline double dis(const L &l, const C &c){ return dis(c.o, l); }
inline double dis(const C &c1, const C &c2){ return dis(c1.o, c2.o); }
inline double relation(const L &l, const C &c){
    double d=dis(l, c);
    if (less(d, c.r)) return -1;  //intersect
    else if (equal(d, c.r)) return 0;  //tangent
    else return 1;  //seperate
}
inline int relation(const C &c1, const C &c2){  //返回的是公切线数量
    double d=dis(c1, c2);
    if (greater(d, c1.r+c2.r)) return 4;  //seperate
    else if (equal(d, c1.r+c2.r)) return 3;  //circumscribed
    else if (less(max(c1.r, c2.r), min(c1.r, c2.r)+d)) return 2;  //intersect
    else if (equal(abs(c1.r-c2.r), d)) return 1;  //inscribed
    else return 0;  //include
}
inline C incircle(const V &a, const V &b, const V &c){  //内接圆
    V o=intersection(bisector(a, b, c), bisector(b, a, c));
    return C(o, dis(o, L(a, b)));
}
inline C excircle(const V &a, const V &b, const V &c){
    V o=intersection(perpendicular(a, b), perpendicular(a, c));
    return C(o, dis(o, a));
}
inline void get_intersection(const C &c, V &a, V &b){  //圆与直线交点
    L l=L(a, b);
    V p=project(c.o, l);
    double d=sqrtl(sqr(c.r)-sqr(dis(c.o, l)));
    a=p+unit(l.d)*d;
    b=p-unit(l.d)*d;
    if (cmp3(b, a)) swap(a, b);
}
inline void get_intersection(const C &c1, const C &c2, V &a, V &b){  //圆与圆交点
    double d=dis(c1, c2);
    double theta=acosl((sqr(c1.r)+sqr(d)-sqr(c2.r))/(2*c1.r*d));
    a=c1.o+c1.r*cosl(theta)*unit(c2.o-c1.o);
    b=a+c_wise(c2.o-c1.o);
    get_intersection(c1, a, b);
}
inline void get_tangent(const C &c, const V &p, V &a, V &b){
    C c2=C((c.o+p)/2, dis(c.o, p)/2);
    get_intersection(c, c2, a, b);
}
inline void get_circumscribe(const C &c1, const C &c2, V *v, int &cnt){  //两圆外切线
    int rel=relation(c1, c2);
    if (rel<1) return;
    double theta=acosl((c2.r-c1.r)/dis(c1, c2));
    V v1=rotate(c1.o-c2.o, theta), v2=rotate(c1.o-c2.o, -theta);
    v[cnt++]=c1.o+unit(v1)*c1.r;
    //v[cnt++]=c2.o+unit(v1)*c2.r;
    if (rel!=1) v[cnt++]=c1.o+unit(v2)*c1.r;
    //v[cnt++]=c2.o+unit(v2)*c2.r;
}
inline void get_inscribe(const C &c1, const C &c2, V *v, int &cnt){  //两圆内切线
    int rel=relation(c1, c2);
    if (rel<3) return;
    double theta=acosl((c1.r+c2.r)/dis(c1, c2));
    V v1=rotate(c2.o-c1.o, theta), v2=rotate(c2.o-c1.o, -theta);
    v[cnt++]=c1.o+unit(v1)*c1.r;
    //v[cnt++]=c2.o+unit(v1)*c2.r;
    if (rel!=3) v[cnt++]=c1.o+unit(v2)*c1.r;
    //v[cnt++]=c2.o+unit(v2)*c2.r;
}
inline double S(const C &c){ return PI*c.r*c.r; }
inline double S_sector(const C &c, double theta){
    return theta/2*c.r*c.r;
}
inline double S_sector(const C &c, const V &a, const V &b){  //a c.o b确定的角割出的扇形面积
    double theta=angle(a-c.o, b-c.o);
    return S_sector(c, theta);
}
inline double S_arc(const C &c, const V &a, const V &b){
    return S_sector(c, a, b)-S_tri(c.o, a, b);
}
double S_intersection(const V &a, const V &b, const C &c){  //圆心三角形和圆的面积交
    L l(a, b);
    double d=dis(c.o, l);
    if (!less(d, c.r)) return S_sector(c, a, b);
    if (in_cir(a, c)&&in_cir(b, c)) return S_tri(a, b, c.o);
    V P=a, P2=b, A=a, B=b;
    get_intersection(c, P, P2);
    if ((!in_cir(a, c))&&(!in_cir(b, c))){  //两边都在圆外
        if (!on_seg(P, l)) return S_sector(c, a, b);
        return S_sector(c, a, b)-S_arc(c, P, P2);
    }
    if (!in_cir(A, c)) swap(A, B);
    if (!on_seg(P, l)) swap(P, P2);
    return S_tri(A, P, c.o)+S_sector(c, B, P);
}
double S_intersection(const V *a, const int &n, C &c){  //圆与多边形的面积交
    double ans=0; int dir=0;
    for (int i=0; i<n; ++i){
        int j=(i+1)%n;
        dir=((a[j]-a[i])^(c.o-a[j]));
        dir=(dir>0?1:-1);
        ans+=dir*S_intersection(a[i], a[j], c);
    }
    return abs(ans);
}
double S_intersection(const C &c1, const C &c2){  //圆与圆的面积交(不是并！并的话改一下就行了)
    int rel=relation(c1, c2);
    if (rel>=3) return 0;
    if (rel<=1) return min(S(c1), S(c2));
    double d=dis(c1, c2);
    double alpha=angle(c2.r, c1.r, d)*2;
    double beta=angle(c1.r, c2.r, d)*2;
    double S1=S_sector(c1, alpha)-S_iso(c1.r, alpha);
    double S2=S_sector(c2, beta)-S_iso(c2.r, beta);
    return S1+S2;
}
inline bool in_hplane(const V &p, const L &l){
    return less((p-l.a)^l.d, 0);
}
inline bool out_hplane(const V &p, const L &l){
    return greater((p-l.a)^l.d, 0);
}
inline bool on_right(const L &a, const L &b, const L &c){  //a和b的交点在c右侧或c上
    if (parallel(a, b)) return true;
    return !in_hplane(intersection(a, b), c);
}
inline bool cmpL(const L &a, const L &b){
    if (equal(a.ang, b.ang)) return in_hplane(a.a, b);
    return a.ang<b.ang;
}
void hplane_intersection(L *a, int &n){  //队列中存的是应保留的线段的编号
    for (int i=0; i<n; ++i) a[i].ang=angle(a[i]);
    sort(a, a+n, cmpL);
    int *q=new int[n], h=0, t=0;
    for (int i=0; i<n; ++i){
        while (h<t-1&&on_right(a[q[t-2]], a[q[t-1]], a[i])) --t;
        while (h<t-1&&on_right(a[q[h]], a[q[h+1]], a[i])) ++h;
        q[t++]=i;
    }
    while (h<t-1&&on_right(a[q[t-1]], a[q[t-2]], a[q[h]])) --t;
    n=t-h;
    for (int i=h; i<t; ++i) a[i-h]=a[q[i]];  //返回删减后的有向边
}
bool build_convex(L *a, int &n, V *v){
    if (n<3) return false;
    for (int i=0; i<n; ++i)
        v[i]=intersection(a[i], a[(i+1)%n]);
    return true;
}
}
using namespace geo_2d;

const int maxn=2005;
int n, T, h, m;
double w;
int x, y, z;
V v1[maxn], v2[maxn], v3[maxn], v4[maxn*2];
L l1[maxn], l2[maxn], l[maxn*2];

int pre(int x){ return x?n-1:x-1; }
int nxt(int x){ return x==n-1?0:x+1; }

int main(){
    scanf("%d", &T);
    while (T--){
        scanf("%d%d%Lf", &n, &h, &w);
        read_polygen(v1, n, false);
        for (int i=0; i<n; ++i){
            l1[i]=L(v1[i], v1[nxt(i)]);
            l1[i].a=l1[i].a+cc_wise(unit(l1[i].d))*w;
            l1[i].b=l1[i].b+cc_wise(unit(l1[i].d))*w;
        }
        hplane_intersection(l1, n);
        build_convex(l1, n, v2);
        scanf("%d%d%d", &x, &y, &z);
        if (in_convex(V(x, y), v2, n)){
            printf("%.9Lf\n", S_polygen(v2, n));
            continue;
        }
        if (z<=h){
            puts("0.0");
            continue;
        }
        double lambda=1.0*z/(h-z);
        for (int i=0; i<n; ++i)
            v3[i]=V(x+lambda*(x-v2[i].x), y+lambda*(y-v2[i].y));
        for (int i=0; i<n; ++i){
            l2[i]=L(v3[i], v3[nxt(i)]);
            l[i]=l1[i];
            l[i+n]=l2[i];
        } m=2*n;
        hplane_intersection(l, m);
        build_convex(l, m, v4);
        printf("%.9Lf\n", S_polygen(v4, m));
    }
    return 0;
}