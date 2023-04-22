#ifndef UTILS_H
#define UTILS_H

#include "complex.h"

complex **get_complex(char *var_name, complex **complex_pointers);

int parse_double(char *str, double *num);

int ignore_whitespaces(char *str, int i);

#endif //UTILS_H
