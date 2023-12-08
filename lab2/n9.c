#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

int check_fraction_ns(unsigned base, double dec){
    if(base % 10 == 0){
        return 1;
    }else if(base % 2 == 0){
        double d = 0;
        while(!(modfl((long double)fabs(dec), (long double*)NULL) < __DBL_EPSILON__)){
            dec *= 10;
            d++;
        }
        dec = dec/pow(5.0, d);
        return (modfl((long double)fabs(dec), (long double*)NULL) < __DBL_EPSILON__);
    }else if(base % 5 == 0){
        double d = 0;
        while(!(modfl((long double)fabs(dec), (long double*)NULL) < __DBL_EPSILON__)){
            dec *= 10;
            d++;
        }
        dec = dec/pow(2.0, d);
        return (modfl((long double)fabs(dec), (long double*)NULL) < __DBL_EPSILON__);
    }
    return 0;
}

int check_multiple_fraction_ns(unsigned base, int n, ...){
    va_list va;
    va_start(va, n);
    if(base < 2){
        printf("wrong base : %u\n", base);
        return -1;
    }
    for(int i = 0; i < n; i++){
        double dec = va_arg(va, double);

        if(isnan(dec) || isinf(dec)){
            printf("wrong decimal fraction(fraction number %d)\n", i+1);
            continue;
        }

        if(dec >= 1){
            printf("%f is greater than 1\n", dec);
            continue;
        }else if(dec <= 0){
            printf("%f is lesser than 0\n", dec);
            continue;
        }
        
        if(check_fraction_ns(base, dec)){
            printf("%e can be represented as final fraction in base = %d\n", dec, base);
        } else{
            printf("%e can not be represented as final fraction in base = %d\n", dec, base);
        }
    }
    return 1;
}

int main(){
    check_multiple_fraction_ns(5, 3, 0.3, 0.0625, 0.2);
    return 0;
}