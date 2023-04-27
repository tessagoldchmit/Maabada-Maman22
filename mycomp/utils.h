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

#define HELP_TEXT_PART1 \
                    "Enter one of the following commands in a valid format:\n\n"\
                    "* read_comp {complex_var}, {real_part}, {imaginary_part}\n\tReads values into a complex variable.\n"\
                    "* print_comp {complex_var}\n\tPrints a complex variable.\n"\
                    "* add_comp {complex_var}, {complex_var}\n\tPrints the result of adding two complex variables.\n"\
                    "* sub_comp {complex_var}, {complex_var}\n\tPrints the result of subtracting two complex variables.\n"
#define HELP_TEXT_PART2 \
                    "* mult_comp_real {complex_var}, {real}\n\tPrints the result of the mult of a complex with a real number.\n"\
                    "* mult_comp_img {complex_var}, {imaginary}\n\tPrints the result of the mult of a complex with an imaginary number.\n"\
                    "* mult_comp_comp {complex_var}, {complex_var}\n\tPrints the result of the mult of 2 complex numbers.\n"\
                    "* abs_comp {complex_var}\n\tPrints the absolute value of a complex variable.\n"\
                    "* stop\n\tStops the program.\n\n"

complex **get_complex(char *var_name, complex **complex_pointers);

int ignore_whitespaces(char *str, int i);

int is_number(char *str, int *i);

int is_comma(const char *str, int *i);

#endif
