#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>

int func_l(char* str){
    int len = 0;
    for(int i = 0; str[i] != '\0'; i++){
        len++;
    }
    return len;
}

char* func_r(char *str){
    int len = func_l(str);
    char *str_rev = (char*)malloc((len + 1) * 1);
    if(!str_rev){
        return (char*)NULL;
    }
    for(int i = 0; i < len; i++){
        str_rev[i] = str[len-i-1];
    }
    str_rev[len] = '\0';
    return str_rev;
}

char* func_u(char *str){
    int len = func_l(str);
    char *new_str = (char*)malloc((len+1) * 1);
    if(!new_str){
        return (char*)NULL;
    }
    for(int i = 0; i < len; i++){
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
    int len = func_l(str);
    char *new_str = (char*)malloc((len + 1) * 1);
    if(!new_str){
        return (char*)NULL;
    }
    int i_num = 0, i_symb = len-1;
    for(int i = 0; i < len; i++){
        if(str[i] >= '0' && str[i] <= '9'){
            new_str[i_num] = str[i];
            i_num++;
        }else{
            new_str[i_symb] = str[i];
            i_symb--;
        }
    }
    char ch_tmp;
    for(int i = i_num; i < (len - i_num)/2 + i_num; i++){
        ch_tmp = new_str[i];
        new_str[i] = new_str[len + i_num - i - 1];
        new_str[len + i_num - i - 1] = ch_tmp;
    }
    new_str[len] = '\0';
    return new_str;
}

char* func_c(int num, char **m_str, int seed){
    srand(seed);
    int len = 0;
    for(int i = 0; i < num; i++){
        len += func_l(m_str[i]);
    }
    char *new_str = (char*)malloc((len + 1) * 1);
    if(!new_str){
        return (char*)NULL;
    }
    int i_new = 0, i_rand, i_len;
    int rand_m[num];
    for(int i = 0; i < num; i++){
        rand_m[i] = i;
    }
    int tmp_r, tmp_int;
    for(int i = 0; i < num; i++){
        tmp_r = rand()%num;
        tmp_int = rand_m[i];
        rand_m[i] = rand_m[tmp_r];
        rand_m[tmp_r] = tmp_int;
    }
    for(int i = 0; i < num; i++){
        i_rand = rand_m[i];
        i_len = func_l(m_str[i_rand]);
        for(int j = 0; j < i_len; j++){
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
                long long tmp_l = strtoll(argv[3], NULL, 10);
                if(tmp_l > 4294967295 || tmp_l < 0){
                    printf("wrong unsigned int value\n");
                    break;
                }
                unsigned int seed = (unsigned int)tmp_l;
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