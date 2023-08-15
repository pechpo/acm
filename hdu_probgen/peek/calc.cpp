#include <cmath>
#include <cstdio>
using namespace std;

int x, y;

int main(){
    x=1000000000; y=x;
    for (int i=1; i<=80; ++i){
        x-=25000000;
        printf("%d %d\n", x, y);
    }
    return 0;
}