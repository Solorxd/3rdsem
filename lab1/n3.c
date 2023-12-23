#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../args_check.c"

check_results float_args_check(char **argv, float *eps, float *a, float *b, float *c){
    check_results r;
    switch(r = mystrtof(argv[2],eps)){
        case SUCCESS:{break;}
        default:{
            return r;
        }
    }
    switch(r = mystrtof(argv[3],a)){
        case SUCCESS:{break;}
        default:{
            return r;
        }
    }
    switch(r = mystrtof(argv[4],b)){
        case SUCCESS:{break;}
        default:{
            return r;
        }
    }
    switch(r = mystrtof(argv[5],c)){
        case SUCCESS:{break;}
        default:{
            return r;
        }
    }
    return SUCCESS;
}

int opts(char **argv, char *f){
    if(strlen(argv[1]) == 2 && (argv[1][0] == '-' || argv[1][0] == '/')){
        *f = argv[1][1];
        return 1;
    }
    return 0;
}

int polynom2(float eps, float a, float b, float c, float *x1, float *x2){
    float D = pow(b,2) - 4*a*c;
    if(fabs(a) <= eps && fabs(b) <= eps){
        return -2;
    }else if(fabs(a) <= eps){
        *x1 = -c/b;
        if(fabs(*x1) <= eps)*x1 = 0;
        return -1;
    }
    if(fabs(D) <= eps){
        *x1 = (-b)/(2*a);
        if(fabs(*x1) <= eps)*x1 = 0;
        return 1;
    }else if(D > eps){
        *x1 = (-b + sqrt(D))/(2*a);
        *x2 = (-b - sqrt(D))/(2*a);
        if(fabs(*x1) <= eps)*x1 = 0;
        if(fabs(*x2) <= eps)*x2 = 0;
        return 2;
    }else{
        return 0;
    }
}

int func_q(float eps, float a, float b, float c, float *x1, float *x2){
    int xn = polynom2(eps, a, b, c, x1, x2);
    switch (xn){
    case -2:{
        printf("invalid equation: %.3f = 0\n", c);
        break;
    }
    case -1:{
        if(!isinf(fabs(*x1))){
            printf("the root of the polynom: %.3fx + (%.3f) = 0 - is:\nx1 = %.3f\n", b, c, *x1);
        }else{
            printf("root float value overflow!\n");
        }
        break;
    }
    case 0:{
        printf("the polynom: %.3fx^2 + (%.3f)x + (%.3f) = 0 - has no real roots\n", a, b, c);
        break;
    }
    case 1:{
        if(!isinf(fabs(*x1))){
            printf("the polynom: %.3fx^2 + (%.3f)x + (%.3f) = 0 - has only 1 root:\nx1 = %.3f\n", a, b, c, *x1);
        }else{
            printf("root float value overflow!\n");
        }
        break;
    }
    case 2:{
        if(isinf(fabs(*x1)) && isinf(fabs(*x2))){
            printf("both roots float value overflow\n");
        }else if(isinf(fabs(*x1))){
            printf("one of the roots float overflow error\nThe other root of the polynom: %.3fx^2 + (%.3f)x + (%.3f) = 0 - is %.3f\n", a, b, c, *x2);
        }else if(isinf(fabs(*x2))){
            printf("one of the roots float overflow error\nThe other root of the polynom: %.3fx^2 + (%.3f)x + (%.3f) = 0 - is %.3f\n", a, b, c, *x1);
        }else{
            printf("the roots of the polynom: %.3fx^2 + (%.3f)x + (%.3f) = 0 - are:\nx1 = %.3f ; x2 = %.3f\n", a, b, c, *x1, *x2);
        }
        break;
    }
    }
    return 1;
}

int func_m(int n1, int n2){
    return n1%n2 == 0;
}

int func_t(float eps, float AB, float BC, float AC){
    return (fabs(AB*AB + BC*BC - AC*AC) < eps) || (fabs(AB*AB + AC*AC - BC*BC) < eps) || (fabs(BC*BC + AC*AC - AB*AB) < eps);
}


int main(int argc, char **argv){
    char fl;

    if(argc < 2){
        printf("no key detected\n");
        return 0;
    }

    if(!opts(argv, &fl)){
        printf("no key detected\n");
    }else{
    switch(fl){
        case 'q':{
            if(argc == 6){
                float eps, a, b, c;
                switch(float_args_check(argv, &eps, &a, &b, &c)){
                    case FLOAT_OVERFLOW:{
                        printf("float overflow\n");
                        return 0;
                    }
                    case WRONG_FORMAT:{
                        printf("wrong format\n");
                        return 0;
                    }
                    case SUCCESS:{
                        break;
                    }
                    default:{
                        return 0;
                    }
                }
            }else{
                printf("wrong arguments amount for this key\n");
            }
            if(eps < 0){
                printf("eps must be a positive number\n");
            }
            int e1, e2, e3;
            e1 = (fabs(a - b) <= eps);
            e2 = (fabs(a - c) <= eps);
            e3 = (fabs(c - b) <= eps);
            float x[12];
            if(e1 && e2){
                func_q(eps, a, a, a, &x[0], &x[1]);
            }else if(e1){
                func_q(eps, a, a, c, &x[0], &x[1]);
                func_q(eps, a, c, a, &x[2], &x[3]);
                func_q(eps, c, a, a, &x[4], &x[5]);
            }else if(e2){
                func_q(eps, a, a, b, &x[0], &x[1]);
                func_q(eps, a, b, a, &x[2], &x[3]);
                func_q(eps, b, a, a, &x[4], &x[5]);
            }else if(e3){
                func_q(eps, b, b, a, &x[0], &x[1]);
                func_q(eps, b, a, b, &x[2], &x[3]);
                func_q(eps, a, b, b, &x[4], &x[5]);
            }else{
                func_q(eps, a, b, c, &x[0], &x[1]);
                func_q(eps, a, c, b, &x[2], &x[3]);
                func_q(eps, b, a, c, &x[4], &x[5]);
                func_q(eps, b, c, a, &x[6], &x[7]);
                func_q(eps, c, a, b, &x[8], &x[9]);
                func_q(eps, c, b, a, &x[10], &x[11]);
            }
            break;
        }
        case 'm':{
            if(argc == 4){
                long n1, n2;
                switch(mystrtol(argv[2], &n1)){
                    case INT_OVERFLOW:{
                        printf("long overflow\n");
                        return 0;
                    }
                    case WRONG_FORMAT:{
                        printf("wrong format\n");
                        return 0;
                    }
                    case SUCCESS:{
                        break;
                    }
                    default:{
                        return 0;
                    }
                }
                switch(mystrtol(argv[3], &n2)){
                    case INT_OVERFLOW:{
                        printf("long overflow\n");
                        return 0;
                    }
                    case WRONG_FORMAT:{
                        printf("wrong format\n");
                        return 0;
                    }
                    case SUCCESS:{
                        break;
                    }
                    default:{
                        return 0;
                    }
                }
                if(n2 == 0){
                    printf("cant divide by zero\n");
                }else{
                    if(func_m(n1, n2)){
                        printf("%ld is a multiple of %ld", n1, n2);
                    }else{
                        printf("%ld is not a multiple of %ld", n1, n2);
                    }
                }
            }else{
                printf("wrong arguments amount for this key\n");
            }
            break;
        }
        case 't':{
            if(argc == 6){
                float eps, AB, BC, AC;
                switch(float_args_check(argv, &eps, &AB, &BC, &AC)){
                    case FLOAT_OVERFLOW:{
                        printf("float overflow\n");
                        return 0;
                    }
                    case WRONG_FORMAT:{
                        printf("wrong format\n");
                        return 0;
                    }
                    case SUCCESS:{
                        if(eps < 0){
                            printf("eps must be a positive number\n");
                        }
                        if(func_t(eps, AB, BC, AC)){
                            printf("there is right triangle with the sides: %.3f  %.3f  %.3f\n", AB, BC, AC);
                        }else{
                            printf("there is no right triangle with the sides: %.3f  %.3f  %.3f\n", AB, BC, AC);
                        }
                        break;
                    }
                    default:{
                        return 0;
                    }
                }
            }else{
                printf("wrong arguments amount for this key\n");
            }
            break;
        }
        default:{
            printf("there is not such key\n");
        }
    }
    }
    return 1;
}