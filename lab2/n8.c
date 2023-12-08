#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

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

char* column_addition(const char* number1, const char* number2, int base){
    size_t len1 = strlen(number1), len2 = strlen(number2);
    size_t len = (len1 > len2) ? len1 : len2;
    if(len > 200){
        return (char*)NULL;
    }
    static char result[200 + 1];
    result[len+1] = '\0';
    int dig1, dig2;
    unsigned char plusone = 0;

    if(base > 36 || base < 2){
        return (char*)NULL;
    }

    for(size_t i = 0; i < len ; i++){
        int tmpdigit = (int)plusone;
        plusone--;
        if(i < len1){
            if((dig1 = chartodigit(number1[len1 - i - 1])) >= base || dig1  == -1 || dig1 >= base){
                return (char*)NULL;
            }
            tmpdigit += dig1;
        }

        if(i < len2){
            if((dig2 = chartodigit(number2[len2 - i - 1])) >= base || dig2  == -1 || dig2 >= base){
                return (char*)NULL;
            }
            tmpdigit += dig2;
        }

        plusone = tmpdigit/base;
        tmpdigit %= base;

        if(tmpdigit < 10){
            result[len - i] = tmpdigit + '0';
        }else{
            result[len - i] = tmpdigit + 'a' - 10;
        }
        
    }

    if(plusone){
        result[0] = '1';
        return result;
    }else{
        return result + 1;
    }
}

char *my_summ(int base, unsigned n, ...){
    char *summ;
    va_list va;
    va_start(va, n);
    if(n == 0){
        return (char*)NULL;
    }
    summ = column_addition(va_arg(va, char*), "0", base);
    for(unsigned i = 1; (i < n) && summ; i++){
        summ = column_addition(summ, va_arg(va, char*), base);
    }
    return summ;
}

int main(){
    char *res;
    res = my_summ(24, 3, "1abc", "100ddd1", "1000hfgg1");
    printf("%s", res);
    return 1;
}