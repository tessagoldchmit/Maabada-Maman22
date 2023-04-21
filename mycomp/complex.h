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
/*void print_comp(complex z);
complex add_comp(complex z1, complex z2);
complex sub_comp(complex z1, complex z2);
complex mult_comp_real(complex z, double m);
complex mult_comp_img(complex z, double m);
complex mult_comp_comp(complex z1, complex z2);
double abs_comp(complex z);
void stop(void);*/

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


#endif /* COMPLEX_H */
