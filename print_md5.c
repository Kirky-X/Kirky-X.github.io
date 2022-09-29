#include<stdio.h>
#include<stdlib.h>
#include<openssl/md5.h>
#include<errno.h>

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


void print_md5_float_all_c_ (float arr[], int* len_ptr, char * arr_name, int* str_len_ptr) {
    int len = *len_ptr;
    int str_len = *str_len_ptr;
    str_len = str_len + 1;
    char checksum[2 * MD5_DIGEST_LENGTH + 1];
    char *arr_name_1 = (char*) calloc(str_len, sizeof(char));
    for (int i = 0; i < str_len - 1; i++) {
       arr_name_1[i] = arr_name[i];
    }
    arr_name_1[str_len - 1] = '\0';

    int ierr = get_md5sum(arr, len, checksum);
    if(ierr != 0) {
        printf ("error calculate md5 \n");
        return;
    }

//    FILE* file = fopen("printmd5.txt", "a");
     printf("md5sum of this array %s is :%s\n", arr_name_1, checksum);
//    fclose(file);
}

void print_md5_float_all_c_with_flag_ (float arr[], int* len_ptr, char * arr_name, int* str_len_ptr, char * flag_name, int* flag_str_len_ptr) {
    int len = *len_ptr;
    int str_len = *str_len_ptr;
    str_len = str_len + 1;
    char checksum[2 * MD5_DIGEST_LENGTH + 1];
    char *arr_name_1 = (char*) calloc(str_len, sizeof(char));
    for (int i = 0; i < str_len - 1; i++) {
       arr_name_1[i] = arr_name[i];
    }
    arr_name_1[str_len - 1] = '\0';

    str_len = *flag_str_len_ptr;
    str_len = str_len + 1;
    char *flag_name_1 = (char*) calloc(str_len, sizeof(char));
    for (int i = 0; i < str_len - 1; i++) {
       flag_name_1[i] = flag_name[i];
    }
    flag_name_1[str_len - 1] = '\0';    

    int ierr = get_md5sum(arr, len, checksum);
    if(ierr != 0) {
        printf ("error calculate md5 \n");
        return;
    }

     printf("[ '%s' ] md5sum of this array %s is :%s\n", flag_name_1, arr_name_1, checksum);
}

void print_md5_float_all_c_with_flag_and_int_ (float arr[], int* len_ptr, char * arr_name, int* str_len_ptr, char * flag_name, int* flag_str_len_ptr, int* numb_ptr) {
    int numb = *numb_ptr;
    int len = *len_ptr;
    int str_len = *str_len_ptr;
    str_len = str_len + 1;
    char checksum[2 * MD5_DIGEST_LENGTH + 1];
    char *arr_name_1 = (char*) calloc(str_len, sizeof(char));
    for (int i = 0; i < str_len - 1; i++) {
       arr_name_1[i] = arr_name[i];
    }
    arr_name_1[str_len - 1] = '\0';

    str_len = *flag_str_len_ptr;
    str_len = str_len + 1;
    char *flag_name_1 = (char*) calloc(str_len, sizeof(char));
    for (int i = 0; i < str_len - 1; i++) {
       flag_name_1[i] = flag_name[i];
    }
    flag_name_1[str_len - 1] = '\0';

    int ierr = get_md5sum(arr, len, checksum);
    if(ierr != 0) {
        printf ("error calculate md5 \n");
        return;
    }

    printf("[ '%s-%d' ] md5sum of this array %s is :%s\n", flag_name_1, numb, arr_name_1, checksum);
}


void writegrid_(float arr[], int* len_ptr, char* path, int* len_path)
{
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

void readgrid_(float arr[], int* len_ptr, char* path, int* len_path)
{
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
