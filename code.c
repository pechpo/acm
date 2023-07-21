#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double a[5], avg, std_dvt;
double rand_d(double l, double r){
    return 1.0*rand()/RAND_MAX*(r-l)+l;
}
double sqr(double x){ return x*x; }
double max(double x, double y){ return x<y?y:x; }

int main(){
    srand(time(0));
    for (int i=0; i<5; ++i){
        a[i]=rand_d(2, 10);
        avg+=a[i];
    }
    avg/=5;
    for (int i=0; i<5; ++i) printf("%.2lf ", a[i]);
    puts("");
    printf("%.2lf\n", avg);
    for (int i=0; i<5; ++i) std_dvt+=sqr(a[i]-avg);
    std_dvt=sqrt(std_dvt);
    printf("%.2lf\n", std_dvt);
    double tmp, maxsum=0;
    for (int i=0; i<3; ++i){
        tmp=a[i]+a[i+1];
        maxsum=max(maxsum, tmp);
    }
    printf("%2lf\n", maxsum);
    return 0;
}