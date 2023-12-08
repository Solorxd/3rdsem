#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int sep(char c){
    return c == ' ' || c == '\t' || c == '\n';
}

int func_8(FILE *fi, FILE *fo){
    char c;
    int max_digit, ns;

    do{
        for(;sep(c = fgetc(fi));){
        }

        if(c == EOF){
            return 1;
        }
        else if(!sep(c)){
            c = tolower(c);
            if(!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z'))){
                return 0;
            }
            max_digit = c;
            while((c = fgetc(fi)) != EOF && !sep(c)){
                c = tolower(c);
                if(!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z'))){
                    return 0;
                }
                if(c > max_digit){
                    max_digit = c;
                }
            }
            if(max_digit >= '0' && max_digit <= '9'){
                ns = max_digit - '0' + 1;
            }else{
                ns = max_digit - 'a' + 11;
            }
            if(c == EOF){
                fprintf(fo, "%d", ns);
                return 1;
            }
            else if(sep(c)){
                fprintf(fo, "%d ", ns);
            }
        }

    }while(c != EOF);
    return 1;
}

int main(int argc, char **argv){
    if(argc != 3){
        printf("%s input_file output_file\n",argv[0]);
        return 0;
    }
    FILE *fi = fopen(argv[1], "r");
    FILE *fo = fopen(argv[2], "w");
    if(!fi || !fo){
        printf("file error!\n");
    }
    if(!func_8(fi, fo)){
        printf("wrong data format\n");
    }
    fclose(fi);
    fclose(fo);
}