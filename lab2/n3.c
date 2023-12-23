#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


size_t find_next_str(char *str, FILE *file, size_t *ind_cur, size_t *ind_cur_str, size_t *ind_start_str){
    size_t l = strlen(str);
    char cur_ch;
    size_t ind_start = 0;
    while((cur_ch = getc(file)) != EOF){
        (*ind_cur)++;
        if(cur_ch == str[0]){
            char fl = 1;
            ind_start = *ind_cur;
            size_t tmp_start_str = *ind_cur_str;
            for(size_t i = 1; i < l; i++){
                cur_ch = getc(file);
                (*ind_cur)++;
                if(cur_ch != str[i]){
                    fl = 0;
                    break;
                }else if(cur_ch == EOF){
                    return 0;
                }
                if(cur_ch == '\n'){
                   (*ind_cur_str)++;
                   *ind_cur = 0;
                }
            }
            if(fl){
                *ind_start_str = tmp_start_str;
                return ind_start;
            }
        }
        if(cur_ch == '\n'){
            (*ind_cur_str)++;
            *ind_cur = 0;
        }
    }
    return 0;
}

int files_count_str(char* str, size_t num, ...){
    va_list name;
    va_start(name, num);
    FILE *file;
    size_t result;
    size_t ind_cur, ind_cur_str, result_line;
    for(size_t i = 0; i < num; i++){
        char *name_f = va_arg(name, char*);
        file = fopen(name_f, "r");
        if(!file){
            printf("can't open file %s\n", name_f);
            continue;
        }
        printf("file %s:\n", name_f);
        ind_cur = 0;
        ind_cur_str = 1;
        while((result = find_next_str(str, file, &ind_cur, &ind_cur_str, &result_line))){
            printf("\tline = %lld : start = %lld\n", result_line, result);           
        }
        fclose(file);
    }
    va_end(name);
    return 1;
}

int main(int argc, char **argv){
    if(argc < 3){
        printf("%s str files...", argv[0]);
        return 0;
    }
    
    files_count_str(argv[1], 2, argv[2], argv[3]);
    return 1;
}