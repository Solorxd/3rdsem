#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

double Polynom(double x, int n, ...){
    va_list va;
    va_start(va, n);
    if(n == 0){
        double tmp = va_arg(va, double);
        va_end(va);
        return tmp;
    }else if(n < 0){
        return 0.0;
    }
    double summ = va_arg(va, double) * x;
    for(int i = 0; i < n-1; i++){
        summ += va_arg(va, double);
        summ *= x;
    }
    summ += va_arg(va, double);
    va_end(va);
    return summ;
}

double f1(double x){
    return Polynom(x, 2, 1.0, 2.0, -6.0);
}

double dih(double A, double B, double eps, double (*f)(double)){
    if(A > B){
        double tmpd = A;
        A = B;
        B = tmpd;
    }
    eps = fabs(eps);
    double C, tmpf;
    while(B - A > eps){
        C = (A+B)/2;
        tmpf = f(C);
        if(tmpf*f(A) < 0){
            B = C;
        }else{
            A = C;
        }
    }
    if(f((A+B)/2) < eps){
        return (A+B)/2;
    }else{
        return B+1;
    }
}

double dih_menu(double A, double B, double eps, double (*f)(double)){
    if(A > B){
        double tmpd = A;
        A = B;
        B = tmpd;
    }
    double tmp = dih(A, B, eps, f);
    if(tmp > B){
        printf("root not found\n");
        return 0;
    }
    else{
        return tmp;
    }
}

int main(){
    printf("%f\n", dih_menu(0, 2, 1e-8, f1));
    return 0;
}