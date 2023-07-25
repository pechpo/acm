#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
//acos返回0~pi，asin返回-pi/2~pi/2。axx系列精度不好，慎用
namespace geo_2d{
const double INF=1e18, PI=3.14159265358979323846, eps=1e-9;
struct V{  //向量及其运算是几何基础，点也可以用向量表示
    LL x, y;
    V():x(0),y(0){}
    V(const V &a){ *this=a; }
    V(const LL &a, const LL &b):x(a),y(b){}
    void read(){ scanf("%lld%lld", &x, &y); }
    void print(){ printf("%lld %lld\n", x, y); }
}O, corner(-1e6-PI, -1e6-2*PI);  //三个vector参数abc表示以a为顶点的角bac/cab
inline bool zero(const double &x){ return abs(x)<eps; }
inline bool equal(const double &a, const double &b){ return zero(a-b); }
inline bool less(const double &a, const double &b){ return a<b-eps; }  //更严格
inline bool greater(const double &a, const double &b){ return a>b+eps; }
LL pre(LL i, LL n){ return i==0?n-1:i-1; }
LL nxt(LL i, LL n){ return i==n-1?0:i+1; }
/*
template <typename Iterator, typename Container>
Iterator pre(Iterator a, Container &S){
    return a==S.begin()?S.end():--a;
}
template <typename Iterator, typename Container>
Iterator nxt(Iterator a, Container &S){
    return ++a==S.end()?S.end():a;
}
*/
inline LL sqr(const LL &x){ return x*x; }
inline bool cmp1(const V &a, const V &b){ return a.x<b.x; }
inline bool cmp2(const V &a, const V &b){ return a.y<b.y; }
inline bool cmp3(const V &a, const V &b){ return a.x>b.x||a.x==b.x&&a.y<b.y; }   //先x后y升序排序
inline bool cmp4(const V &a, const V &b){ return a.x<b.x||a.x==b.x&&a.y>b.y; }   //先x后y升序排序
struct cmp5{
    bool operator()(const V &a, const V &b){ return cmp3(a, b); }
};
struct cmp6{
    bool operator()(const V &a, const V &b){ return cmp4(a, b); }
};
inline V operator-(const V &a){ return V(-a.x, -a.y); }
inline V operator+(const V &a, const V &b){ return V(a.x+b.x, a.y+b.y); }
inline V operator-(const V &a, const V &b){ return V(a.x-b.x, a.y-b.y); }
inline V operator*(const LL &x, const V &a){ return V(a.x*x, a.y*x); }
inline V operator*(const V &a, const LL &x){ return V(a.x*x, a.y*x); }
inline V operator/(const V &a, const LL &x){ return V(a.x/x, a.y/x); }
inline bool operator==(const V &a, const V &b){ return a.x==b.x&&a.y==b.y;}
inline bool operator!=(const V &a, const V &b){ return !(a==b); }
inline LL operator*(const V &a, const V &b){ return a.x*b.x+a.y*b.y; }
inline LL operator^(const V &a, const V &b){ return a.x*b.y-a.y*b.x; }
inline double len(const V &a){ return sqrt(a.x*a.x+a.y*a.y); }
inline double dis(const V &a, const V &b){ return len(a-b); }
inline V c_wise(const V &a){ return V(a.y, -a.x); }
inline double S_tri(const V &a, const V &b, const V &c){ return abs((b-a)^(c-a))/2; }
inline LL S_tri2(const V &a, const V &b, const V &c){ return abs((b-a)^(c-a)); }
inline double S_iso(const LL &l, const double &theta){ return 0.5*l*l*sin(theta); }
inline double S_roundtable(const LL &r, const LL &R, const LL &h){  //圆台体积
    return PI*h*(sqr(r)+r*R+sqr(R))/3;
}
bool equal_sign(LL a, LL b){
    return a>0&&b>0||a<0&&b<0;
}
bool contra_sign(LL a, LL b){
    return a>0&&b<0||a<0&&b>0;
}
/*inline bool operator<(const V &a, const V&b){  //二元组排序
    return less(a.x, b.x)||(equal(a.x, b.x)&&less(a.y, b.y));
}*/
inline double angle(const LL &a, const LL &b, const LL &c){  //余弦定理
    return acos((sqr(b)+sqr(c)-sqr(a))/(2*b*c));
}
inline double angle(const V &a, const V &b){  //向量夹角
    if ((a^b)==0) return 0;
    return acos(a*b/len(a)/len(b));
}  //0~pi
inline double angle2(const V &a, const V &b){  //-pi~pi，叉乘决定符号，与向量顺序有关
    return (a^b)>=0?angle(a, b):-angle(a, b);
}
inline bool obtuse(const V &a, const V &b, const V &c){ return (b-a)*(c-a)<0; }  //∠bac
inline bool acute(const V &a, const V &b, const V &c){ return (b-a)*(c-a)>0; }
inline bool right(const V &a, const V &b, const V &c){ return (b-a)*(c-a)==0; }
struct L{  //记录单位方向向量+两点，也可以用来表示线段
    V d, a, b;
    L(){}
    L(const V &x1, const V &x2, const V &x3):d(x1),a(x2),b(x3){}
    L(const V &x, const V &y){ *this=L(y-x, x, y); }
    L(const V &d){ *this=L(d, V(0,0), d); }
};
inline L get_L(const V &d, const V &p){ return L(d, p, p+d); }
inline double angle(const V &v){  //从x轴开始算
    double tmp=atan2(v.y, v.x);
    return tmp>=0?tmp:tmp+2*PI;
}
inline double angle(const L &l){
    return angle(l.d);
}
inline bool on_line(const V &p, const L &l){
    return (l.d^(p-l.a))==0;
}
inline bool on_seg(const V &p, const L &l){
    return (dis(p, l.a)+dis(p, l.b)-dis(l.a, l.b))==0;
}
inline double dis(const V &p, const L &l){
    return 1.0*abs((p-l.a)^(p-l.b))/dis(l.a, l.b);
}
inline double dis2(const V &p, const L &l){  //带符号距离
    return 1.0*((p-l.a)^(p-l.b))/dis(l.a, l.b);
}
inline bool collinear(const V &a, const V &b){ return (a^b)==0; }
inline bool orthogonal(const V &a, const V &b){ return a*b==0; }
inline bool parallel(const L &l1, const L &l2){ return (l1.d^l2.d)==0; }
inline bool orthogonal(const L &l1, const L &l2){ return (l1.d*l2.d)==0; }
inline bool straddle(const L &l1, const L &l2){  //l1跨立在l2上
    LL f1=(l1.a-l2.a)^l2.d;
    LL f2=(l1.b-l2.a)^l2.d;
    if (f1*f2<=0) return true;
    else return false;
}
inline bool is_intersect2(const L &l1, const L &l2){  //线与线段相交，l1为线
    LL a=(l2.a-l1.a)^l1.d, b=(l2.b-l1.a)^l1.d;
    if (a>=0&&b<=0) return true;
    if (a<=0&&b>=0) return true;
    return false;
}
inline bool is_intersect(const L &l1, const L &l2){  //线段相交
    if ((min(l1.a.x, l1.b.x)>=max(l2.a.x, l2.b.x))||
        (max(l1.a.x, l1.b.x)<=min(l2.a.x, l2.b.x))||
        (min(l1.a.y, l1.b.y)>=max(l2.a.y, l2.b.y))||
        (max(l1.a.y, l1.b.y)<=min(l2.a.y, l2.b.y)))
            return false;
    //以上是快速排斥
    return straddle(l1, l2)&&straddle(l2, l1);
}  //先考虑l1跨立在l2上，再考虑l2跨立在l1上
inline void read_polygon(V *a, LL &n, bool with_n){
    if (with_n) scanf("%d", &n);
    for (int i=0; i<n; ++i) a[i].read();
}
inline void print_polygon(V *a, LL &n, bool with_n){
    if (with_n) printf("%d\n", n);
    for (int i=0; i<n; ++i) a[i].print();
}
//为方便操作直接传数组，以O为原点
inline double L_polygen(const V *a, const LL &n){
    double res=0;
    for (LL i=0; i<n; ++i) res+=dis(a[i], a[(i+1)%n]);
    return res;
}
inline LL S2_polygen(const V *a, const LL &n){
    LL res=0;
    for (LL i=0; i<n; ++i) res+=(a[i]^a[(i+1)%n]);
    return res;
}
inline void read_polygen(V *a, LL &n, bool with_n){
    if (with_n) scanf("%lld", &n);
    for (LL i=0; i<n; ++i) a[i].read();
}
inline void print_polygen(V *a, LL &n, bool with_n){
    if (with_n) printf("%lld\n", n);
    for (LL i=0; i<n; ++i) a[i].print();
}
inline bool is_convex(const V *a, const LL &n){
    LL j, k, d=0, nd; LL o;
    for (LL i=0; i<n; ++i){
        j=(i+1)%n, k=(i+2)%n;
        o=(a[j]-a[i])^(a[k]-a[j]);
        if (o==0) continue;
        nd=o<0?-1:1;
        if (!d) d=nd;
        else if (d!=nd) return false;
    }
    return true;
}
inline bool cmp(const V &a, const V &b){
    LL dot=(a-O)^(b-O);
    if (dot>0) return true;
    return false;
}
inline LL rshort(const V &a, const V &b){  //极角排序(找正确的基准点以极角为指标排序）比较函数
    LL dot=(a-O)^(b-O);
    if (dot>0) return 2;  //左返回0，等返回1，右返回2
    if (dot==0) return dis(a, O)<=dis(b, O);  //全共线情况
    return 0;
}
inline LL lshort(const V &a, const V &b){
    LL dot=(a-O)^(b-O);
    if (dot>0) return 0;  //左返回2，等返回1，右返回0
    if (dot==0) return dis(a, O)<dis(b, O);
    return 2;
}
inline bool in_poly(const V &p, const V *a, const LL &n){
    double x; LL j, res=0;
    for (LL i=0; i<n; ++i){
        j=(i+1)%n;
        if (a[i].y==a[j].y) continue;
        if (max(a[i].y, a[j].y)<p.y) continue;
        if (min(a[i].y, a[j].y)>=p.y) continue;
        x=a[i].x+1.0*(p.y-a[i].y)/(a[j].y-a[i].y)*(a[j].x-a[i].x);
        if (x<p.x) res^=1;
    }
    return res?true:false;
}
inline LL in_convex(const V &p, const V *a, const LL &n){  //已经去边界极角排序，满足a[0]在最下方
    O=a[0];
    if (lshort(a[1], p)||rshort(a[n-1], p)) return 0;
    LL x=upper_bound(a+1, a+n, p, cmp)-a-1;
    O=a[x];  //2包含 1在边上 0在凸包外
    return lshort(p, a[(x+1)%n]);
}
inline V find_lowest(V *a, const LL &n){
    LL id=0;
    for (LL i=0; i<n; ++i)
        if (a[i].y<a[id].y||
                a[i].y==a[id].y&&a[i].x<a[id].x) id=i;
    return a[id];
}
inline void polar_sort(V *a, const LL &n, const V &origin){
    O=origin;
    sort(a, a+n, rshort);  //以在右侧或者共线且距离小为小
    LL m;  //最后的共线部分要反转，以便边上点要保留的情况
    for (m=n-1; m>=0; --m) if (!((a[m]-a[0])^(a[n-1]-a[0]))) break;
    if (~m) reverse(a+m+1, a+n);  //如果是一条直线就不用反转了
    O=V(0, 0);
}
bool cmp_A(const V &a, const V &b){
    double a1=angle(a-O), a2=angle(b-O);
    return a1<a2||a1==a2&&dis(a, O)<dis(b, O);
}
inline void polar_sort2(V *a, const LL &n, const V &origin){  //真·极角排序
    O=origin;
    sort(a, a+n, cmp_A);
    O=V(0, 0);
}
inline bool turn_right(const V &p1, const V &p2, const V &p3){  //p1指向p2，p2指向p3，前面乘后面
    return ((p2-p1)^(p3-p2))<0;
}
inline bool turn_left(const V &p1, const V &p2, const V &p3){
    return ((p2-p1)^(p3-p2))>0;
}
inline bool turn_right2(const V &O, const V &A, const V &B){  //OA到OB
    return ((A-O)^(B-O))<0;
}
inline bool turn_left2(const V &O, const V &A, const V &B){
    return ((A-O)^(B-O))>0;
}
inline void graham(V *a, LL &n, bool include_on_edge){
    LL cnt=0, id1, id2;
    LL *s=new LL[n];
    for (LL i=0; i<=n; ++i){
        while (cnt>=2){
            id1=s[cnt-1]; id2=s[cnt-2];
            if (include_on_edge){
                if (a[id1]!=a[i%n]&&!turn_right(a[id2], a[id1], a[i%n])) break;
            } else if (turn_left(a[id2], a[id1], a[i%n])) break;
            if (i==n&&cnt==2) break;  //特判点都在一条直线上的情况
            --cnt;
        }
        if (i<n) s[cnt++]=i;
    }
    //if (a[s[0]]==a[s[cnt-1]]) cnt=1;  //特判只有一个点的情况，不出现重复点
    n=cnt;
    for (LL i=0; i<n; ++i) a[i]=a[s[i]];
    delete []s;
}
inline void andrew(V *a, LL &n, bool include_on_edge){
    LL cnt=0, id1, id2;
    LL *s=new LL[n];
    for (LL i=0; i<n; ++i){
        while (cnt>=2){
            id1=s[cnt-1]; id2=s[cnt-2];
            if (include_on_edge){
                if (!turn_right(a[id2], a[id1], a[i%n])) break;
            } else if (turn_left(a[id2], a[id1], a[i%n])) break;
            --cnt;
        }
        if (i<n) s[cnt++]=i;
    }
    n=cnt;
    for (LL i=0; i<n; ++i) a[i]=a[s[i]];
    delete []s;
}
inline void merge_2(V *a, LL &n, V *b, LL &m, V *c, LL &N){
    N=0;
    for (LL i=0; i<n; ++i) c[N++]=a[i];
    for (LL i=1; i<m-1; ++i) c[N++]=b[i];
}
inline void merge_convex(V *a, LL &n, V *b, LL &m, V *c, LL &N, bool include_on_edge, bool (*cmp)(const V &a, const V &b)){
    LL cnta=0, cntb=0; N=0;
    while (N<n+m){
        while ((cntb==m||cmp(a[cnta], b[cntb]))&&cnta<n) c[N++]=a[cnta++];
        while ((cnta==n||!cmp(a[cnta], b[cntb]))&&cntb<m) c[N++]=b[cntb++];
    }
    andrew(c, N, include_on_edge);
}
template <typename cmp> using Iter=typename multiset<V, cmp>::iterator;
template <typename cmp, typename Iter>
inline bool in_dynavex(Iter iter, multiset<V, cmp> &S){
    if (iter==S.begin()||iter==--S.end()) return false;
    if (!turn_left(*pre(iter, S), *iter, *nxt(iter, S))) return true;
    return false;
}
template <typename cmp>
inline bool in_dynavex(V &p, multiset<V, cmp>&S){
    auto iter=S.find(p);
    if (iter!=S.end()) return true;
    iter=S.insert(p);
    bool flag=in_dynavex(iter, S);
    S.erase(iter);
    return flag;
}
template <typename maintain_type>  //对关于边的数据进行动态维护
inline void maintain1(maintain_type &obj, const V &a, const V &b){  //加边
    obj+=dis(a, b);
}
template <typename maintain_type>
inline void maintain2(maintain_type &obj, const V &a, const V &b){  //删边
    obj-=dis(a, b);
}
template <typename cmp, typename maintain_type>
inline void dynavex_insert(const V &p, multiset<V, cmp> &S, maintain_type &obj){
    auto iter=S.insert(p);
    if (S.siz()==2) maintain1(obj, *S.begin(), *++S.begin());
    if (S.siz()<3) return;
    if (in_dynavex(iter, S)){
        S.erase(iter);
        return;
    }
    if (iter!=S.begin()&&iter!=--S.end())
        maintain2(obj, *pre(iter, S), *nxt(iter, S));
    if (iter!=S.begin()){
        maintain1(obj, *pre(iter, S), *iter);
        while (pre(iter, S)!=S.begin()){
            auto iter2=pre(iter, S);
            auto iter3=pre(iter2, S);
            if (!turn_left(*iter3, *iter2, *iter)){
                maintain2(obj, *iter2, *iter3);
                maintain2(obj, *iter2, *iter);
                maintain1(obj, *iter3, *iter);
                S.erase(iter2);
            }
            else break;
        }
    }
    if (iter!=--S.end()){
        maintain1(obj, *nxt(iter, S), *iter);
        while (++nxt(iter, S)!=S.end()){
            auto iter2=nxt(iter, S);
            auto iter3=nxt(iter2, S);
            if (!turn_left(*iter, *iter2, *iter3)){
                maintain2(obj, *iter2, *iter3);
                maintain2(obj, *iter2, *iter);
                maintain1(obj, *iter3, *iter);
                S.erase(iter2);
            }
            else break;
        }
    }
}
template <typename maintain_type>
struct Dynavex{
    multiset<V, cmp5> upper;
    multiset<V, cmp6> lower;
    inline void insert(const V &p, maintain_type &obj){
        dynavex_insert(p, upper, obj);
        dynavex_insert(p, lower, obj);
    }
    inline bool inside(const V &p){
        return in_dynavex(p, upper)&&in_dynavex(p, lower);
    }
};
inline double height(const V &a, const V &b1, const V &b2){  //b1、b2为底
    return S_tri(a, b1, b2)/dis(b1, b2);
}
inline double diameter(const V *a, const LL &n){
    double ans=0; LL j=0;
    for (LL i=0; i<n; ++i){  //枚举顶点，对面是平行线
        while (height(a[i], a[j], a[(j+1)%n])<height(a[i], a[(j+1)%n], a[(j+2)%n]))
            j=(j+1)%n;
        ans=max(ans, dis(a[i], a[j]));
        ans=max(ans, dis(a[i], a[(j+1)%n]));
    }
    return ans;
}
double max_dis(V *a, LL &n){  //最长距离点对（直径）
    graham(a, n, false);
    return diameter(a, n);
}
double min_dis(V *a, V *b, const LL &l, const LL &r){  //随着分治进行，对b要按y排序
    if (l+1==r) return INF;
    LL m=(l+r)>>1;
    double D=min(min_dis(a, b, l, m), min_dis(a, b, m, r));
    V *c=(V*)malloc(sizeof(V)*(r-l));
    V *d=(V*)malloc(sizeof(V)*(r-l));
    LL i=l, j=m, cnt=0;
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
double min_dis(V *a, const LL &n){  //最短距离点对
    sort(a, a+n, cmp1);
    V *b=(V*)malloc(sizeof(V)*n);
    memcpy(b, a, sizeof(V)*n);
    double ans=min_dis(a, b, 0, n);
    free(b);
    return ans;
}
void Minkowski_sum(V *a, LL n, V *b, LL m, V *c, LL &N){
    V *l=(V*)malloc((n+m)*sizeof(V)); N=0;
    LL cnta=0, cntb=0;
    V pa, pb;
    while (cnta<n||cntb<m){
        if (n) pa=a[(cnta+1)%n]-a[cnta];
        if (m) pb=b[(cntb+1)%m]-b[cntb];
        if (cnta==n){
            l[N++]=pb; cntb++;
            continue;
        }
        if (cntb==m){
            l[N++]=pa; cnta++;
            continue;
        }
        if ((pa^pb)>0) l[N++]=pa, cnta++;
        else if ((pa^pb)==0) l[N++]=pa+pb, cnta++, cntb++;
        else l[N++]=pb, cntb++;
    }
    if (!m) c[0]=a[0];
    else if (!n) c[0]=b[0];
    else c[0]=a[0]+b[0];  //最下面的点，一定是正好往右走  //可以先判一下
    for (LL i=0; i<N; ++i)
        c[i+1]=c[i]+l[i];
    free(l);
}
using pdd=pair<double, double>;
inline bool seg_intersect(const pdd &a, const pdd &b){
    if (less(b.second, a.first)) return false;
    if (greater(b.first, a.second)) return false;
    return true;
}
inline void seg_add(pdd &a, const pdd &b){
    if (!seg_intersect(a, b)) return;
    a.first=min(a.first, b.first);
    a.second=max(a.second, b.second);
}
inline bool seg_include(const pdd &a, const pdd &b){
    return a.first<=b.first&&a.second>=b.second;
}
}
using namespace geo_2d;