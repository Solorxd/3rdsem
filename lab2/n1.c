#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include "../args_check.c"

size_t func_l(char* str){
    size_t len = 0;
    for(size_t i = 0; str[i] != '\0'; i++){
        if(len == SIZE_MAX){
            return 0;
        }
        len++;
    }
    return len;
}

char* func_r(char *str){
    size_t len = func_l(str);
    char *str_rev = (char*)malloc((len + 1) * 1);
    if(!str_rev){
        return (char*)NULL;
    }
    for(size_t i = 0; i < len; i++){
        str_rev[i] = str[len-i-1];
    }
    str_rev[len] = '\0';
    return str_rev;
}

char* func_u(char *str){
    size_t len = func_l(str);
    char *new_str = (char*)malloc((len+1) * 1);
    if(!new_str){
        return (char*)NULL;
    }
    for(size_t i = 0; i < len; i++){
        if(i%2 == 1){
            new_str[i] = toupper(str[i]);
        }else{
            new_str[i] = str[i];
        }
    }
    new_str[len] = '\0';
    return new_str;
}

char* func_n(char *str){
    size_t len = func_l(str);
    char *new_str = (char*)malloc((len + 1) * 1);
    if(!new_str){
        return (char*)NULL;
    }
    size_t i_num = 0, i_symb = len-1;
    for(size_t i = 0; i < len; i++){
        if(str[i] >= '0' && str[i] <= '9'){
            new_str[i_num] = str[i];
            i_num++;
        }else{
            new_str[i_symb] = str[i];
            i_symb--;
        }
    }
    char ch_tmp;
    for(size_t i = i_num; i < (len - i_num)/2 + i_num; i++){
        ch_tmp = new_str[i];
        new_str[i] = new_str[len + i_num - i - 1];
        new_str[len + i_num - i - 1] = ch_tmp;
    }
    new_str[len] = '\0';
    return new_str;
}

char* func_c(size_t num, char **m_str, int seed){
    srand(seed);
    size_t len = 0;
    for(size_t i = 0; i < num; i++){
        size_t tmp = func_l(m_str[i]);
        if(SIZE_MAX - tmp < len){
            return (char*)NULL;
        }
        len += tmp;
    }
    char *new_str = (char*)malloc((len + 1) * 1);
    if(!new_str){
        return (char*)NULL;
    }
    size_t i_new = 0, i_rand, i_len;
    size_t rand_m[num];
    for(size_t i = 0; i < num; i++){
        rand_m[i] = i;
    }
    size_t tmp_r, tmp_int;
    for(size_t i = 0; i < num; i++){
        tmp_r = rand()%num;
        tmp_int = rand_m[i];
        rand_m[i] = rand_m[tmp_r];
        rand_m[tmp_r] = tmp_int;
    }
    for(size_t i = 0; i < num; i++){
        i_rand = rand_m[i];
        i_len = func_l(m_str[i_rand]);
        for(size_t j = 0; j < i_len; j++){
            new_str[i_new] = m_str[i_rand][j];
            i_new++;
        }
    }
    new_str[len] = '\0';
    return new_str;
}

int main(int argc, char **argv){

    if(argc < 2){
        printf("%s -option str\noptions:-l str, -r str, -u str, -n str, -c str seed str...\n", argv[0]);
        return 0;
    }
    
    if(strlen(argv[1]) == 2 && argv[1][0] == '-'){
        switch(argv[1][1]){
            case 'l':{
                if(argc != 3){
                    printf("wrong arg amount\n");
                    break;
                }
                int len;
                len = func_l(argv[2]);
                printf("%d\n", len);
                break;
            }
            case 'r':{
                if(argc != 3){
                    printf("wrong arg amount\n");
                    break;
                }
                char *str_rev = func_r(argv[2]);
                printf("%s\n", str_rev);
                free(str_rev);
                break;
            }
            case 'u':{
                if(argc != 3){
                    printf("wrong arg amount\n");
                    break;
                }
                char *new_str = func_u(argv[2]);
                printf("%s\n", new_str);
                free(new_str);
                break;
            }
            case 'n':{
                if(argc != 3){
                    printf("wrong arg amount\n");
                    break;
                }
                char *new_str = func_n(argv[2]);
                printf("%s\n", new_str);
                free(new_str);
                break;
            }
            case 'c':{
                if(argc < 4){
                    printf("wrong arg amount\n");
                    break;
                }
                char *m_str[argc-3];
                m_str[0] = argv[2];
                for(int i = 4; i < argc; i++){
                    m_str[i-3] = argv[i];
                }
                unsigned int seed;
                switch(mystrtoui(argv[3], &seed)){
                    case SUCCESS:{
                        break;
                    }
                    case WRONG_FORMAT:{
                        printf("wrong format\n");
                        return 0;
                    }
                    case UNSIGNED_OVERFLOW:{
                        printf("unsigned overflow\n");
                        return 0;
                    }
                    default:{
                        return 0;
                    }
                }
                char *new_str = func_c(argc-3, m_str, seed);
                printf("%s\n", new_str);
                free(new_str);
                break;
            }
            default:{
                printf("there is no such flag\n");
                break;
            }
        }
    }
}