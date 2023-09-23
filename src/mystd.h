#ifndef MYSTD_H_
#define MYSTD_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

char* mystd_strcat(int count, char* str, ...);
#endif

#ifdef MYSTD_IMPLEMENTATION
char* mystd_strcat(int count, char* str, ...) {
    size_t str_size = 1;
    va_list ptr;

    str_size += strlen(str);
    va_start(ptr,str);
    char* arg;
    for (int i = 0; i < count - 1; ++i) {
        arg = va_arg(ptr, char*);
        str_size += strlen(arg);
    }
    va_end(ptr);
    char *res = (char*) malloc(str_size);

    strcpy(res, str);
    va_start(ptr,str);
    for (int i = 0; i < count - 1; ++i) {
        arg = va_arg(ptr, char*);
        strcat(res,arg);
    }
    va_end(ptr);
    return res;
}
#endif
