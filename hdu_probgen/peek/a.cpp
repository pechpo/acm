#include<cstdio>
#include<vector>
#include<set>
#include<cmath>
#include<algorithm>
using namespace std;

struct Point{
    long double x, y;
    void read() {
        scanf("%Lf%Lf", &x, &y);
    }
    friend Point operator + (Point p1, Point p2) {
        return {p1.x + p2.x, p1.y + p2.y};
    }
    friend Point operator - (Point p1, Point p2) {
        return {p1.x - p2.x, p1.y - p2.y};
    }
    friend Point operator * (Point p1,long double k){
        return {p1.x*k, p1.y*k};
    }
    friend Point operator / (Point p1,long double k){
        return {p1.x/k, p1.y/k};
    }
    Point trans(long double newlen){
        long double len=mod(); 
        return {x/len*newlen, y/len*newlen};
    }
    long double mod(){return sqrt(x*x+y*y);}
};

long double mulpoint(Point v1,Point v2){return (v1.x*v2.x+v1.y*v2.y);}
long double mulcross(Point v1,Point v2){return (v1.x*v2.y-v1.y*v2.x);}

struct Segment{
    Point p1, p2;
    long double prevLen = 0;
    void read() {
        p1.read(); p2.read();
    }
    long double len() {
        return (p1-p2).mod();
    }
    friend bool operator < (Segment ls, Segment rs) {
        return ls.prevLen < rs.prevLen;
    }
    Point mid() {return (p1+p2)/2;}
};

struct note{
    long double len;
    int type;  
    friend bool operator < (note a1,note a2) {
        return a1.len < a2.len;
    }
};


bool isRaySegmentIntersection(Segment& ray, Segment& seg) {
    return  mulcross(seg.p1-ray.p1, ray.p2-ray.p1)*
            mulcross(seg.p2-ray.p1, ray.p2-ray.p1) < -1e-4;
}

int sgn(long double x) {return x>0? 1: (x<0? -1: 0);}

int dcmp(long double x){
    if(fabs(x) < 1e-18) return 0;
    else return x < 0 ? -1 : 1;
}
bool segment_proper_intersection(Point& a1, Point& a2, Point& b1, Point& b2)
{
    long double c1 = mulcross(a2 - a1, b1 - a1), c2 = mulcross(a2 - a1, b2 - a1);
    long double c3 = mulcross(b2 - b1, a1 - b1), c4 = mulcross(b2 - b1, a2 - b1);
    return dcmp(c1) * dcmp(c2) <= 0 && dcmp(c3) * dcmp(c4) <= 0;
}

bool isSegSegIntersection(Segment& ray, Segment& seg) {
    return segment_proper_intersection(ray.p1, ray.p2, seg.p1, seg.p2);
}
struct Line {
    Point p, u;
    Line(Segment s) : p(s.p1), u(s.p2-s.p1) {}
};
Point inters(Line l1,Line l2){return l1.p+l1.u*(mulcross(l2.p-l1.p,l2.u)/mulcross(l1.u,l2.u));}

bool samedir(Point p1, Point p2, Point p0) {
    return mulpoint(p1-p0, p2-p0) > 0;
}

Segment shink(Point p1, Point p2) {
    return {p1 + (p2-p1).trans(1e-8), p2 + (p1-p2).trans(1e-8)};
}

void work(vector<Point>& points, set<Segment> segset, Point light, vector<note>& ans, Point& lv, Point &rv) {
    // printf("\nlight: %Lf %Lf\n", light.x, light.y);
    for (int i=0; i<(int)points.size(); i++) {
        Segment ray = {points[i], light};
        if (ray.len() < 1e-8) continue;

        long double mindis = 1e18; 
        Segment minseg;
        for (auto seg : segset) {
            if (isRaySegmentIntersection(ray, seg)) {
                auto inter = inters(ray, seg);
                auto newdis = (inter-light).mod();
                if (samedir(inter, points[i], light) && newdis < mindis) {
                    mindis = newdis;
                    minseg = seg;
                }
            }
        }
        if (mindis < 1e16) {
            segset.erase(minseg);
            auto inter = inters(ray, minseg);
            Segment s1 = {minseg.p1, inter, minseg.prevLen};
            Segment s2 = {inter, minseg.p2, minseg.prevLen + s1.len()};
            segset.insert(s1);
            segset.insert(s2);
        }
    }

    for (auto seg : segset) {
        auto mid = seg.mid();
        
        // printf("mid : %Lf %Lf\n", mid.x, mid.y);
        double fsgn = mulcross(lv, mid-light)*mulcross(mid-light, rv);
        double fsgn2 = mulcross(lv, mid-light)*mulcross(lv, rv);
        if (fsgn < -1e-3 ||  fsgn2 < -1e-3) continue;

        bool isValid = true;
        for (auto o : segset) {
            if ((o.p2-o.p1).mod() < 1e-8) continue;
            Segment tryer = shink(light, mid);
            if (isSegSegIntersection(tryer, o)) {
                // printf("(%.8Lf %.8Lf) (%.8Lf %.8Lf)\n", o.p1.x, o.p1.y, o.p2.x, o.p2.y);
                isValid = false;
                break;
            }
        }
        if (isValid) {
            // printf("segment: %Lf %Lf\n", seg.prevLen, seg.prevLen + seg.len());
            ans.push_back({seg.prevLen, 1});
            ans.push_back({seg.prevLen + seg.len(), -1});
        }
    }

}
void solve() 
{
    int n,m;
    scanf("%d%d",&n,&m);
    vector<Point> points(n);
    vector<Segment> segments(n);
    set<Segment> segset;
    for (int i=0;i<n;i++) points[i].read();
    for (int i=0;i<n;i++) segments[i] = {points[i], points[(i+1)%n]};
    for (int i=0;i<n;i++) {
        if (i!=0) {
            segments[i].prevLen = segments[i-1].prevLen + segments[i-1].len();
        }
        segset.insert(segments[i]);
    }

    vector<int> lights(m);
    vector<note> ans;
    for (int i=0;i<m;i++) {
        scanf("%d", &lights[i]);
        lights[i]--;
        
        Point light = points[lights[i]];
        Point lv = (points[(lights[i]+1)%n]-light);
        Point rv = (points[(lights[i]-1+n)%n]-light);
        work(points, segset, light + lv.trans(1e-6), ans, lv, rv);
        work(points, segset, light + rv.trans(1e-6), ans, lv, rv);

        ans.push_back({segments[lights[i]].prevLen, 1});
        ans.push_back({segments[lights[i]].prevLen + segments[lights[i]].len(), -1});
        ans.push_back({segments[(lights[i]-1+n)%n].prevLen, 1});
        ans.push_back({segments[(lights[i]-1+n)%n].prevLen + segments[(lights[i]-1+n)%n].len(), -1});
    }
    sort(ans.begin(), ans.end());
    long double ret = 0, lst = -1e9;
    int lightLevel = 0;
    for (auto a_ans : ans) {
        if (a_ans.type == 1) {
            lightLevel++;
            if (lightLevel == 1) {
                lst = a_ans.len;
            }
        }else{
            lightLevel--;
            if (lightLevel == 0) {
                ret += a_ans.len - lst;
            }
        }
        // printf("%d %d %Lf %Lf\n", a_ans.type, lightLevel, a_ans.len, lst);
    }
    printf("%Lf\n", ret);
}

int main()
{
    freopen("data.in", "r", stdin);
    freopen("other.out", "w", stdout);
    int t;
    scanf("%d", &t);
    while (t--) solve();
    fclose(stdin); fclose(stdout);
}