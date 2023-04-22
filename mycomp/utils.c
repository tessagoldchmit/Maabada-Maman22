//
// Created by tessa on 4/21/2023.
//

#include <ctype.h>
#include "utils.h"
#include "complex.h"

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
    int i;
    for (i = 0; i < num_complex; i++) {
        if (strcmp(var_name, complex_names[i]) == 0) {
            return &complex_pointers[i];
        }
    }
    return NULL;
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

/**
 * Skips over whitespace characters in a given string starting from a given index.
 *
 * @param str: a pointer to the input string to process.
 * @param i: an integer representing the index of the first character to start processing from.
 *
 * @return: An integer representing the index of the next non-whitespace character in the string.
 */
int ignore_whitespaces(char *str, int i) {
    while (isspace(str[i])) {
        i++;
    }
    return i;
}

/**
 * Checks if the string starting at the index pointed to by i represents a valid number.
 * A valid number can contain digits, a decimal point (at most once), and an optional sign (+/-).
 *
 * Parameters:
 * str (char*): A pointer to the string to validate.
 * i (int*): A pointer to an integer representing the index at which to start the validation.
 *
 * Returns:
 * int: 1 if the string represents a valid number, 0 otherwise.
 */
int check_number(char *str, int *i) {
    int dot_count = 0;

    if (!isdigit(str[*i]) && str[*i] != '-' && str[*i] != '+') {
        HANDLE_ERROR(ERR_INVALID_PARAMETER);
    }

    while (isdigit(str[*i]) || str[*i] == '.' || str[*i] == '-') {
        if (str[*i] == '.') {
            dot_count++;
        }
        (*i)++;
    }

    if (dot_count > 1) {
        HANDLE_ERROR(ERR_INVALID_PARAMETER);
    }

    return 1;
}