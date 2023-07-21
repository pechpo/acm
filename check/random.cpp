#include <set>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int maxn=100;

int rand_int(int x){
    return rand()%x+1;
}

int rand_int(int l, int r){
    return rand_int(r-l+1)+l-1;
}

int main(){
    freopen("data.in", "w", stdout);
    time_t t;
    srand(time(&t));
    int T=11, n, q, x, y;
    printf("%d\n", T);
    for (int i=0; i<T; ++i){
        n=rand_int(maxn/2, maxn);
        q=rand_int(maxn/2, maxn);
        printf("%d %d\n", n, q);
        for (int i=0; i<n; ++i){
            x=rand_int(-maxn, maxn);
            y=rand_int(-maxn, maxn);
            printf("%d %d\n", x, y);
        }
        for (int i=0; i<q; ++i)
            printf("%d\n", rand_int(0, maxn));
    }
    fclose(stdout);
    return 0;
}