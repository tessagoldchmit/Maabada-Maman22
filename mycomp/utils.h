#ifndef UTILS_H
#define UTILS_H

#include "complex.h"

#define HANDLE_ERROR(msg) \
    do { \
        printf(msg); \
        return 0; \
    } while (0)


complex **get_complex(char *var_name, complex **complex_pointers);

int parse_double(char *str, double *num);

int ignore_whitespaces(char *str, int i);

int check_number(char *str, int *i);

int validate_comma(char *str, int *i);

#endif
