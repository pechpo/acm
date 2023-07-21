#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn=1e6+65;
using ull=unsigned long long;
struct Bitset{
    ull a[maxn>>6];  //64=2^6 这是存数据的，pos是存位置的
    int len;
    void get_len(int l){ len=(l>>6)+1; }
    inline void set0(int pos){ a[pos>>6]&=~(1ull<<(pos&63)); }
    inline void set1(int pos){ a[pos>>6]|=1ull<<(pos&63); }
    inline void set(int pos, int x){ if (x==1) set1(pos); else set0(pos); }
    inline bool operator[](int pos){ return a[pos>>6]&(1ull<<(pos&63)); }
    inline ull tail(int pos){  //从pos到此节末尾的数据块
        return a[pos>>6]<<(pos&63);
    }
    inline ull head(int pos){  //从此节开头到pos的数据块
        return a[pos>>6]>>(~(pos&63));
    }
}a, b;
# define BIT2(n)       n,       n+1,       n+1,       n+2
# define BIT4(n) BIT2(n), BIT2(n+1), BIT2(n+1), BIT2(n+2)
# define BIT6(n) BIT4(n), BIT4(n+1), BIT4(n+1), BIT4(n+2)
# define BIT8(n) BIT6(n), BIT6(n+1), BIT6(n+1), BIT6(n+2)
const int table[256]={BIT8(0)};
inline int popcnt(ull x){ int ans=0; while (x) ans+=table[x&255], x>>=8; return ans; }

char s[maxn], t[maxn];

int main(){
    scanf("%s%s", s, t);
    int n=strlen(s), m=strlen(t);
    a.get_len(n); b.get_len(m);
    for (int i=0; i<n; ++i) a.set(i, (s[i]=='b'));
    for (int i=0; i<m; ++i) b.set(i, (t[i]=='b'));
    int ans=m;
    for (int i=0; i<=n-m; ++i){
        int cnt=0;
        for (int j=0; j<b.len; ++j){
            cnt+=popcnt(a.tail(i+(j<<6))&b.a[j]);
            if (i&64) cnt+=popcnt(a.head(i+(j+1<<6)-1)&b.a[j]);
        }
        ans=min(ans, cnt);
    }
    printf("%d\n", ans);
    return 0;
}