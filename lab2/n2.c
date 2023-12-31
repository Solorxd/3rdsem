#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

double geom_mean(int n, ...){
    va_list va;
    va_start(va, n);
    double log_sum = 0;
    double tmp;
    for(int i = 0; i < n; i++){
        tmp = va_arg(va, double);
        log_sum += log2(tmp);
    }
    if(log_sum && !isnan(log_sum)){
        return exp2(log_sum/n);
    }
    return 0;
}

float rec_pow(float x, int n){
    if(n > 0){
        if(n%2 == 1){
            return x * rec_pow(x*x, n/2);
        }
        return rec_pow(x*x, n/2);
    }else if(n == 0){
        return 1;
    }
    return rec_pow(1/x, n*(-1));
}

int main(){
    printf("%lf, %lf, %lf\n", rec_pow(-10, 2), rec_pow(1, 10), rec_pow(10, -5));
    printf("%lf, %lf, %lf\n", geom_mean(2, 2.0, 18.0), geom_mean(4, -1.0, -1.0, -1.0, -1.0), geom_mean(5, 10.0, 10.0, 10.0, 10.0, 10.0));
}