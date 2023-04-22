#ifndef UTILS_H
#define UTILS_H

#include "complex.h"

complex **get_complex(char *var_name, complex **complex_pointers);

int is_complex(char *var_name);

int parse_double(char *str, double *num);

int count_args(char args[]);

void remove_spaces(char *string);

int count_commas(char *str);

#endif //UTILS_H
