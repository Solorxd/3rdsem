#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

typedef enum{
    WRONG_DOUBLE_VALUE = -1,
    NO,
    YES
}isconvex_results;

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

int vect2d_cmp(const void *v1, const void *v2){
    double product = (((double*)v1)[0] * ((double*)v2)[1] - ((double*)v1)[1] * ((double*)v2)[0]);
    double eps = 1e-8;
    return (product > eps) - (product < -eps);
}

isconvex_results isconvex(unsigned n, ...){
    if(n < 3){
        return 0;
    }else if(n == 3){
        return 1;
    }
    double vertexes[n][2];
    va_list va;
    va_start(va, n);
    double min_y = INFINITY;
    unsigned min_n;

    for(unsigned i = 0; i < n; i++){
        vertexes[i][0] = va_arg(va, double);
        vertexes[i][1] = va_arg(va, double);
        if(isnan(vertexes[i][1]) || isnan(vertexes[i][0]) || isinf(vertexes[i][0]) || isinf(vertexes[i][1])){
            return WRONG_DOUBLE_VALUE;
        }
        if(vertexes[i][1] < min_y){
            min_y = vertexes[i][1];
            min_n = i;
        }
    }

    double vectors_from_miny[n-1][2];
    double tmp_x = vertexes[0][0], tmp_y = vertexes[0][1];

    vertexes[0][0] = vertexes[min_n][0];
    vertexes[0][1] = min_y;
    vertexes[min_n][0] = tmp_x;
    vertexes[min_n][1] = tmp_y;
    for(unsigned i = 0; i < n-1; i++){
        vectors_from_miny[i][0] = vertexes[i+1][0] - vertexes[0][0];
        vectors_from_miny[i][1] = vertexes[i+1][1] - vertexes[0][1];
    }

    qsort(vectors_from_miny, n-1, 2 * sizeof(double), vect2d_cmp);

    for(unsigned i = 0; i < n-1; i++){
        vertexes[i+1][0] = vectors_from_miny[i][0] + vertexes[0][0];
        vertexes[i+1][1] = vectors_from_miny[i][1] + vertexes[0][1]; 
    }

    unsigned count1 = 0, count2 = 0;
    
    for(unsigned i = 0; i < n; i++){
        double v1[2], v2[2];
        v1[0] = vertexes[(i+1)%n][0] - vertexes[i][0];
        v1[1] = vertexes[(i+1)%n][1] - vertexes[i][1];
        v2[0] = vertexes[(i+2)%n][0] - vertexes[(i+1)%n][0];
        v2[1] = vertexes[(i+2)%n][1] - vertexes[(i+1)%n][1];
        int tmp = vect2d_cmp(v1, v2);
        if(tmp > 0){
            count1++;
        }else if(tmp < 0){
            count2++;
        }
    }

    if(count1 == 0 || count2 == 0){
        return YES;
    }
    return NO;
}

int main(){
    printf("%d\n", isconvex(5, -3.0, -1.0, 2.0, 2.0, -3.0, 4.0, 2.0, -2.0, -2.99999, 1.0));
    printf("%d\n", isconvex(5, -3.0, -1.0, 2.0, 2.0, -3.0, 4.0, 2.0, -2.0, -3.00001, 1.0));
    printf("%d\n", isconvex(4, -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0, -1.0));
    printf("%f\n", Polynom(-1.0, 3, 2.0, 5.0, 7.0, 9.0));
    printf("%f\n", Polynom(0, 2.0, 1.0, 2.0, 1.0));
    return 0;
}