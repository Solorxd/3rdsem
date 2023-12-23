#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef enum {
    BAD_MALLOC = -1,
    WRONG_DOUBLE_VALUE,
    OK
}results;

int sep(char c){
    return c == ' ' || c == '\t';
}

int new_func(double eps, double a, double **G, unsigned n, ...){
    if(eps < 0){
        return 0;
    }
    va_list va;
    va_start(va, n);
    double *Gtmp = (double*)malloc( sizeof(double) * (n+1) );
    if(!Gtmp){
        return BAD_MALLOC;
    }
    va_end(va);
    long long factorios[n+1];
    double A[n+1];
    A[0] = 1;
    factorios[0] = 1;
    a = -a;
    for(unsigned i = 1; i <= n; i++){
        factorios[i] = factorios[i-1] * i;
        A[i] = A[i-1] * a;
    }
    for(unsigned i = n;; i--){
        Gtmp[n-i] = va_arg(va, double);
        if(isinf(Gtmp[n-i]) || isnan(Gtmp[n-i])){
            free(Gtmp);
            return WRONG_DOUBLE_VALUE;
        }
        for(unsigned k = i+1; k <= n; k++){
            Gtmp[n-i] -= (factorios[k]/(factorios[k-i] * factorios[i]) * A[k-i] * Gtmp[n-k]);
        }
        if(i == 0){
            break;
        }
    }
    *G = Gtmp;
    return OK;
}

int main(){
    double *G;
    int n = 3;
    new_func(1e-8, -2, &G, n, -5.0, 7.0, 1.0, -3.0);
    for(int i = 0; i <= n; i++){
        printf("%f\n", G[i]);
    }
    free(G);
    return 0;
}