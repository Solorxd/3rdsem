#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int sep(char c){
    return c == ' ' || c == '\t' || c == '\n';
}

void fputrec(char c,FILE* fo,unsigned int base){
    if(c/base)fputrec(c/base, fo, base);
    fputc(c%base + '0', fo);
}

int fputLataskii(char c, FILE *fo, unsigned int base){
    if(base > 10){
        return 0;
    }
    if(!fo){
        return 0;
    }
    if(c >= 'A' && c <= 'Z'){
        fputrec(c, fo, base);
    }else{
        fputc(c, fo);
    }
    return 1;
}

int func_r(FILE *f1, FILE *f2, FILE *f){
    if(!f1 || !f2 || !f){
        return 0;
    }
    char c = 0;
    int f1_eof = 0, f2_eof = 0;
    while(!(f1_eof && f2_eof)){
        if(!f1_eof){

        for(;sep(c = fgetc(f1));){
        }

        if(c == EOF){
            fputc(' ', f);
            f1_eof = 1;
        }
        else if(!sep(c)){
            fputc(c, f);
            while((c = fgetc(f1)) != EOF && !sep(c)){
                fputc(c, f);
            }
            if(c == EOF){
                fputc(' ', f);
                f1_eof = 1;
            }
            else if(sep(c)){
                fputc(' ', f);
            }
        }

        }

        if(!f2_eof){

        for(;sep(c = fgetc(f2));){
        }

        if(c == EOF){
            fputc(' ', f);
            f2_eof = 1;
        }
        else if(!sep(c)){
            fputc(c, f);
            while((c = fgetc(f2)) != EOF && !sep(c)){
                fputc(c, f);
            }
            if(c == EOF){
                fputc(' ', f);
                f2_eof = 1;
            }
            else if(sep(c)){
                fputc(' ', f);
            }
        }

        }
    }
    return 1;
}

int func_a(FILE *fi, FILE *fo){
    if(!fi || !fo){
        return 0;
    }
    char c;
    unsigned char count = 1;

    do{
        for(;sep(c = fgetc(fi));){}
        if(c == EOF){
            return 1;
        }
        else if(!sep(c)){
            if(count == 10){
                fputLataskii(toupper(c), fo, 4);
                while((c = fgetc(fi)) != EOF && !sep(c)){
                    fputLataskii(toupper(c), fo, 4);
                }
                count = 1;
            }else if(count%5 == 0){
                fputLataskii(toupper(c), fo, 8);
                while((c = fgetc(fi)) != EOF && !sep(c)){
                    fputLataskii(toupper(c), fo, 8);
                }
                count++;
            }else if(count%2 == 0){
                fputc(toupper(c), fo);
                while((c = fgetc(fi)) != EOF && !sep(c)){
                    fputc(toupper(c), fo);
                }
                count++;
            }else{
                fputc(c, fo);
                while((c = fgetc(fi)) != EOF && !sep(c)){
                    fputc(c, fo);
                }
                count++;
            }
            if(c == EOF){
                return 1;
            }
            else if(sep(c)){
                fputc(' ', fo);
            }
        }
    }while(c != EOF);
    return 1;
}

int main(int argc, char **argv){
    if(argc >= 2){
    switch ((strcmp(argv[1], "-r") == 0) + 2*(strcmp(argv[1], "-a") == 0)){
        case 0:{
            printf("wrong key\n");
            break;
        }
        case 1:{
            if(argc != 5){
                printf("wrong arg amount\n");
                break;
            }
            FILE *f1 = fopen(argv[2], "r");
            FILE *f2 = fopen(argv[3], "r");
            FILE *f = fopen(argv[4], "w");
            if(!func_r(f1, f2, f)){
                printf("file error\n");
            }
            fclose(f1);
            fclose(f2);
            fclose(f);
            break;
        }
        case 2:{
            if(argc !=4){
                printf("wrong arg amount\n");
                break;
            }
            FILE *fi = fopen(argv[2], "r");
            FILE *fo = fopen(argv[3], "w");
            if(!func_a(fi, fo)){
                printf("file error\n");
            }
            fclose(fi);
            fclose(fo);
            break;
        }
    }
    }else{
        printf("wrong arg amount\n");
    }
}