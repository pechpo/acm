#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn=2005;
char s1[maxn], s2[maxn], S[maxn];
int n, n1, n2, m1, m2, m;
int a1[maxn], a2[maxn], a[maxn], offset;

int main(){
    scanf("%s%s", s1, s2);
    n1=strlen(s1), n2=strlen(s2);
    int o1=0, o2=0;
    for (int i=0; i<n1; ++i)  //去小数点
        if (s1[i]=='.') o1=n1-i-1;
    for (int i=0; i<n2; ++i)
        if (s2[i]=='.') o2=n2-i-1;
    offset=max(o1, o2);
    for (int i=0; i<offset-o1; ++i) a1[m1++]=0;  //补后导零
    for (int i=0; i<offset-o2; ++i) a2[m2++]=0;
    for (int i=n1-1; i>=0; --i)
        if (s1[i]!='.') a1[m1++]=s1[i]-'0';
    for (int i=n2-1; i>=0; --i)
        if (s2[i]!='.') a2[m2++]=s2[i]-'0';
    m=max(m1, m2);
    for (int i=0; i<m; ++i) a[i]=a1[i]+a2[i];
    for (int i=0; i<m; ++i)
        if (a[i]>9) a[i]-=10, a[i+1]++;  //加法和进位
    if (a[m]) ++m;
    for (int i=m-1; i>=0; --i){
        S[n++]=a[i]+'0';
        if (i&&i==offset) S[n++]='.';
    }
    char *s=S;
    while (*s=='0'&&n>1&&*(s+1)!='.')
        ++s, --n;
    for (int i=o1; i<offset; ++i) n1++;  //格式问题，补假想小数
    for (int i=o2; i<offset; ++i) n2++;
    if (o1&&!o2) n2++;
    if (o2&&!o1) n1++;
    int N=max(n1, max(n2, n))+3;
    for (int i=0; i<N-n1; ++i) putchar(' ');
    printf("%s", s1);
    for (int i=o1; i<offset; ++i) putchar(' ');
    if (o2&&!o1) putchar(' ');
    puts("");
    putchar('+');
    for (int i=1; i<N-n2; ++i) putchar(' ');
    printf("%s", s2);
    for (int i=o2; i<offset; ++i) putchar(' ');
    if (o1&&!o2) putchar(' ');
    puts("");
    for (int i=0; i<N; ++i) putchar('-');
    puts("");
    for (int i=0; i<N-n; ++i) putchar(' ');
    printf("%s\n", s);
    return 0;
}