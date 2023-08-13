#include <cstdio>
using namespace std;

int main(){
    freopen("test.in", "w", stdout);
    puts("1000");
    for (int i=1; i<=1000; ++i){
        puts("-1000 -1000 1000 1000\n-1000 1000 1000 -1000");
    }
    fclose(stdout);
    return 0;
}