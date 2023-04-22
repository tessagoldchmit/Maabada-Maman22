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
 * Determines if a variable with the given name is a complex number variable.
 *
 * @param var_name the name of the variable to check (one of "A", "B", "C", "D", "E", "F")
 * @return 1 if the variable is a complex number variable, or 0 otherwise
 */
int is_complex(char *var_name) {
    char *complex_names[] = {"A", "B", "C", "D", "E", "F"};
    int num_complex = sizeof(complex_names) / sizeof(complex_names[0]);
    int i;
    for (i = 0; i < num_complex; i++) {
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

/**
 * Count the number of arguments in a string delimited by commas.
 *
 * @param args A string containing the arguments, delimited by commas.
 * @return The number of arguments in the string.
 */
int count_args(char args[]) {
    int num_args = 0; // Initialize the counter to 0
    char *args_copy = strdup(args); // Make a copy of the input string

    char *token = strtok(args_copy, ",");
    while (token != NULL) {
        num_args++;
        token = strtok(NULL, ",");
    }

    return num_args;
}

/**
 * Remove all whitespace characters from a string in-place.
 *
 * @param string A pointer to the string to be modified.
 */
void remove_spaces(char *string) {
    char *src = string;
    char *dst = string;
    while (*src != '\0') {
        if (!isspace(*src)) {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

/**
 * Count the number of commas in a string.
 *
 * @param str A string to be searched for commas.
 * @return The number of commas in the string.
 */
int count_commas(char *str) {
    int count = 0;
    if (str == NULL) {
        return 0;
    }
    while (*str != '\0') {
        if (*str == ',')
            count++;
        str++;
    }
    return count;
}
