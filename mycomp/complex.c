#include "complex.h"


/**
 * Reads in the real and imaginary components of a complex number.
 *
 * @param  z A pointer to the complex number to be modified.
 * @param  real_part The real component to be assigned to the complex number.
 * @param  imag_part The imaginary component to be assigned to the complex number.
 */
void read_comp(complex *z, double real_part, double imag_part) {
    z->real = real_part;
    z->imag = imag_part;
}


/**
 * Prints a complex number in the format "real + (imag)i".
 *
 * @param  z The complex number to be printed.
 */
void print_comp(complex z) {
    printf("%.2f + (%.2f)i\n", z.real, z.imag);
}


/**
 * Adds two complex numbers together.
 *
 * @param  z1 The first complex number to be added.
 * @param  z2 The second complex number to be added.
 */
void add_comp(complex z1, complex z2) {
    complex result;
    result.real = z1.real + z2.real;
    result.imag = z1.imag + z2.imag;
    print_comp(result);
}


/**
 * Subtracts one complex number from another.
 *
 * @param  z1 The complex number from which to subtract.
 * @param  z2 The complex number to subtract.
 */
void sub_comp(complex z1, complex z2) {
    complex result;
    result.real = z1.real - z2.real;
    result.imag = z1.imag - z2.imag;
    print_comp(result);
}


/**
 * Multiplies a complex number by a real number.
 *
 * @param  z The complex number to be multiplied.
 * @param  m The real number by which to multiply the complex number.
 */
void mult_comp_real(complex z, double m) {
    complex result;
    result.real = z.real * m;
    result.imag = z.imag * m;
    print_comp(result);
}


/**
 * Multiplies a complex number by a pure imaginary number.
 *
 * @param  z The complex number to be multiplied.
 * @param  m The pure imaginary number by which to multiply the complex number.
 * @return The result of multiplying a complex number by a pure imaginary number.
 */
void mult_comp_img(complex z, double m) {
    complex result;
    result.real = -m * z.imag;
    result.imag = m * z.real;
    print_comp(result);
}


/**
 * Multiplies two complex numbers together.
 *
 * @param  z1 The first complex number to be multiplied.
 * @param  z2 The second complex number to be multiplied.
 */
void mult_comp_comp(complex z1, complex z2) {
    complex result;
    result.real = z1.real * z2.real - z1.imag * z2.imag;
    result.imag = z1.real * z2.imag + z1.imag * z2.real;
    print_comp(result);
}


/**
 * Calculates the absolute value of a complex number.
 *
 * @param  z The complex number for which to calculate the absolute value.
 * @return The absolute value of a complex number.
 */
void abs_comp(complex z) {
    double abs = sqrt(z.real * z.real + z.imag * z.imag);
    printf("%f", abs);

}


/**
 * Prints a message to the console indicating the program has stopped, then exits the program.
 */
void stop(void) {
    printf("Stopping program...\n");
    exit(0);
}
