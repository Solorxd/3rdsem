#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int opts(int argc, char **argv, char *f1, char *f2){
    if(strlen(argv[1]) == 3 && (argv[1][0] == '-' || argv[1][0] == '/') && argc == 4){
        if(argv[1][1] != 'n'){
            return 0;
        }
        *f1 = argv[1][1];
        *f2 = argv[1][2];
        return 2;
    }else if(strlen(argv[1]) == 2 && (argv[1][0] == '-' || argv[1][0] == '/') && argc == 3){
        *f2 = argv[1][1];
        *f1 = '\0';
        return 1;
    }
    return 0;
}

int func_d(FILE *in, FILE *out){
    char cur;
    while((cur = fgetc(in)) != EOF){
        if(cur < '0' || cur > '9'){
            fputc(cur, out);
        }
    }
    return 1;
}   

int func_i(FILE *in, FILE *out){
    char cur;
    int kolvo_lat = 0;
    while((cur = fgetc(in)) != EOF){
        if(cur == '\n'){
            fprintf(out , "%d", kolvo_lat);
            fputc(cur, out);
            kolvo_lat = 0;
        }else if((cur >= 'A' && cur <= 'Z') || (cur >= 'a' && cur <= 'z')){
            kolvo_lat++;
        }
    }
    fprintf(out , "%d", kolvo_lat);
    return 1;
}

int func_s(FILE *in, FILE *out){
    char cur;
    int kolvo_notlatnum = 0;
    while((cur = fgetc(in)) != EOF){
        if(cur == '\n'){
            fprintf(out , "%d", kolvo_notlatnum);
            fputc(cur, out);
            kolvo_notlatnum = 0;
        }else if((cur < 'A' || cur > 'Z') && (cur < 'a' || cur > 'z') && (cur < '0' || cur > '9') && cur != ' '){
            kolvo_notlatnum++;
        }
    }
    fprintf(out , "%d", kolvo_notlatnum);
    return 1;
}

int func_a(FILE *in, FILE *out){
    char cur;
    while((cur = fgetc(in)) != EOF){
        if((cur < '0' || cur > '9')/* && cur != '\n'*/){
            fprintf(out , "%x", cur);
        }else{
            fputc(cur, out);
        }
    }
    return 1;
}

int main(int argc, char** argv){
    char f1, f2;
    FILE *in, *out;
    if(argc == 1){
        printf("arguments error\n");
        return 0;
    }
    switch (opts(argc, argv, &f1, &f2)){
    case 2:{
        in = fopen(argv[2], "r");
        if(!in){
            printf("error opening this file\n");
            return 0;
        }
        out = fopen(argv[3], "w");
        if(!out){
            fclose(in);
            printf("error creating a file\n");
            return 0;
        }
        break;
    }
    case 1:{
        in = fopen(argv[2], "r");
        if(!in){
            printf("error opening this file\n");
            return 0;
        }
        char out_name[strlen(argv[2]) + 5];
        out_name[0] = 'o';
        out_name[1] = 'u';
        out_name[2] = 't';
        out_name[3] = '_';
        for(int i = 4; i < (int)strlen(argv[2]) + 5; i++){
            out_name[i] = argv[2][i-4];
        }
        out = fopen(out_name, "w");
        if(!out){
            fclose(in);
            printf("error creating a file\n");
            return 0;
        }
        break;
    }
    case 0:{
        printf("arguments error\n");
        return 0;
    }
    }

    switch (f2){
    case 'd':{
        func_d(in, out);
        break;
    }
    case 'i':{
        func_i(in, out);
        break;
    }
    case 's':{
        func_s(in, out);
        break;
    }
    case 'a':{
        func_a(in, out);
        break;
    }
    default:{
        printf("there is no such key\n");
    }
    }
    fclose(in);
    fclose(out);
    return 1;
}