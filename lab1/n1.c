#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../args_check.c"

int argum(char **astr, char *mode, long *num){
    int fl1 = -2, fl2 = -1;

    if((astr[2][0] == '-' || astr[2][0] == '/') && strlen(astr[2]) == 2){
        *mode = astr[2][1];
        fl1 = 0;
    }
    switch(mystrtol(astr[1], num)){
        case SUCCESS:{
            fl2 = 0;
            break;
        }
        default:{
            break;
        }
    }
    
    return fl1 + fl2;
}

int is_prime(unsigned long num){
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

void printdigits(unsigned long num){
    if(num){
        if(num/10){
            printdigits(num/10);
        }
        printf("%ld ", num%10);
    }
}

unsigned long long factorialf(long num){
    unsigned long long tmp = 1;
    for(long i = 2; i <= num; i++){
        if(ULONG_LONG_MAX/i > tmp){
            tmp *= i;
        }else{
            return 0;
        }
    }
    return tmp;
}


int main(int argc, char **argv){

    if(argc != 3){
        printf("wrong argument amount\n");
        return 0;
    }

    char mode;
    long num;
    
    switch(argum(argv, &mode, &num)){
        case -1:{
            printf("int overflow\n");
            return 0;
        }
        case -2:{
            printf("no key detected\n");
            return 0;
        }
        case -3:{
            printf("wrong arguments\n");
            return 0;
        }
    }


    switch(mode){
        case 'h': {
            int n = 0;
            if(abs(num) > 100)
            {
                printf("no numbers found\n");
                break;
            }else if (num == 0)
            {
                printf("cant divide by zero!\n");
                break;
            }
            
            for(int i = 1; i <= 100; i++){
                if(i%num == 0){
                    printf("%d  ", i);
                    n++;
                    if(n%10 == 0 && i != 100){
                        printf("\n");
                    }
                }
            }
            printf("\n");
            break;
        }
        case 'p': {
            if(num < 0){
                printf("the number is not natural\n");
                break;
            }
            int res = is_prime(num);
            if(res){
                printf("the number %ld is prime\n", num);
            }else{
                printf("the number %ld is not prime\n", num);
            }
            break;
        }
        case 's': {
            if(num < 0){   
                printf("- ");
                printdigits(abs(num));
                printf("\n");
            }else{
                printdigits(num);
                printf("\n");
            }
            break;
        }
        case 'e': {
            if(num < 1 || num > 10){
                printf("invalid power value\n");
                break;
            }

            for (int i = 1; i <= num; i++){
                
                printf("%d\t", i);
            }
            printf("\n");
            for (int i = 1; i < 11; i++){   
                long long cur_v = i;
                for (int j = 1; j <= num; j++){   
                    printf("%lld\t", cur_v);
                    if(j != num)cur_v *= i;
                }
                printf("\n");
            }
            
            break;
        }
        case 'a': {
            if(num < 1){
                printf("invalid value\n");
                break;
            }
            printf("%lld\n", (long long)num*(1+num)/2);
            break;
        }
        case 'f': {
            if(num < 0){
                printf("number is negative\n");
                break;
            }
            long long tmp_f = factorialf(num);
            if(tmp_f){
                printf("%llu\n", tmp_f);
            }else{
                printf("long long overflow\n");
            }
            break;
        }
        default:{
            printf("there is no such key\n");
            break;
        }
    }

    return 1;
}