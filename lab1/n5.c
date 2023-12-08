#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

int float_args_check(char **argv, float *eps, float *x){
    *eps = strtof(argv[1], NULL);
    *x = strtof(argv[2], NULL);
    if(fabs(*eps) == HUGE_VALF || fabs(*x) == HUGE_VALF || isnan(*x) || isnan(*eps)){
        return 0;
    }
    if(*eps < 0){
        *eps = fabs(*eps);
        return 2;
    }
    return 1;
}

int main(int argc, char **argv){
    float eps, x;
    if(argc != 3){
        printf("wrong arg amouth");
        return 0;
    }
    switch(float_args_check(argv, &eps, &x)){
    case 0:{
        printf("float overflow\n");
        return 0;
        }
    case 2:{
        printf("eps must be a positive number\nprogramm will continue with absolute value of eps\n");
        break;
        }
    }
    double summ_a = 0, summ_b = 0, summ_c = 0, summ_d = 0;
    double sl;
    int n;
    double factorial = 1;
    n = 0;
    sl = pow(x, n)/factorial;
    while (fabs(sl) > eps && !isinf(summ_a) && !isnan(summ_a)){
        summ_a += sl;
        n++;
        factorial *= n;
        sl = pow(x, n)/factorial;
    }

    n = 0;
    factorial = 1;
    sl = pow(-1, n)*pow(x, 2*n)/factorial;
    while (fabs(sl) > eps && !isinf(summ_b) && !isnan(summ_b)){
        summ_b += sl;
        n++;
        factorial *= 2*n*(2*n-1);
        sl = (pow(-1, n)*pow(x, 2*n))/factorial;
    }

    n = 0;
    factorial = 1;
    double factorial2 = 1; 
    sl = pow(3, 3*n)*pow(factorial, 3)*pow(x, 2*n)/factorial2;
    while (fabs(sl) > eps && !isinf(summ_c) && !isnan(summ_c)){
        summ_c += sl;
        n++;
        factorial *= n;
        factorial2 *= 3*n*(3*n-1)*(3*n-2);
        sl = (pow(3, 3*n)*pow(factorial, 3)*pow(x, 2*n))/factorial2;
    }

    n = 1;
    factorial = 1;
    factorial2 = 2;
    sl = pow(-1, n)*factorial*pow(x, 2*n)/factorial2;
    while (fabs(sl) > eps && !isinf(summ_d) && !isnan(summ_d)){
        summ_d += sl;
        n++;
        factorial *= 2*n - 1;
        factorial2 *= 2*n;
        sl = (pow(-1, n)*factorial*pow(x, 2*n))/factorial2;
    }

    if(!isinf(summ_a) && !isnan(summ_a)){
        printf("S_a = %f\n", summ_a);
    }else{
        printf("a. summ value overflow\n");
    }
    if(!isinf(summ_b) && !isnan(summ_b)){
        printf("S_b = %f\n", summ_b);
    }else{
        printf("b. summ value overflow\n");
    }
    if(!isinf(summ_c) && !isnan(summ_c)){
        printf("S_c = %f\n", summ_c);
    }else{
        printf("c. summ value overflow\n");
    }
    if(!isinf(summ_d) && !isnan(summ_d)){
        printf("S_d = %f\n", summ_d);
    }else{
        printf("d. summ value overflow\n");
    }
    return 1;
}