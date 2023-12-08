#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_prime(unsigned long long num){   
    if (num == 2){
        return 1;
    }
    else if(num == 1 || num == 0){
        return 0;
    }

    for (int i = 2; i < sqrt(num) + 1; i++){
        if(num%i == 0)return 0;
    }
    
    return 1;
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

double lim_e(unsigned long long n){
    if(!n){
        return 1;
    }
    return pow((1 + 1/(double)n), (double)n);
}

double lim_pi(unsigned long long n){
    if(!n){
        return 1;
    }
    static double factorial = 1;
    static double factorial2n = 1;
    factorial *= (double)n;
    factorial2n *= 2*(double)n*(2*(double)n - 1);
    return pow((pow(2, (double)n) * factorial), 4)/((double)n * factorial2n * factorial2n);
}

double lim_ln2(unsigned long long n){
    if(!n){
        return 0;
    }
    return (double)n * (pow(2, 1/(double)n) - 1);
}

double lim_sqrt2(unsigned long long n){
    if(!n){
        return -0.5;
    }
    static double x = -0.5;
    x = x - (x*x)/2 + 1;
    return x;
}

double lim_gamma(unsigned long long n){
    if(n == 0){
        return 0;
    }

    double result;

    static double row = 0;

    row += 1/(double)n;

    /*double factorials[n+1];
    factorials[0] = 1;
    double result = 0;

    for(unsigned long long i = 1; i <= n; i++){
        factorials[i] = factorials[i-1] * (double)i;
    }

    for(unsigned long long k = 1; k <= n; k++){
        if(k%2 == 0){
            result += ((factorials[n]/(factorials[k]*factorials[n-k])) * log(factorials[k])) / (double)k;
        }else{
            result -= ((factorials[n]/(factorials[k]*factorials[n-k])) * log(factorials[k])) / (double)k;
        }
    }*/

    result = row - log(n);

    return result;
}

double row_e(unsigned long long n){
    if(!n){
        return 1;
    }
    static double factorial = 1;
    factorial *= (double)n;
    return 1/factorial;
}

double row_pi(unsigned long long n){
    if(!n){
        return 0;
    }else if((n-1)%2 == 0){
        return 4.0/(2*(double)n - 1);
    }else{
        return -4.0/(2*(double)n - 1);
    }
}

double row_ln2(unsigned long long n){
    if(!n){
        return 0;
    }else if((n-1)%2 == 0){
        return 1.0/(double)n;
    }else{
        return -1.0/(double)n;
    }
}

double row_sqrt2(unsigned long long n){
    if(n == 0 || n == 1){
        return 1;
    }
    double x = pow(2, pow(2, -(double)n));
    return x;
}

double row_gamma(unsigned long long n){
    if(n == 0){
        return 0;
    }else if(n == 1){
        return -pow(3.14159265358979323846, 2)/6;
    }
    double tmp = floor(sqrt((double)n));
    return 1.0/(tmp*tmp) - 1.0/(double)n;
}

double dih_e(double x){
    return log(x) - 1;
}

double dih_pihalved(double x){
    return 1/tan(x);
}

double dih_ln2(double x){
    return exp(x) - 2;
}

double dih_sqrt2(double x){
    return x*x - 2;
}

double plus(double n1, double n2){
    return n1 + n2;
}

double composition(double n1, double n2){
    return n1 * n2;
}

double tmplim_for_gamma(unsigned long long n){
    double result = 1;
    for(unsigned long long i = 2; i <= n; i++){
        if(is_prime(i))result *= ((double)i - 1)/(double)i;
    }
    result *= log((double)n);
    return result;
}

double count_with_row(double (*f)(unsigned long long), double (*operation)(double, double), double operation_neutral_el, double eps){
    double row_element;
    double result = operation_neutral_el;
    for(unsigned long i = 0; (i < ULONG_MAX/2) && ((fabs((row_element = f(i)) - operation_neutral_el) > eps) || (fabs(result - operation_neutral_el) <= __DBL_EPSILON__) || fabs(row_element - operation_neutral_el) <= __DBL_EPSILON__) && !isnan(row_element) && !isinf(row_element); i++){
        result = operation(result, row_element);
    }
    return result;
}

double count_with_lim(double (*f)(unsigned long long), double eps){
    double prev, cur = f(0);
    unsigned long long n = 1;
    do{
        prev = cur;
        cur = f(n++);
    }while(fabs(cur - prev) >= eps && n < ULONG_MAX/2 && !isnan(cur) && !isinf(cur));
    if(isnan(cur) || isinf(cur)){
        return prev;
    }
    return cur;
}

double dih_gamma(double x){
    static double lim = 0;
    if(!lim){
        lim = count_with_lim(tmplim_for_gamma, 1e-5);
    }
    return exp(-x) - lim;
}

int main(int argc, char **argv){
    if(argc != 2){
        printf("%s epsilon\n", argv[0]);
        return 0;
    }
    double eps = strtof(argv[1], NULL);

    if(eps <= __DBL_EPSILON__){
        printf("wrong epsilon value");
        return 0;
    }

    printf("Limits:\n");
    printf("\te = %lf\n", count_with_lim(lim_e, eps));
    printf("\tpi = %lf\n", count_with_lim(lim_pi, eps));
    printf("\tln2 = %lf\n", count_with_lim(lim_ln2, eps));
    printf("\tsqrt2 = %lf\n", count_with_lim(lim_sqrt2, eps));
    printf("\tgamma = %lf\n", count_with_lim(lim_gamma, eps));

    printf("Rows/Compositons:\n");
    printf("\te = %lf\n", count_with_row(row_e, plus, 0.0, eps));
    printf("\tpi = %lf\n", count_with_row(row_pi, plus, 0.0, eps));
    printf("\tln2 = %lf\n", count_with_row(row_ln2, plus, 0.0, eps));
    printf("\tsqrt2 = %lf\n", count_with_row(row_sqrt2, composition, 1.0, eps));
    printf("\tgamma = %lf\n", count_with_row(row_gamma, plus, 0.0, eps));

    printf("dih:\n");
    printf("\te = %lf\n", dih(2, 3, eps, dih_e));
    printf("\tpi = %lf\n", 2*dih(1, 3, eps, dih_pihalved));
    printf("\tln2 = %lf\n", dih(0, 1, eps, dih_ln2));
    printf("\tsqrt2 = %lf\n", dih(1, 2, eps, dih_sqrt2));
    printf("\tgamma = %lf\n", dih(0, 1, eps, dih_gamma));

    return 1;
}