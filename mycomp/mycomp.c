#include "complex.h"


void parse_user_input(char *str, complex **complex_pointers);

void handle_read_comp(int num_args, char *args[], complex **complex_pointers);

int parse_double(char *str, double *num);

int is_complex(char *var_name);

complex **get_complex(char *var_name, complex **complex_pointers);


int main() {
    complex A = {0, 0};
    complex B = {0, 0};
    complex C = {0, 0};
    complex D = {0, 0};
    complex E = {0, 0};
    complex F = {0, 0};
    complex *complex_pointers[] = {&A, &B, &C, &D, &E, &F};

    char str[] = "read_comp A, 2, 3";
    parse_user_input(str, complex_pointers);
    printf("A = %.2f + %.2fi\n", A.real, A.imag);
    return 0;
}

void parse_user_input(char *str, complex **complex_pointers) {
    char *p = strtok(str, " \n\t\v\f");
    char *args[4];
    int num_args = 0;
    while (p) {
        args[num_args++] = p;
        p = strtok(NULL, ", ");
    }
    if (num_args == 0) {
        printf(ERR_EMPTY_COMMAND);
        return;
    }
    if (strcmp(args[0], "read_comp") == 0) {
        handle_read_comp(num_args, args, complex_pointers);
    }
}

void handle_read_comp(int num_args, char *args[], complex **complex_pointers) {
    if (num_args != 4) {
        printf(ERR_MISSING_PARAMETER);
        return;
    }
    if (!is_complex(args[1])) {
        printf(ERR_UNDEFINED_COMPLEX_VAR);
        return;
    }
    double real, imag;
    if (!parse_double(args[2], &real) || !parse_double(args[3], &imag)) {
        printf(ERR_INVALID_PARAMETER);
        return;
    }
    complex **ptr_to_complex = get_complex(args[1], complex_pointers);
    read_comp(*ptr_to_complex, real, imag);
}

/**
 * Returns a pointer to a pointer to a complex number variable with the given name.
 *
 * @param var_name the name of the variable to search for (one of "A", "B", "C", "D", "E", "F")
 * @param complex_pointers an array of pointers to complex numbers
 * @return a pointer to a pointer to a complex number variable with the given name, or NULL if no variable with the given name was found
 */
complex **get_complex(char *var_name, complex **complex_pointers) {
    char *complex_names[] = {"A", "B", "C", "D", "E", "F"};
    int num_complex = sizeof(complex_names) / sizeof(complex_names[0]);

    for (int i = 0; i < num_complex; i++) {
        if (strcmp(var_name, complex_names[i]) == 0) {
            return &complex_pointers[i];
        }
    }
    return NULL;
}

/**
 * Determines if a variable with the given name is a complex number variable.
 *
 * @param var_name the name of the variable to check (one of "A", "B", "C", "D", "E", "F")
 * @return 1 if the variable is a complex number variable, or 0 otherwise
 */
int is_complex(char *var_name) {
    char *complex_names[] = {"A", "B", "C", "D", "E", "F"};
    int num_complex = sizeof(complex_names) / sizeof(complex_names[0]);

    for (int i = 0; i < num_complex; i++) {
        if (strcmp(var_name, complex_names[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * Converts a string to a double, if possible.
 *
 * @param str the string to convert to a double
 * @param num a pointer to where the resulting double should be stored
 * @return 1 if the string was successfully converted to a double, or 0 otherwise
 */
int parse_double(char *str, double *num) {
    char *endptr;
    *num = strtod(str, &endptr);
    if (*endptr != '\0') {
        // the input string contained invalid characters
        return 0;
    }
    return 1;
}
