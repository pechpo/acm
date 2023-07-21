#include <cstdio>
using namespace std;

struct Bit{  //Fenwick Tree
    const static int maxn=1e5+5;
    int a[maxn], n, q[maxn], m;
    inline int lowbit(int x){ return x&(-x); }
    Bit(){};
    Bit(int N){ n=N; }  //注意初始化大小
    inline void clear(){
        for (int i=0; i<m; ++i)
            a[q[i]]=0;
        m=0;
    }
    inline void modify(int x, int d){
        while (x<=n){
            if (!a[x]) q[m++]=x;
            a[x]+=d;
            x+=lowbit(x);
        }
    }
    inline int query(int x){
        int ans=0;
        while (x){
            ans+=a[x];
            x-=lowbit(x);
        }
        return ans;
    }
    inline int query(int l, int r){
        return query(r)-query(l-1);
    }
}bit;