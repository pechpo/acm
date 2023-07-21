#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

using LL = long long;
using LD = long double;
using PII = pair<int, int>;

LL gcd(LL x, LL y) { return y ? gcd(y, x % y) : x; }

LD sqr(LD v) { return v * v; }

const int maxn = 1e6 + 5;
PII p[maxn];
int id[maxn], n;

int mod(int x)
{
    if (x < 0)
        return x + n;
    if (x >= n)
        return x - n;
    return x;
}

struct L
{
    LL A, B, C;
    L(const PII &a, const PII &b)
    {
        A = b.second - a.second, B = a.first - b.first;
        LL d = gcd(A, B);
        A /= d, B /= d;
        C = -A * a.first - B * a.second;
    }
    LL lenl(const PII &c)
    {
        return abs(A * c.first + B * c.second + C);
    }
    LD len(const PII &c)
    {
        return lenl(c) / sqrtl(sqr(A) + sqr(B));
    }
};

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        p[i].first = x ;
        p[i].second = y;
    }
    for (int i = 0; i < n; ++i)
    {
        id[i] = i;
    }
    sort(id, id + 3);
    int x = id[0], y = id[1], z = id[2];
    for (int i = 0; i < 10000; ++i)
    {
        L l1(p[x], p[y]);
        bool ux = false, uy = false, uz = false;
        while (l1.lenl(p[mod(z + 1)]) > l1.lenl(p[z]))
            z = mod(z + 1), uz = true;
        while (l1.lenl(p[mod(z - 1)]) > l1.lenl(p[z]))
            z = mod(z - 1), uz = true;
        L l2(p[x], p[z]);
        while (l2.lenl(p[mod(y + 1)]) > l2.lenl(p[y]))
            y = mod(y + 1), uy = true;
        while (l2.lenl(p[mod(y - 1)]) > l2.lenl(p[y]))
            y = mod(y - 1), uy = true;
        L l3(p[y], p[z]);
        while (l3.lenl(p[mod(x + 1)]) > l3.lenl(p[x]))
            x = mod(x + 1), uz = true;
        while (l3.lenl(p[mod(x - 1)]) > l3.lenl(p[x]))
            x = mod(x - 1), uz = true;
        if (!ux && !uy && !uz)
            break;
    }
    printf("%d %d %d\n", x + 1, y + 1, z + 1);
    return 0;
}
