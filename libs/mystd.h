#ifndef MYSTD_H_
#define MYSTD_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

char* mystd_strcat_null(char* str, ...);

#define mystd_strcat(str,...) mystd_strcat_null(str, __VA_ARGS__, NULL)

#endif

#ifdef MYSTD_IMPLEMENTATION
char* mystd_strcat_null(char* str, ...) {
    size_t str_size = 1;
    va_list ptr;

    str_size += strlen(str);
    va_start(ptr,str);
    char* arg;
    while ((arg = va_arg(ptr, char*)) != NULL) {
        str_size += strlen(arg);
    }
    va_end(ptr);
    char *res = (char*) malloc(str_size);

    strcpy(res, str);
    va_start(ptr,str);
    while ((arg = va_arg(ptr, char*)) != NULL) {
        strcat(res,arg);
    }
    va_end(ptr);
    return res;
}
#endif
