#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef enum {
    NULL_STR = 1,
    INT_OVERFLOW,
    UNSIGNED_OVERFLOW,
    FLOAT_OVERFLOW,
    WRONG_FORMAT,
    SUCCESS
} check_results;

int sep(char c){
    return c == ' ' || c == '\t';
}

check_results mystrtol(char *str, long *result){
    if(str == NULL){
        return NULL_STR;
    }
    
    long tmp;
    char ng_fl = 1;
    size_t i = 0;

    for(;sep(i);){i++;}

    if(str[i] >= '0' && str[i] <= '9'){
        tmp = str[i] - '0'; 
    }else if(str[i] == '-'){
        tmp = 0;
        ng_fl = -1;
    }else if(str[i] == '+'){
        tmp = 0;
        ng_fl = 1;
    }else{
        return WRONG_FORMAT;
    }

    i++;

    while(i < SIZE_MAX && str[i] != '\0'){
        if(str[i] >= '0' && str[i] <= '9'){
            if((LONG_MAX - (str[i] - '0'))/10 >= tmp && (LONG_MIN + (str[i] - '0'))/10 <= tmp){
                tmp = tmp*10 + (str[i] - '0') * ng_fl;
            }else{
                return INT_OVERFLOW;
            }
        }else{
            return WRONG_FORMAT;
        }
        i++;
    }
    *result = tmp;
    return SUCCESS;
}

check_results mystrtoll(char *str, long long *result){
    if(str == NULL){
        return NULL_STR;
    }
    
    long long tmp;
    char ng_fl = 1;
    size_t i = 0;

    for(;sep(i);){i++;}

    if(str[i] >= '0' && str[i] <= '9'){
        tmp = str[i] - '0'; 
    }else if(str[i] == '-'){
        tmp = 0;
        ng_fl = -1;
    }else if(str[i] == '+'){
        tmp = 0;
        ng_fl = 1;
    }else{
        return WRONG_FORMAT;
    }

    i++;

    while(i < SIZE_MAX && str[i] != '\0'){
        if(str[i] >= '0' && str[i] <= '9'){
            if((LONG_LONG_MAX - (str[i] - '0'))/10 >= tmp && (LONG_LONG_MIN + (str[i] - '0'))/10 <= tmp){
                tmp = tmp*10 + (str[i] - '0') * ng_fl;
            }else{
                return INT_OVERFLOW;
            }
        }else{
            return WRONG_FORMAT;
        }
        i++;
    }
    *result = tmp;
    return SUCCESS;
}

check_results mystrtoui(char *str, unsigned *result){
    if(str == NULL){
        return NULL_STR;
    }
    
    unsigned tmp;
    size_t i = 0;

    for(;sep(i);){i++;}

    if(str[i] >= '0' && str[i] <= '9'){
        tmp = str[i] - '0'; 
    }else if(str[i] == '+'){
        tmp = 0;
    }else{
        return WRONG_FORMAT;
    }

    i++;

    while(i < SIZE_MAX && str[i] != '\0'){
        if(str[i] >= '0' && str[i] <= '9'){
            if((UINT_MAX - (str[i] - '0'))/10 >= tmp){
                tmp = tmp*10 + (str[i] - '0');
            }else{
                return UNSIGNED_OVERFLOW;
            }
        }else{
            return WRONG_FORMAT;
        }
        i++;
    }
    *result = tmp;
    return SUCCESS;
}

check_results mystrtof(char *str, float *result){
    if(str == NULL){
        return NULL_STR;
    }
    
    float tmp;
    char ng_fl = 1;
    size_t i = 0;

    for(;sep(i);){i++;}

    if(str[i] >= '0' && str[i] <= '9'){
        tmp = str[i] - '0'; 
    }else if(str[i] == '-'){
        tmp = 0;
        ng_fl = -1;
    }else if(str[i] == '+'){
        tmp = 0;
        ng_fl = 1;
    }else{
        return WRONG_FORMAT;
    }

    i++;

    while(i < SIZE_MAX && str[i] != '\0'){
        if(str[i] >= '0' && str[i] <= '9'){
            tmp = tmp*10 + (str[i] - '0') * ng_fl;
        }else if(str[i] == '.' || str[i] == 'e' || str[i] == 'E'){
            break;
        }else{
            return WRONG_FORMAT;
        }
        i++;
    }

     if(str[i] == '.'){
        i++;
        float tmpf = 1;
        while(i < SIZE_MAX && str[i] != '\0'){
            if(str[i] >= '0' && str[i] <= '9'){
                tmpf *= 0.1;
                tmp += (str[i]-'0')*tmpf;
            }else if(str[i] == 'e' || str[i] == 'E'){
                break;
            }
            else{
                return WRONG_FORMAT;
            }
            i++;
        }
    }

    if(str[i] == 'e' || str[i] == 'E'){
        long e;
        switch(mystrtol(str + (i+1), &e)){
            case SUCCESS:{
                tmp *= pow(10, (double)e);
                break;
            }
            case INT_OVERFLOW:{
                return FLOAT_OVERFLOW;
            }
            default:{
                return WRONG_FORMAT;
            }
        }
    }


    *result = tmp;
    return SUCCESS;
}