#include <cstdio>
using namespace std;

const int mod=998244353, maxn=2e5+5;

int pow(int a, int x){
    int base=a, val=1;
    for (; x; x>>=1){
        if (x&1) val=1ll*val*base%mod;
        base=1ll*base*base%mod;
    }
    return val;
}

int rev(int a){
    return pow(a, mod-2);
}

int fac[maxn];
void init(){
    fac[0]=fac[1]=1;
    for (int i=2; i<maxn; ++i)
        fac[i]=1ll*fac[i-1]*i%mod;
}

int main(){
    init();
    printf("%d %d %d\n", fac[5], pow(3, 4), rev(2));
    return 0;
}