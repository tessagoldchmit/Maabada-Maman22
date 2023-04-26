#ifndef UTILS_H
#define UTILS_H

#include "complex.h"

#define HANDLE_ERROR(msg) \
    do { \
        printf(msg); \
        return 0; \
    } while (0)

#define LOG_INFO(func_name) \
    printf("Info: The function %s has completed successfully\n", func_name)


complex **get_complex(char *var_name, complex **complex_pointers);

int ignore_whitespaces(char *str, int i);

int is_number(char *str, int *i);

int is_comma(const char *str, int *i);

#endif
