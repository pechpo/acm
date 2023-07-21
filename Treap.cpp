#include <cstdio>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>
using namespace std;

default_random_engine generator;
uniform_int_distribution<int> distribution(INT_MIN, INT_MAX);
auto dice=bind(distribution, generator);

const int maxn=2e6+5;

struct Treap{
    int n, rt, cnt;
    int c[maxn][2], key[maxn], pri[maxn]={INT_MAX};
    int p[maxn], size[maxn], mul[maxn];
    int t, q[maxn];  //垃圾回收
    inline int bias(int x){ return x==c[p[x]][1]; }
    inline int new_node(){ return t?q[--t]:++cnt; }
    inline void push_up(int x){
        size[x]=size[c[x][0]]+size[c[x][1]]+mul[x];
    }
    inline void link(int x, int y, int b){
        if (y) p[y]=x;
        if (x) c[x][b]=y; else rt=y;
    }
    void rotate(int x, int l){
        int y=c[x][l^1], z=p[x], b=bias(x), u=c[y][l];
        link(z, y, b);
        link(y, x, l);
        link(x, u, l^1);
        push_up(x); push_up(y);
    }
    void insert(int x){
        int z=rt, y=0, b=0;
        while (z){
            ++size[z];
            if (x==key[z]){ ++mul[z]; return; }
            if (x<key[z]) z=c[y=z][b=0];
            else z=c[y=z][b=1];
        }
        z=new_node();
        link(y, z, b);
        key[z]=x; pri[z]=dice();
        size[z]=mul[z]=1; 
        while (z!=rt){
            y=p[z]; b=bias(z);
            if (pri[y]<pri[z]) break;
            rotate(y, b^1);
        }
    }
    void delete_key(int x){
        int z=rt;
        while (key[z]!=x){
            --size[z];
            if (x<key[z]) z=c[z][0];
            else z=c[z][1];
        }
        if (mul[z]>1){
            --size[z]; --mul[z];
            return;
        }
        int l, w;
        while (size[z]>1){
            l=(pri[c[z][0]]>pri[c[z][1]]);
            w=c[z][l];
            rotate(z, l^1); --size[w];
        }
        link(p[z], 0, bias(z));
        q[t++]=z;
    }
    int select(int x){
        int z=rt, cnt=0;
        while (z&&key[z]!=x){
            if (x<key[z]) z=c[z][0];
            else cnt+=size[c[z][0]]+mul[z], z=c[z][1];
        }
        return cnt+size[c[z][0]]+1;
    }
    int rank(int x){
        int z=rt, cnt=size[c[z][0]];
        while (!(x>cnt&&x<=cnt+mul[z])){
            if (x<=cnt){
                cnt-=size[c[z][0]];
                z=c[z][0];
                cnt+=size[c[z][0]];
            } else {
                cnt+=mul[z];
                z=c[z][1];
                cnt+=size[c[z][0]];
            }
        }
        return key[z];
    }
    int predecessor(int x){
        int z=rt, y=0;
        while (z){
            if (x<=key[z]) z=c[z][0];
            else y=z, z=c[z][1];
        }
        return key[y];
    }
    int successor(int x){
        int z=rt, y=0;
        while (z){
            if (x<key[z]) y=z, z=c[z][0];
            else z=c[z][1];
        }
        return key[y];
    }
}T;

int main(){
    int n, op, x;
    scanf("%d", &n);
    while (n--){
        scanf("%d%d", &op, &x);
        if (op==1) T.insert(x);
        if (op==2) T.delete_key(x);
        if (op==3) printf("%d\n", T.select(x));
        if (op==4) printf("%d\n", T.rank(x));
        if (op==5) printf("%d\n", T.predecessor(x));
        if (op==6) printf("%d\n", T.successor(x));
    }
    return 0;
}