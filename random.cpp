#include <ctime>
#include <cstdio>
#include <random>
#include <iostream>
using namespace std;

int main(){
    default_random_engine e(time(0));
    uniform_int_distribution<int> u1(0, 10);
    uniform_real_distribution<double> u2(0, 1);
    printf("%d\n", u1(e));
    printf("%.9lf\n", u2(e));
    srand(time(NULL));
    printf("%d\n", rand());
    return 0;
}