#include<stdio.h>
#include<stdlib.h>
#include<openssl/md5.h>
#include<errno.h>
#include<mpi.h>

/**
 * 将数据生成md5值
 *
 * @buffer      : 指向数据起始地址的指针
 * @buffersize  : 数据的长度
 * @checksum    : 生成数据的字符串指针，用于存储生成的MD5
 * @return 返回MD5生成结果，0：success，1：failed
 */
int get_md5sum(void* buffer, unsigned long buffersize, char* checksum) {
    MD5_CTX ctx;
    unsigned char digest[MD5_DIGEST_LENGTH];

    int rc = MD5_Init(&ctx);
    if(rc != 1) {
        fprintf(stderr, "error in get_md5sum : MD5_Init\n");
        return 1;
    }

    rc =  MD5_Update(&ctx, buffer, sizeof(float) * buffersize);
    if(rc != 1) {
        fprintf(stderr, "error in get_md5sum : MD5_Update\n");
        return 1;
    }

    rc = MD5_Final(digest, &ctx);
    if(rc != 1) {
        fprintf(stderr, "error in get_md5sum : MD5_Final\n");
        return 1;
    }

    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        snprintf(&(checksum[i * 2]), 16 * 2, "%02x \n", (unsigned int)digest[i]);
    }

    checksum[2 * MD5_DIGEST_LENGTH + 1] = '\0';
    return 0;
}

/**
 * 修正字符串，在原有字符串末尾加结束符'\0'
 *
 * @arr_name     : 指向字符串起始地址的指针
 * @str_len_ptr  : 字符串的长度
 * @return 修正后的字符串
 */
char* get_str(char* arr_name, int* str_len_ptr) {
    int str_len = *str_len_ptr;
    str_len = str_len + 1;
    char* arr_res = (char*) calloc(str_len, sizeof(char));
    for (int i = 0; i < str_len - 1; i++) {
       arr_res[i] = arr_name[i];
    }
    arr_res[str_len - 1] = '\0';
    return arr_res;
}

/**
 * 打印指定变量的MD5值，带进程号打印/只打主进程
 *
 * @arr              : 指向变量起始地址的指针。传址给get_md5sum的 void* buffer
 * @len_ptr          : 变量数据长度
 * @arr_name         : 指向变量名称起始地址的指针
 * @str_len_ptr      : 变量字符串的长度
 * @is_master        : 判断是否只打印主进程，0：只打印主进程的数据，1：带进程号打印全部进程数据
 */
void print_md5_float_all_c_ (float arr[], int* len_ptr, char* arr_name, int* str_len_ptr, int* is_master) {
    int all = *is_master;
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank != 0 && all == 0){
       return;
    }
    
    char* arr_res = get_str(arr_name, str_len_ptr);
    
    // 生成MD5
    int len = *len_ptr;
    char checksum[2 * MD5_DIGEST_LENGTH + 1];
    int ierr = get_md5sum(arr, len, checksum);
    if(ierr != 0) {
        printf ("error calculate md5 \n");
        return;
    }

    if (all == 1){
        printf("rank %d, md5sum of this array %s is :%s\n", rank, arr_res, checksum);
    } else {
        printf("md5sum of this array %s is :%s\n", arr_res, checksum);
    }
}


/**
 * 打印指定变量的MD5值，带标志位和进程号打印
 *
 * @arr              : 指向变量起始地址的指针。传址给get_md5sum的 void* buffer
 * @len_ptr          : 变量数据长度
 * @arr_name         : 指向变量名称起始地址的指针
 * @str_len_ptr      : 变量字符串的长度
 * @flag_name        : 指向标志位起始地址的指针
 * @flag_str_len_ptr : 标志位字符串的长度 
 * @is_master        : 判断是否只打印主进程，0：只打印主进程的数据，1：带进程号打印全部进程数据
 */
void print_md5_float_all_c_with_flag_ (float arr[], int* len_ptr, char* arr_name, int* str_len_ptr, char* flag_name, int* flag_str_len_ptr, int* is_master) {
    int all = *is_master;
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank != 0 && all == 0){
       return;
    }
    
    char* arr_res = get_str(arr_name, str_len_ptr);
    char* flag_res = get_str(flag_name, flag_str_len_ptr);
    
    //生成MD5
    int len = *len_ptr;
    char checksum[2 * MD5_DIGEST_LENGTH + 1];
    int ierr = get_md5sum(arr, len, checksum);
    if(ierr != 0) {
        printf ("error calculate md5 \n");
        return;
    }
    if (all == 1){
        printf("[ '%s' ] rank %d, md5sum of this array %s is :%s\n", flag_res, rank, arr_res, checksum);
    } else {
        printf("[ '%s' ] md5sum of this array %s is :%s\n", flag_res, arr_res, checksum);
    }
}


/**
 * 打印指定变量的MD5值，带标志位、进程号和一位数值打印
 *
 * @arr              : 指向变量起始地址的指针。传址给get_md5sum的 void* buffer
 * @len_ptr          : 变量数据长度
 * @arr_name         : 指向变量名称起始地址的指针
 * @str_len_ptr      : 变量字符串的长度
 * @flag_name        : 指向标志位起始地址的指针
 * @flag_str_len_ptr : 标志位字符串的长度 
 * @numb_ptr         : 数值标志位，用于指示循环当中的轮次
 * @is_master        : 判断是否只打印主进程，0：只打印主进程的数据，1：带进程号打印全部进程数据
 */
void print_md5_float_all_c_with_flag_and_int_ (float arr[], int* len_ptr, char* arr_name, int* str_len_ptr, char* flag_name, int* flag_str_len_ptr, int* numb_ptr, int* is_master) {
    int all = *is_master;
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank != 0 && all == 0){
       return;
    }
    
    int numb = *numb_ptr;
    char* arr_res = get_str(arr_name, str_len_ptr);
    char* flag_res = get_str(flag_name, flag_str_len_ptr);
    
    //生成MD5
    int len = *len_ptr;
    char checksum[2 * MD5_DIGEST_LENGTH + 1];
    int ierr = get_md5sum(arr, len, checksum);
    if(ierr != 0) {
        printf ("error calculate md5 \n");
        return;
    }

    if (all == 1){
        printf("[ '%s-%d' ] rank %d, md5sum of this array %s is :%s\n", flag_res, numb, rank, arr_res, checksum);
    } else {
        printf("[ '%s-%d' ] md5sum of this array %s is :%s\n", flag_res, numb, arr_res, checksum);
    }
}


/**
 * 打印指定变量的MD5值，带标志位、进程号和两位数值打印
 *
 * @arr               : 指向变量起始地址的指针。传址给get_md5sum的 void* buffer
 * @len_ptr           : 变量数据长度
 * @arr_name          : 指向变量名称起始地址的指针
 * @str_len_ptr       : 变量字符串的长度
 * @flag_name         : 指向标志位起始地址的指针
 * @flag_str_len_ptr  : 标志位字符串的长度 
 * @numb1_ptr         : 数值标志位，用于指示循环当中的轮次
 * @numb2_ptr         : 数值标志位，用于指示循环当中的轮次
 * @is_master         : 判断是否只打印主进程，0：只打印主进程的数据，1：带进程号打印全部进程数据
 */
void print_md5_float_all_c_with_flag_and_int2_ (float arr[], int* len_ptr, char* arr_name, int* str_len_ptr, char* flag_name, int* flag_str_len_ptr, int* numb1_ptr, int* numb2_ptr, int* is_master) {
    int all = *is_master;
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank != 0 && all == 0){
       return;
    }

    int numb1 = *numb1_ptr;
    int numb2 = *numb2_ptr;
    char* arr_res = get_str(arr_name, str_len_ptr);
    char* flag_res = get_str(flag_name, flag_str_len_ptr);
    
    //生成MD5
    int len = *len_ptr;
    char checksum[2 * MD5_DIGEST_LENGTH + 1];
    int ierr = get_md5sum(arr, len, checksum);
    if(ierr != 0) {
        printf ("error calculate md5 \n");
        return;
    }

    if (all == 1){
        printf("[ '%s-%d-%d' ] rank %d, md5sum of this array %s is :%s\n", flag_res, numb1, numb2, rank, arr_res, checksum);
    } else {
        printf("[ '%s-%d-%d' ] md5sum of this array %s is :%s\n", flag_res, numb1, numb2, arr_res, checksum);
    }
}

/**
 * 将文件中的数据写入网格中
 */
void writegrid_(float arr[], int* len_ptr, char* path, int* len_path){
    int len = *len_ptr * sizeof(float);
    int step = 5000;
    char path_1[10];
    static int index = 0;
    path_1[0] = '.';
    path_1[1] = '/';
    path_1[2] = 't';
    path_1[3] = 'm';
    path_1[4] = 'p';
    path_1[5] = '/';
    path_1[6] = 'x';
    path_1[7] = '0' + index;
    path_1[8] = 0;
    if (index == 5) {
       return;
    }
    ++index;
    FILE* file = fopen(path_1, "w+");
    if (file == NULL) {
        printf ("open fail errno = %d \n", errno);
        return;
    }

    while (len > 0) {
        step = len >= step ? step : len;
        int rt =  fwrite(arr, 1, step, file);
        if (rt != step) {
            printf ("fwrite error: rt:%d len:%d", rt, len);
            fclose(file);
            return;
        }
        len = len - step;
        fseek(file, *len_ptr * sizeof(float) - len, SEEK_SET);
        arr = arr + step;
    } 

    fclose(file);
}

/**
 * 将网格内的数据写入到文件
 */
void readgrid_(float arr[], int* len_ptr, char* path, int* len_path){
    int len = *len_ptr * sizeof(float);
    int step = 5000;
    char path_1[10];
    static int index = 1;
    path_1[0] = '.';
    path_1[1] = '/';
    path_1[2] = 't';
    path_1[3] = 'm';
    path_1[4] = 'p';
    path_1[5] = '/';
    path_1[6] = 'x';
    path_1[7] = '0' + index;
    path_1[8] = 0;
    ++index;

    FILE* file = fopen(path_1, "r+");
    if (file == NULL) {
        printf ("open fail errno = %d \n", errno);
        return;
    }

    fseek(file, 0, SEEK_SET);
    while (len > 0) {
        step = len >= step ? step : len;
        int rt =  fread(arr, 1, step, file);
        if (rt != step) {
            printf ("fread error: rt:%d len:%d", rt, len);
            fclose(file);
            return;
        }
        len = len - step;
        fseek(file, *len_ptr * sizeof(float) - len, SEEK_SET);
        arr = arr + step;
    }

    fclose(file);
}

