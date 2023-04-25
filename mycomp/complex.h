#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/**
@struct complex
A structure to hold the real and imaginary components of a complex number.
*/
typedef struct {
    double real;
    double imag;
} complex;

/* function declarations */
void read_comp(complex *z, double real_part, double imag_part);

void print_comp(complex z);

void add_comp(complex z1, complex z2);

void sub_comp(complex z1, complex z2);

void mult_comp_real(complex z, double m);

void mult_comp_img(complex z, double m);

void mult_comp_comp(complex z1, complex z2);

void abs_comp(complex z);

void stop(complex **complex_pointers);

#define NUM_COMMANDS 9

#define VALID_COMMANDS {"read_comp", "print_comp", "add_comp", "sub_comp", "mult_comp_real", "mult_comp_img", "mult_comp_comp", "abs_comp", "stop"}


/* Error messages */
#define ERR_EMPTY_COMMAND "Error: empty command\n"
#define ERR_MISSING_PARAMETER "Error: missing parameter\n"
#define ERR_INVALID_PARAMETER "Error: invalid parameter - not a number\n"
#define ERR_UNDEFINED_COMPLEX_VAR "Error: undefined complex variable\n"
#define ERR_UNDEFINED_COMMAND "Error: undefined command name\n"
#define ERR_EXTRANEOUS_TEXT "Error: extraneous text after end of command\n"
#define ERR_MULTIPLE_CONSECUTIVE_COMMAS "Error: multiple consecutive commas\n"
#define ERR_MISSING_COMMA "Error: missing comma\n"
#define ERR_ILLEGAL_COMMA "Error: illegal comma\n"
#define ERR_ILLEGAL_COMMA_AFTER_COMMAND_NAME "Error: illegal comma after the command name\n"


#endif /* COMPLEX_H */
