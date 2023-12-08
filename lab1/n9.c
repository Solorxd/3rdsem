#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int swap_min_max(unsigned arr_size, int arr[arr_size]){
    unsigned i_max = 0, i_min = 0;
    int max = arr[0], min = arr[0];

    for(unsigned i = 1; i < arr_size; i++){
        if(arr[i] > max){
            max = arr[i];
            i_max = i;
        }else if(arr[i] < min){
            min = arr[i];
            i_min = i;
        }
    }

    arr[i_min] = max;
    arr[i_max] = min;
    return 1; 
}

int main(int argc, char **argv){
    if(argc != 3){
        printf("%s a b\nwhere a < b\n", argv[0]);
        return 0;
    }

            /* Пункт 1 */

    long a, b;
    a = strtol(argv[1], NULL, 10);
    b = strtol(argv[2], NULL, 10);
    if(a > RAND_MAX || a < -RAND_MAX || b > RAND_MAX || b < -RAND_MAX){
        printf("a or b value doesn't fit rand() range\n");
        return 0;
    }else if(a >= b){
        printf("a must be lesser than b\n");
        return 0;
    }

    srand(time(NULL));

    unsigned arr_size = 20;
    int array[arr_size];

    for(unsigned i = 0; i < arr_size; i++){
        array[i] = rand()%(b - a + 1) + a;
    }

    swap_min_max(arr_size, array);

            /* Пункт 2 */

    int *A, *B, *C, d;
    unsigned d_size = 10 + rand()%9991;
    
    A = (int*)malloc(sizeof(int) * d_size);
    B = (int*)malloc(sizeof(int) * d_size);
    C = (int*)malloc(sizeof(int) * d_size);
    if(!A || !B || !C){
        printf("Bad malloc\n");
        return 0;
    }

    for(unsigned i = 0; i < d_size; i++){
        A[i] = rand()%2001 - 1000;
        B[i] = rand()%2001 - 1000;
    }

    for(unsigned i = 0; i < d_size; i++){
        d = RAND_MAX;
        C[i] = 2*A[i];
        for(unsigned j = 0; j < d_size; j++){
            int tmp = B[j] - A[i];
            if(abs(tmp) < abs(d)){
                d = tmp;
            }
        }
        C[i] += d;
    }

    /* Реализация через хэш таблицу
    int *C2;
    C2 = (int*)malloc(sizeof(int) * d_size);
    if(!C){
        printf("Bad malloc\n");
        return 0;
    }
    char hash[2001];
    memset(hash, 0, 2001);
    for(unsigned i = 0; i < d_size; i++){
        hash[B[i] + 1000] = 1;
    }

    for(unsigned i = 0; i < d_size; i++){
        d = 0;
        C2[i] = 2*A[i];
        int j = 0;
        int tmp = A[i] + 1000;
        while(j < 2001){
            if((tmp - j >= 0) && hash[tmp - j]){
                d = -j;
                break;
            }else if((tmp + j <= 2000) && hash[tmp + j]){
                d = j;
                break;
            }
            j++;
        }
        C2[i] += d;
    }


    free(C2);
    */
   free(A);
   free(B);
   free(C);
}