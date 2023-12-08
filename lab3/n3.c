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
    OK
} result_codes;

typedef struct{
    unsigned id;
    char name[20];
    char surname[20];
    float salary;
} Employee;

int sep(char c){
    return c == ' ' || c == '\t';
}

void free_employee_array(Employee **emp_m, int n){
    for(int i = 0; i < n; i++){
        free(emp_m[i]);
    }
    free(emp_m);
}

int readempfile(Employee ***emp_res, FILE* in, int block_size){
    if(!in){
        return -1;
    }
    int n = 0;

    Employee **emp_m = (Employee**)malloc(sizeof(Employee*) * block_size);
    if(!emp_m)return BAD_MALLOC;

    char c;

    do{
        while(sep(c = fgetc(in)));
        
        if(c == EOF){
            break;
        }
        
        printf("%d : ", n);

        emp_m[n] = (Employee*)malloc(sizeof(Employee));
        
        emp_m[n]->id = 0;
        do{
            if(c >= '0' && c <= '9'){
                c -= '0';
                if((UINT_MAX - c)/10 < emp_m[n]->id){
                    free_employee_array(emp_m, n+1);
                    return INT_OVERFLOW;
                }else{
                    emp_m[n]->id = emp_m[n]->id*10 + c;
                }
            }else{
                free_employee_array(emp_m, n+1);
                return WRONG_DATA_FORMAT;
            }
        }while(!sep(c = fgetc(in)));

        printf("id:%u ", emp_m[n]->id);

        while(sep(c = fgetc(in)) && c != EOF);
        
        if(c == EOF){
            free_employee_array(emp_m, n+1);
            return WRONG_DATA_FORMAT;
        }

        unsigned i = 0;

        do{
            if(i < 19 && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))){
                emp_m[n]->name[i++] = c;
            }else{
                free_employee_array(emp_m, n+1);
                return WRONG_DATA_FORMAT;
            }
        }while(!sep(c = fgetc(in)));
        emp_m[n]->name[i] = '\0';

        printf("name:%s ", emp_m[n]->name);
        
        while(sep(c = fgetc(in)));
        
        if(c == EOF){
            free_employee_array(emp_m, n+1);
            return WRONG_DATA_FORMAT;
        }

        i = 0;
        do{
            if(i < 19 && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))){
                emp_m[n]->surname[i++] = c;
            }else{
                free_employee_array(emp_m, n+1);
                return WRONG_DATA_FORMAT;
            }
        }while(!sep(c = fgetc(in)));
        emp_m[n]->surname[i] = '\0';

        printf("surname:%s ", emp_m[n]->surname);
        
        while(sep(c = fgetc(in)));
        
        if(c == EOF){
            free_employee_array(emp_m, n+1);
            return WRONG_DATA_FORMAT;
        }

        char neg_fl = 0;
        if(c == '-'){
            neg_fl = 1;
            emp_m[n]->salary = 0;
        }else if(c == '+'){
            emp_m[n]->salary = 0;
        }else if(c >= '0' && c <= '9'){
            emp_m[n]->salary = c - '0';
        }else{
           free_employee_array(emp_m, n+1);
            return WRONG_DATA_FORMAT; 
        }

        while(!sep(c = fgetc(in)) && c != '.' && c != 'e' && c != 'E' && c != '\n'){
            if(c >= '0' && c <= '9'){
                emp_m[n]->salary = emp_m[n]->salary*10 + c - '0';
            }
            else{
                free_employee_array(emp_m, n+1);
                return WRONG_DATA_FORMAT;
            }
        }

        if(c == '.'){
            double tmpd = 1, tmpdouble = 0;
            while(!sep(c = fgetc(in)) && c != EOF && c != '\n' && c != 'e' && c != 'E'){
                if(c >= '0' && c <= '9'){
                    tmpdouble = tmpdouble*10 + (c-'0');
                    tmpd *= 0.1;
                }else{
                    free_employee_array(emp_m, n+1);
                    return WRONG_DATA_FORMAT;
                }
                
            }
            emp_m[n]->salary += tmpdouble * tmpd;
        }
        
        if(c == 'e' || c == 'E'){
            int exp;
            char neg_fl_e = 0;
            if((c = fgetc(in)) == '-'){
                exp = 0;
                neg_fl_e = 1;
            }else if(c == '+'){
                exp = 0;
            }else if(c >= '0' && c <= '9'){
                exp = c -'0';
            }else{
                free_employee_array(emp_m, n+1);
                return WRONG_DATA_FORMAT;
            }

            while(!sep(c = fgetc(in)) && c != EOF && c != '\n'){
                if(c >= '0' && c <= '9'){
                    exp = exp*10 + (c - '0');
                    if(exp >= 100){
                        free_employee_array(emp_m, n+1);
                        return WRONG_DATA_FORMAT;
                    }
                }else{
                    free_employee_array(emp_m, n+1);
                    return WRONG_DATA_FORMAT;
                }
            }

            if(neg_fl_e)exp *= -1;

            emp_m[n]->salary *= pow(10, exp);
        }
        
        if(neg_fl)emp_m[n]->salary *= -1;

        if(isinf(emp_m[n]->salary) || isnan(emp_m[n]->salary)){
            free_employee_array(emp_m, n+1);
            return FLOAT_OVERFLOW;
        }

        printf("salary:%lf\n", emp_m[n]->salary);

        n++;

        if(n%block_size == 0){
            if(INT_MAX - block_size < n){
                free_employee_array(emp_m, n);
                return WRONG_DATA_FORMAT;
            }
            Employee** tmpemp = (Employee**)realloc(emp_m, n + block_size);
            if(!tmpemp){
                free_employee_array(emp_m, n+1);
                return BAD_REALLOC;
            }
            emp_m = tmpemp;
        }

        while(sep(c) && c != '\n' && c != EOF){
            c = fgetc(in);
        }

        if(c != '\n' && c != EOF){
            free_employee_array(emp_m, n);
            return WRONG_DATA_FORMAT;
        }

    }while(c != EOF);
    
    *emp_res = emp_m;
    return n;
}

int employeecmp(const void* e1, const void* e2){
    double eps = 1e-10;
    Employee *emp1 = *(Employee**)e1, *emp2 = *(Employee**)e2;
    int tmp_res = ((emp1->salary - emp2->salary > eps) - (emp2->salary - emp1->salary > eps));
    if(tmp_res){
        return tmp_res;
    }else{
        tmp_res = strcmp(emp1->name, emp2->name);
        if(tmp_res){
            return tmp_res;
        }else{
            tmp_res = strcmp(emp1->surname, emp2->surname);
            if(tmp_res){
                return tmp_res;
            }else{
                tmp_res = (emp1->id > emp2->id) - (emp2->id > emp1->id);
                return tmp_res;
            }
        }
    }
}

int employeecmp_rev(const void* e1, const void* e2){
    return -employeecmp(e1, e2);
}

int main(int argc, char **argv){

    if(argc != 4){
        printf("%s -option input_file output_file\noptions:\n\t-a(/a) : normal sort\n\t-d(/d) : reverse sort\n", argv[0]);
        return 0;
    }

    int sortfl;
    if(!strcmp( argv[1], "-a") || !strcmp(argv[1], "/a") ){
        sortfl = 1;
    }else if( !strcmp(argv[1], "-d") || !strcmp(argv[1], "/d") ){
        sortfl = 0;
    }else{
        printf("no flag detected:-a(/a) or -d(/d)\n");
        return 0;
    }


    FILE *in = fopen(argv[2], "r"), *out = fopen(argv[3], "w");
    if(!in || !out){
        printf("file error!\n");
        return 0;
    }

    int block_size = 20;
    Employee **emp_m;

    int n = readempfile(&emp_m, in, block_size);

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
        default:{
            printf("success! %d lines red\n", n);
            break;
        }
    }

    if(sortfl){
        qsort(emp_m, n, sizeof(Employee*), employeecmp);
    }else{
        qsort(emp_m, n, sizeof(Employee*), employeecmp_rev);
    }

    printf("xdlol\n");

    for(int i = 0; i < n; i++){
        fprintf(out ,"%u %s %s %lf\n", emp_m[i]->id, emp_m[i]->name, emp_m[i]->surname, emp_m[i]->salary);
        printf("%u %s %s %lf\n", emp_m[i]->id, emp_m[i]->name, emp_m[i]->surname, emp_m[i]->salary);
        free(emp_m[i]);
    }
    
    fclose(in);
    fclose(out);
    free(emp_m);
    return 1;
}