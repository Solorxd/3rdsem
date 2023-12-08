#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int float_args_check(char **argv, double *eps){
    *eps = strtof(argv[1], NULL);
    if(*eps < 0){
        *eps = fabs(*eps);
        return -1;
    }
    return 1;
}

float f1(float x){
    return log(1+x)/x;
}

float f2(float x){
    return exp(-(x*x)/2);
}

float f3(float x){
    return log(1/(1-x));
}

float f4(float x){
    return pow(x, x);
}

int integral(float (*f)(float), double eps, double *sum_r){
    if(eps < 0 || isnan(eps) || isinf(eps)){
        return -1;
    }
    double s_prev = 0, step = 1, sum;
    do{
        s_prev = sum;
        sum = 0;
        for(float x = 0; fabs(x - 1) >= eps; x += step){
            sum += f(x+step/2) * step;
        }
        step /= 2;
    }while(fabs(sum-s_prev) > eps && step > 1e-7);
    if(isinf(sum)){
        return -2;
    }else if(isnan(sum)){
        return -3;
    }
    *sum_r = sum;
    return 1;
}

int main(int argc, char **argv){
    if(argc != 2){
        printf("%s epsilon\n", argv[0]);
        return 0;
    }
    double eps;
    if(float_args_check(argv, &eps) == -1){
        printf("eps must be a positive number\n");
        return 0;
    }
    
    double s1, s2, s3, s4;

    switch(integral(f1, eps, &s1)){
        case -1:{
            printf("invalid eps value\n");
            return 0;
        }
        case -2:{
            printf("first sum overflow\n");
            break;
        }
        case -3:{
            printf("first sum NaN\n");
            break;
        }
        default:{
            printf("first sum = %lf\n", s1);
        }
    }

    switch(integral(f2, eps, &s2)){
        case -2:{
            printf("second sum overflow\n");
            break;
        }
        case -3:{
            printf("second sum NaN\n");
            break;
        }
        default:{
            printf("second sum = %lf\n", s2);
        }
    }

    switch(integral(f3, eps, &s3)){
        case -2:{
            printf("third sum overflow\n");
            break;
        }
        case -3:{
            printf("third sum NaN\n");
            break;
        }
        default:{
            printf("third sum = %lf\n", s3);
        }
    }

    switch(integral(f4, eps, &s4)){
        case -2:{
            printf("fourth sum overflow\n");
            break;
        }
        case -3:{
            printf("fourth sum NaN\n");
            break;
        }
        default:{
            printf("fourth sum = %lf\n", s4);
        }
    }
    
    return 1;
}