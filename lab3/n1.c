#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

long long bin_inc(long long *n){
    if(*n == LONG_LONG_MAX)return 0;
    long long i = 1;
    while((*n & i)){
        *n &= ~i;
        i <<= 1;
    }
    *n |= i;
    return *n;
}

long long bin_dec(long long *n){
    if(*n == LONG_LONG_MIN)return 0;
    long long i = 1;
    while(!(*n & i) && i){
        *n |= i;
        i <<= 1;
    }
    *n &= ~i;
    return *n;
}

char* to_bin_power_ns(unsigned r, long long n){
    char *alph = "0123456789abcdefghijklmnopqrstuvwxyz";
    if( r <= 5 && r != 0 ){
        int ns_max_digit = ~(INT_MAX << r);
        long long size = 1;
        char neg_fl = 0;
        if(n < 0){
            n = ~n;
            bin_inc(&n);
            bin_inc(&size);
            neg_fl = 1;
        }
        long long n_cpy = n;
        while(n_cpy){
            n_cpy >>= r;
            bin_inc(&size);
        }
        char *new_num = (char*)malloc(size);
        bin_dec(&size);
        if(neg_fl)new_num[0] = '-';
        for(long long i = bin_dec(&size); i >= neg_fl; bin_dec(&i)){
            new_num[i] = alph[(n & ns_max_digit)];
            n >>= r;
        }
        bin_inc(&size);
        new_num[size] = '\0';
        return new_num;
    }else{
        return (char*)NULL;
    }
}

int main(){
    char *lol;
    lol = to_bin_power_ns(1, 2047);
    printf("%s\n", lol);
    free(lol);
    return 1;
}