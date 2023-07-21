#include <cstdio>

int mod1=1e9+7, mod2=998244353;

int hash(char *s, const int &n, int mod){
    unsigned long long res=0;
    for (int i=0; i<n; ++i)
        res=((res<<8)+s[i])%mod;
    return (int)res;
}