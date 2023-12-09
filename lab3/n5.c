#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef enum {
    BAD_MALLOC = -4,
    INT_OVERFLOW,
    FLOAT_OVERFLOW,
    BAD_REALLOC,
    WRONG_DATA_FORMAT,
    FILE_ERROR,
    OK
} result_codes;

typedef struct{
    unsigned id;
    char name[20];
    char surname[20];
    char group[10];
    unsigned char *marks;
} Student;

typedef struct{
    Student **a;
    size_t size;
}Student_base;

int sep(char c){
    return c == ' ' || c == '\t';
}

void free_Student_base(Student_base *SB){
    for(size_t i = 0; i < SB->size; i++){
        free(SB->a[i]->marks);
        free(SB->a[i]);
    }
    free(SB->a);
    SB->size = 0;
}

int readempfile(Student_base *SB, FILE* in, int block_size){
    if(!in){
        return FILE_ERROR;
    }

    SB->size = 0;
    SB->a = (Student**)malloc(sizeof(Student*) * block_size);
    if(!SB->a)return BAD_MALLOC;

    char c;

    do{
        while(sep(c = fgetc(in)));
        
        if(c == EOF){
            break;
        }
        

        SB->a[SB->size] = (Student*)malloc(sizeof(Student));
        
        SB->a[SB->size]->id = 0;
        do{
            if(c >= '0' && c <= '9'){
                c -= '0';
                if((UINT_MAX - c)/10 < SB->a[SB->size]->id){
                    free_Student_base(SB);
                    return INT_OVERFLOW;
                }else{
                    SB->a[SB->size]->id = SB->a[SB->size]->id*10 + c;
                }
            }else{
                free_Student_base(SB);
                return WRONG_DATA_FORMAT;
            }
        }while(!sep(c = fgetc(in)));


        while(sep(c = fgetc(in)));
        
        if(c == EOF){
            free_Student_base(SB);
            return WRONG_DATA_FORMAT;
        }

        unsigned i = 0;

        do{
            if(i < 19 && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))){
                SB->a[SB->size]->name[i++] = c;
            }else{
                free_Student_base(SB);
                return WRONG_DATA_FORMAT;
            }
        }while(!sep(c = fgetc(in)));
        SB->a[SB->size]->name[i] = '\0';


        
        while(sep(c = fgetc(in)));
        
        if(c == EOF){
            free_Student_base(SB);
            return WRONG_DATA_FORMAT;
        }


        i = 0;
        do{
            if(i < 19 && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))){
                SB->a[SB->size]->surname[i++] = c;
            }else{
                free_Student_base(SB);
                return WRONG_DATA_FORMAT;
            }
        }while(!sep(c = fgetc(in)));
        SB->a[SB->size]->surname[i] = '\0';

        
        while(sep(c = fgetc(in)));
        
        if(c == EOF){
            free_Student_base(SB);
            return WRONG_DATA_FORMAT;
        }

        i = 0;
        do{
            if(i < 9){
                SB->a[SB->size]->group[i++] = c;
            }else{
                free_Student_base(SB);
                return WRONG_DATA_FORMAT;
            }
        }while(!sep(c = fgetc(in)));
        SB->a[SB->size]->group[i] = '\0';

        while(sep(c = fgetc(in)));
        
        if(c == EOF){
            free_Student_base(SB);
            return WRONG_DATA_FORMAT;
        }

        size_t tmp_i = 0;
        unsigned char *tmp_uchar = (unsigned char*)malloc(sizeof(unsigned char) * 6);
        do{
            if(c >= '1' && c <= '5'){
                tmp_uchar[tmp_i++] = c;
                c = fgetc(in);
            }else{
                free(tmp_uchar);
                free_Student_base(SB);
                return WRONG_DATA_FORMAT;
            }
        }while(tmp_i < 5);
        tmp_uchar[tmp_i] = '\0';
        SB->a[SB->size]->marks = tmp_uchar;

        while(sep(c)){
            c = fgetc(in);
        }

        if(c != '\n' && c != EOF){
            printf("noway\n");
            free_Student_base(SB);
            return WRONG_DATA_FORMAT;
        }

        SB->size++;

        if(SB->size%block_size == 0){
            if(SIZE_MAX - block_size < SB->size){
                free_Student_base(SB);
                return WRONG_DATA_FORMAT;
            }
            Student** tmpsa = (Student**)realloc(SB->a, SB->size + block_size);
            if(!tmpsa){
                free_Student_base(SB);
                return BAD_REALLOC;
            }
            SB->a = tmpsa;
        }

    }while(c != EOF);

    
    return OK;
}

result_codes fprintSB(Student_base SB, FILE* out){
    if(!out){
        return FILE_ERROR;
    }
    for(size_t i = 0; i < SB.size; i++){
        fprintf(out, "%u %s %s %s %s\n", SB.a[i]->id, SB.a[i]->name, SB.a[i]->surname, SB.a[i]->group, SB.a[i]->marks);
    }
    return OK;
}

int Studentcmp_id(const void *s1, const void *s2){
    return (*(Student**)s1)->id - (*(Student**)s2)->id;
}

int Studentcmp_name(const void *s1, const void *s2){
    return strcmp((*(Student**)s1)->name, (*(Student**)s2)->name);
}

int Studentcmp_surname(const void *s1, const void *s2){
    return strcmp((*(Student**)s1)->surname, (*(Student**)s2)->surname);
}

int Studentcmp_group(const void *s1, const void *s2){
    return strcmp((*(Student**)s1)->group, (*(Student**)s2)->group);
}

double count_average_mark(unsigned char *marks){
    double sum = 0;
    double count = 0;
    for(size_t i = 0; marks[i] != '\0' && i < SIZE_MAX; i++){
        sum += marks[i] - '0';
        count++; 
    }
    return sum/count;
}

int main(int argc, char **argv){
    FILE *in, *out;
    switch(argc){
        case 2:{
            in = fopen(argv[1], "r");
            out = stdout;
            if(!in){
                printf("file error!\n");
                return 0;
            }
            break;
        }
        case 3:{
            in = fopen(argv[1], "r");
            out = fopen(argv[2], "w");
            if(!in || !out){
                printf("file error!\n");
                return 0;
            }
            break;
        }
        default:{
            printf("%s input_file [output_file]", argv[0]);
            return 0;
        }
    }

    int block_size = 1;
    Student_base SB;

    result_codes n = readempfile(&SB, in, block_size);

    switch(n){
        case BAD_MALLOC:{
            printf("Bad malloc\n");
            return 0;
        }
        case BAD_REALLOC:{
            printf("Bad realloc\n");
            return 0;
        }
        case WRONG_DATA_FORMAT:{
            printf("Empty file or invalid base format\n");
            return 0;
        }
        case INT_OVERFLOW:{
            printf("Int overflow\n");
            return 0;
        }
        case FLOAT_OVERFLOW:{
            printf("Float overflow\n");
            return 0;
        }
        case FILE_ERROR:{
            printf("File error\n");
            return 0;
        }
        case OK:{
            break;
        }
    }

    char ans = 0;

    do{
        switch(ans){
            case '1':{
                printf("\tSort by:\n1. id\n2. name\n3. surname\n4. group\n0. back\n~");
                scanf("\n%c", &ans);
                switch(ans){
                    case '1':{
                        qsort(SB.a, SB.size, sizeof(Student*), Studentcmp_id);
                        break;
                    }
                    case '2':{
                        qsort(SB.a, SB.size, sizeof(Student*), Studentcmp_name);
                        break;
                    }
                    case '3':{
                        qsort(SB.a, SB.size, sizeof(Student*), Studentcmp_surname);
                        break;
                    }
                    case '4':{
                        qsort(SB.a, SB.size, sizeof(Student*), Studentcmp_group);
                        break;
                    }
                    default:{
                        break;
                    }
                }
                ans = 0;
                break;
            }
            case '2':{
                printf("\tFind by:\n1. id\n2. name\n3. surname\n4. group\n0. back\n~");
                scanf("\n%c", &ans);
                switch(ans){
                    case '1':{
                        printf("input id:");
                        unsigned key;
                        scanf("\n%u", &key);
                        fprintf(out, "\tSearch results with key id : %u\n", key);
                        size_t fl = 0;
                        for(size_t i = 0; i < SB.size; i++){
                            if(SB.a[i]->id == key){
                                fprintf(out, "%u %s %s %s %s\n", SB.a[i]->id, SB.a[i]->name, SB.a[i]->surname, SB.a[i]->group, SB.a[i]->marks);
                                fl++;
                            }
                        }
                        fprintf(out, "%lld students found\n", fl);
                        break;
                    }
                    case '2':{
                        printf("input name:");
                        char key[20];
                        scanf("\n%s", key);
                        fprintf(out, "\tSearch results with key name : %s\n", key);
                        size_t fl = 0;
                        for(size_t i = 0; i < SB.size; i++){
                            if(!strcmp(SB.a[i]->name, key)){
                                fprintf(out, "%u %s %s %s %s\n", SB.a[i]->id, SB.a[i]->name, SB.a[i]->surname, SB.a[i]->group, SB.a[i]->marks);
                                fl++;
                            }
                        }
                        fprintf(out, "%lld students found\n", fl);
                        break;
                    }
                    case '3':{
                        printf("input surname:");
                        char key[20];
                        scanf("\n%s", key);
                        fprintf(out, "\tSearch results with key surname : %s\n", key);
                        size_t fl = 0;
                        for(size_t i = 0; i < SB.size; i++){
                            if(!strcmp(SB.a[i]->surname, key)){
                                fprintf(out, "%u %s %s %s %s\n", SB.a[i]->id, SB.a[i]->name, SB.a[i]->surname, SB.a[i]->group, SB.a[i]->marks);
                                fl++;
                            }
                        }
                        fprintf(out, "%lld students found\n", fl);
                        break;
                    }
                    case '4':{
                        printf("input group:");
                        char key[10];
                        scanf("\n%s", key);
                        fprintf(out, "\tSearch results with key group : %s\n", key);
                        size_t fl = 0;
                        for(size_t i = 0; i < SB.size; i++){
                            if(!strcmp(SB.a[i]->group, key)){
                                fprintf(out, "%u %s %s %s %s\n", SB.a[i]->id, SB.a[i]->name, SB.a[i]->surname, SB.a[i]->group, SB.a[i]->marks);
                                fl++;
                            }
                        }
                        fprintf(out, "%lld students found\n", fl);
                        break;
                    }
                    default:{
                        break;
                    }
                }
                ans = 0;
                break;
            }
            case '3':{
                double average;
                double sum = 0;
                for(size_t i = 0; i < SB.size; i++){
                    sum += count_average_mark(SB.a[i]->marks);
                }
                average = sum/(double)SB.size;
                fprintf(out, "the average mark is %lf\n Students with marks above average:\n", average);
                size_t fl = 0;
                for(size_t i = 0; i < SB.size; i++){
                    if(count_average_mark(SB.a[i]->marks) - average > __DBL_EPSILON__){
                        fprintf(out, "%s %s\n",SB.a[i]->name, SB.a[i]->surname);
                        fl++;
                    }
                }
                fprintf(out, "%lld students found\n", fl);

                ans = 0;
                break;
            }
            case '4':{
                fprintSB(SB, out);
                ans = 0;
                break;
            }
            case 0:{
                printf("1. Sort\n2. Find\n3. Print student with marks above average\n4. print table\n0. exit\n>");
                scanf("\n%c", &ans);
                break;
            }
            default:{
                scanf("%c", &ans);
                break;
            }
        }
    }while(ans != '0');

    
    fclose(in);
    if(out != stdout){
        fclose(out);
    }
    free_Student_base(&SB);
    return 1;
}