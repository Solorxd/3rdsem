#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int chartodigit(char c){
    if(c >= '0' && c <= '9'){
        return c - '0';
    }else if(c >= 'a' && c <= 'z'){
        return c - 'a' + 10;
    }else if(c >= 'A' && c <= 'Z'){
        return c - 'A' + 10;
    }else{
        return -1;
    }
}

int printnumberbase(long n, int base){
    char *alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";
    char longchar[100];
    if(n < 0){
        printf("-");
        n = -n;
    }
    int i = 0;
    while(n){
        longchar[i] = alphabet[n%base];
        n /= base;
        i++;
    }
    while(i > 0)printf("%c", longchar[--i]);
    printf("\n");
    return 1;
}

int func_10(){
    char ans[100];
    char stop_fl = 1;
    long number, max_number;
    int ns = 0;
    printf("input number system:");
    fgets(ans, 100, stdin);
    for(int i = 0; ans[i] != '\n' && ans[i] != '\0'; i++){
        if(ans[i] >= '0' && ans[i] <= '9'){
            ns = ns*10 + ans[i] - '0';
        }else{
            ns = -1;
            break;
        }
    }
    if(ns > 36 || ns < 2){
        printf("invalid number system\n");
        return -1;
    }
    do{
        printf(">");
        fgets(ans, 100, stdin);
        if(ans[0] == 'S' && ans[1] == 't' && ans[2] == 'o' && ans[3] == 'p' && ans[4] == '\n'){
            stop_fl = 0;
        }else{
            number = 0;
            char fl = 1;
            if(ans[0] != '-'){

                for(int i = 0; ans[i] != '\n' && ans[i] != '\0'; i++){
                    int tmpdigit = chartodigit(ans[i]);

                    if(tmpdigit < ns && tmpdigit >= 0){

                        if((LONG_MAX - (long)tmpdigit)/(long)ns < number){
                            printf("long overflow\n");
                            fl = 0;
                            break;
                        }

                        number = number*ns + tmpdigit;
                    }else{

                        printf("wrong number format\n");
                        fl = 0;
                        break;

                    }
                }
                
            }else{

                for(int i = 1; ans[i] != '\n' && ans[i] != '\0'; i++){
                    int tmpdigit = chartodigit(ans[i]);

                    if(tmpdigit < ns && tmpdigit >= 0){
                        if(((LONG_MIN + tmpdigit)/(long)ns) > number){
                            printf("long overflow\n");
                            fl = 0;
                            break;
                        }

                        number = number*ns - tmpdigit;
                    }else{

                        printf("wrong number format\n");
                        fl = 0;
                        break;
                        
                    }
                }

            }

            if(fl){
                if(number > max_number){
                    max_number = number;
                }
            }
        }
    }while(stop_fl);

    printnumberbase(max_number, 9);
    printnumberbase(max_number, 18);
    printnumberbase(max_number, 27);
    printnumberbase(max_number, 36);

    return 1;
}

int main(){
    func_10();
    return 1;
}