#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

namespace geo_3d{
const double eps=1e-9, INF=1e9, PI=3.14159265358979323846;
struct V{  //向量及其运算是几何基础，点也可以用向量表示
    double x, y, z;
    V():x(0),y(0),z(0){}
    V(const V &a){ *this=a; }
    V(const double &a, const double &b, const double &c):x(a),y(b),z(c){}
    void read(){ scanf("%lf%lf%lf", &x, &y, &z); }
    void print(){ printf("%.9lf %.9lf %.9lf\n", x, y, z); }  //位数多精度高
    void print_space(){ printf("%.9lf %.9lf %.9lf ", x, y, z); }
    void print_int(){ printf("%d %d %d\n", (int)x, (int)y, (int)z); }
}O;  //三个vector参数abc表示以a为顶点的角bac/cab
inline double sqr(const double &x){ return x*x; }
inline bool zero(const double &x){ return abs(x)<eps; }
inline bool zero(const V &p){ return zero(p.x)&&zero(p.y)&&zero(p.z); }
inline bool equal(const double &a, const double &b){ return zero(a-b); }
inline bool less(const double &a, const double &b){ return a<b-eps; }
inline bool greater(const double &a, const double &b){ return a>b+eps; }
inline bool cmp1(const V &a, const V &b){ return a.x<b.x; }
inline bool cmp2(const V &a, const V &b){ return a.y<b.y; }
inline bool cmp3(const V &a, const V &b){ return a.z<b.z; }
inline V operator+(const V &a, const V &b){ return V(a.x+b.x, a.y+b.y, a.z+b.z); }
inline V operator-(const V &a, const V &b){ return V(a.x-b.x, a.y-b.y, a.z-b.z); }
inline V operator*(const double &x, const V &a){ return V(a.x*x, a.y*x, a.z*x); }
inline V operator*(const V &a, const double &x){ return V(a.x*x, a.y*x, a.z*x); }
inline V operator/(const V &a, const double &x){ return V(a.x/x, a.y/x, a.z/x); }
inline bool operator==(const V &a, const V &b){ return equal(a.x, b.x)&&equal(a.y, b.y)&&equal(a.x, b.z);}
inline bool operator!=(const V &a, const V &b){ return !(a==b); }
inline double operator*(const V &a, const V &b){ return a.x*b.x+a.y*b.y+a.z*b.z; }
inline V operator^(const V &a, const V &b){
    return V(a.y*b.z-b.y*a.z, b.x*a.z-a.x*b.z, a.x*b.y-b.x*a.y);
}
inline double len(const V &a){ return sqrt(a.x*a.x+a.y*a.y+a.z*a.z); }
inline double dis(const V &a, const V &b){ return len(a-b); }
inline V mid(const V &a, const V &b){ return V((a.x+b.x)/2, (a.y+b.y)/2, (a.z+b.z)/2); }
inline V unit(const V &a){ return a/len(a); }
inline double S_tri(const V &a, const V &b, const V &c){ return len((b-a)^(c-a))/2; }
inline double S_iso(const double &l, const double &theta){ return 0.5*l*l*sin(theta); }
bool equal_sign(double a, double b){  //以下两个函数都比较严格
    return greater(a, 0)&&greater(b, 0)||less(a, 0)&&less(b, 0);
}
bool contra_sign(double a, double b){
    return greater(a, 0)&&less(b, 0)||less(a, 0)&&greater(b, 0);
}
inline double angle(const double &a, const double &b, const double &c){  //余弦定理
    return acos((sqr(b)+sqr(c)-sqr(a))/(2*b*c));
}
inline double angle(const V &a, const V &b){
    return acos(a*b/len(a)/len(b));
}  //0~pi
inline bool obtuse(const V &a, const V &b, const V &c){ return less((b-a)*(c-a), 0); }
inline bool acute(const V &a, const V &b, const V &c){ return greater((b-a)*(c-a), 0); }
inline bool right(const V &a, const V &b, const V &c){ return zero((b-a)*(c-a)); }
struct L{  //记录单位方向向量+两点，也可以用来表示线段  需保证两点有一定距离
    V d, a, b;
    L(){}
    L(const V &x1, const V &x2, const V &x3):d(x1),a(x2),b(x3){}
    L(const V &x, const V &y){ *this=L(y-x, x, y); }
    void read(){
        a.read(); b.read();
        d=b-a;
    }
    void print(){
        a.print(); b.print(); d.print();
    }
};
inline L line(const V &d, const V &p){ return L(d, p, p+d); }
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
    return len((p-l.a)^(p-l.b))/dis(l.a, l.b);
}
inline bool collinear(const V &a, const V &b){ return zero(a^b); }
inline bool orthogonal(const V &a, const V &b){ return zero(a*b); }
inline bool parallel(const L &l1, const L &l2){ return zero(l1.d^l2.d); }
inline bool orthogonal(const L &l1, const L &l2){ return zero(l1.d*l2.d); }
inline L bisector(const V &a, const V &b, const V &c){  //angleBAC
    V d1=(b-a)/len(b-a), d2=(c-a)/len(c-a);
    V d=(d1+d2)/len(d1+d2);
    return L(d, a, a+d);
}
struct P{
    V n, a;
    P(){}
    P(const V &x1, const V &x2):n(x1),a(x2){}
    void read(){
        V a, b, c;
        a.read(); b.read(); c.read();
        build(a, b, c);
    }
    void build(const V &x, const V &y, const V &z){ 
        *this={(y-x)^(z-x), x};
    }
};
inline double dis(const V &p, const P &plane){
    return (p-plane.a)*plane.n/len(plane.n);
}
inline bool on_plane(const V &p, const P &plane){
    return zero((p-plane.a)*plane.n);
}
inline bool parallel(const L &l, const P &plane){
    return zero(l.d*plane.n);
}
inline bool on_plane(const L &l, const P &plane){  //前提判断parallel
    return on_plane(l.a, plane);
}
inline bool is_intersect(const L &l, const P &plane){  //线段与平面相交
    double a=(l.a-plane.a)*plane.n, b=(l.b-plane.a)*plane.n;
    return !equal_sign(a, b);
}
inline V intersection(const L &l, const P &plane){
    const V &p=(on_plane(l.a, plane)?l.b:l.a);
    double k=((p-plane.a)*plane.n)/(l.d*plane.n);
    return p-k*l.d;
}
inline V project(const V &p, const P &plane){
    return intersection((L){plane.n, p, p+plane.n}, plane);
}
inline bool parallel(const P &p1, const P &p2){
    return zero(p1.n^p2.n);
}
inline L intersection(const P &p1, const P &p2){
    V d=p1.n^p2.n;
    V p=intersection(line(p1.n^d, p1.a), p2);
    return line(d, p);
}
struct G{
    V o;
    double r;
    G(){}
    G(const V &o1, double r1):o(o1), r(r1){}
    void read(){
        o.read();
        scanf("%lf", &r);
    }
    void print(){
        printf("%.9lf %.9lf %9.lf %.9lf\n", o.x, o.y, o.z, r);
    }
};
inline bool in_globe(const V &p, const G &c){ return less(dis(c.o, p), c.r); }
inline bool on_globe(const V &p, const G &c){ return equal(dis(c.o, p), c.r); }
inline bool out_globe(const V &p, const G &c){ return greater(dis(c.o, p), c.r); }
inline double dis(const L &l, const G &c){ return dis(c.o, l); }
inline double dis(const G &c1, const G &c2){ return dis(c1.o, c2.o); }
struct C{
    V o, n;
    double r;
    C(){}
    C(const V &x1, const V&x2, const double r1):o(x1), n(x2), r(r1){}
    void read(){
        o.read(); n.read();
        scanf("%lf", &r);
    }
    P plane()const{ return P(n, o); }
};
inline bool in_circle(const V &p, const C &c){  //先保证p在c所在平面上
    return less(dis(p, c.o), c.r);
}
inline bool out_circle(const V &p, const C &c){  //先保证p在c所在平面上
    return greater(dis(p, c.o), c.r);
}
inline vector<V> intersection(const C &c, const L &l){  //先保证l在c所在平面上
    vector<V> ret;
    if (!less(dis(c.o, l), c.r)) return ret;
    V p=project(c.o, l);
    double d=sqrt(sqr(c.r)-sqr(dis(c.o, l)));
    ret.push_back(p+unit(l.d)*d);
    ret.push_back(p-unit(l.d)*d);
    return ret;
}
inline vector<V> intersection(const C &c, const P &plane){
    if (parallel(c.plane(), plane)) return vector<V>();
    L l=intersection(c.plane(), plane);
    return intersection(c, l);
}
}
using namespace geo_3d;
