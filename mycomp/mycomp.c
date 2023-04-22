#include "complex.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void parse_user_input(char *str, complex **complex_pointers);

void handle_read_comp(char *args[], complex **complex_pointers);

void handle_print_comp(char *args[], complex **complex_pointers);

void handle_add_comp(char *args[], complex **complex_pointers);

void handle_sub_comp(char *args[], complex **complex_pointers);

void handle_mult_comp_real(char *args[], complex **complex_pointers);

void handle_mult_comp_img(char *args[], complex **complex_pointers);

void handle_mult_comp_comp(char *args[], complex **complex_pointers);

void handle_abs_comp(char *args[], complex **complex_pointers);

void handle_stop(char *args[]);

int main() {
    int i;
    complex A = {0, 0};
    complex B = {0, 0};
    complex C = {0, 0};
    complex D = {0, 0};
    complex E = {0, 0};
    complex F = {0, 0};
    complex *complex_pointers[] = {&A, &B, &C, &D, &E, &F};

    char *strs[] = {"print_comp A",
                    "print_comp B",
                    "print_comp C",
                    "read_comp A, 45.1, -23.75",
                    "print_comp A",
                    "read_comp B, 54.2, 3.56",
                    "print_comp B",
                    "read_comp C, 0, -1",
                    "print_comp C",
                    "add_comp A, B",
                    "sub_comp C, A",
                    "sub_comp B, B",
                    "sub_comp D, A",
                    "mult_comp_real A, 2.51",
                    "mult_comp_img A, -2.564",
                    "mult_comp_comp A, B",
                    "mult_comp_comp E, C",
                    "abs_comp A",
                    "abs_comp B",
                    "abs_comp C",
                    "abs_comp F"
    };

    int num_strs = sizeof(strs) / sizeof(char *);

    for (i = 0; i < num_strs; i++) {
        printf("%s\n", strs[i]);
        parse_user_input(strs[i], complex_pointers);
        printf("\n");
    }

    return 0;
}

void parse_user_input(char *str, complex **complex_pointers) {
    char *copy = strdup(str);
    char *p = strtok(copy, " \n\t\v\f");
    char *command = p;
    char *args = strtok(NULL, "");

    if (str[0] == '\0') {
        printf(ERR_EMPTY_COMMAND);
        return;
    }
    if (strcmp(command, "read_comp") == 0) {
        handle_read_comp(&args, complex_pointers);
    } else if (strcmp(command, "print_comp") == 0) {
        handle_print_comp(&args, complex_pointers);
    } else if (strcmp(command, "add_comp") == 0) {
        handle_add_comp(&args, complex_pointers);
    } else if (strcmp(command, "sub_comp") == 0) {
        handle_sub_comp(&args, complex_pointers);
    } else if (strcmp(command, "mult_comp_real") == 0) {
        handle_mult_comp_real(&args, complex_pointers);
    } else if (strcmp(command, "mult_comp_img") == 0) {
        handle_mult_comp_img(&args, complex_pointers);
    } else if (strcmp(command, "mult_comp_comp") == 0) {
        handle_mult_comp_comp(&args, complex_pointers);
    } else if (strcmp(command, "abs_comp") == 0) {
        handle_abs_comp(&args, complex_pointers);
    } else if (strcmp(command, "stop") == 0) {
        handle_stop(&args);
    } else {
        printf(ERR_UNDEFINED_COMMAND);
        return;
    }
}

/**
 * Validates a string with the format "L,D,D", where L is a letter A-F, and D are decimal digits.
 *
 * @param str The string to be validated.
 *
 * @return Returns 1 if the string is valid, otherwise 0.
 */
int validate_string_letter_double_double(char *str) {
    int i = 0;
    int letter_count = 0, comma_count = 0;

    if (!str) {
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    }

    i = ignore_whitespaces(str, i);

    // check for A-F letter
    if (isalpha(str[i])) {
        char letter = str[i];
        if (letter < 'A' || letter > 'F') {
            HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
        }
        letter_count++;
    } else {
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    }
    i++;

    i = ignore_whitespaces(str, i);

    // check for comma after letter
    if (!validate_comma(str, &i)) {
        HANDLE_ERROR(ERR_MISSING_COMMA);
    }
    comma_count++;

    i = ignore_whitespaces(str, i);

    // check for first number
    if (!check_number(str, &i)) {
        HANDLE_ERROR(ERR_INVALID_PARAMETER);
    }

    i = ignore_whitespaces(str, i);

    // check for comma after first number
    if (!validate_comma(str, &i)) {
        HANDLE_ERROR(ERR_MISSING_COMMA);
    }
    comma_count++;

    i = ignore_whitespaces(str, i);

    // check for second number
    if (!check_number(str, &i)) {
        HANDLE_ERROR(ERR_INVALID_PARAMETER);
    }

    i = ignore_whitespaces(str, i);

    // check for illegal comma
    if (str[i] == ',') {
        HANDLE_ERROR(ERR_ILLEGAL_COMMA);
    }

    i = ignore_whitespaces(str, i);

    // check for extraneous text after end of command
    if (str[i])
        HANDLE_ERROR(ERR_EXTRANEOUS_TEXT);

    // check for missing parameter or multiple consecutive commas
    if (letter_count == 0 || comma_count < 2) {
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    } else if (comma_count > 2) {
        HANDLE_ERROR(ERR_MULTIPLE_CONSECUTIVE_COMMAS);
    }

    return 1;
}

/**
 * Validates a string with the format "L", where L is a letter A-F.
 *
 * @param str The string to be validated.
 *
 * @return Returns 1 if the string is valid, otherwise 0.
 */
int validate_string_letter(char *str) {
    int i = 0;

    if (!str) {
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    }

    i = ignore_whitespaces(str, i);

    // check for A-F letter
    if (isalpha(str[i])) {
        char letter = str[i];
        if (letter < 'A' || letter > 'F') {
            HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
        }
    } else {
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    }
    i++;

    i = ignore_whitespaces(str, i);

    // check for extraneous text after end of command
    if (str[i])
        HANDLE_ERROR(ERR_EXTRANEOUS_TEXT);

    return 1;
}

/**
 * Validates a string with the format "L,L", where L is a letter A-F.
 *
 * @param str The string to be validated.
 *
 * @return Returns 1 if the string is valid, otherwise 0.
 */
int validate_string_letter_letter(char *str) {
    int i = 0;
    int letter_count = 0, comma_count = 0;

    if (!str) {
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    }

    i = ignore_whitespaces(str, i);

    // check for first A-F letter
    if (isalpha(str[i])) {
        char letter = str[i];
        if (letter < 'A' || letter > 'F') {
            HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
        }
        letter_count++;
    } else {
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    }
    i++;

    i = ignore_whitespaces(str, i);

    // check for comma after first letter
    if (!validate_comma(str, &i)) {
        HANDLE_ERROR(ERR_MISSING_COMMA);
    }
    comma_count++;

    i = ignore_whitespaces(str, i);

    // check for second A-F letter
    if (isalpha(str[i])) {
        char letter = str[i];
        if (letter < 'A' || letter > 'F') {
            HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
        }
        letter_count++;
    } else {
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    }
    i++;

    i = ignore_whitespaces(str, i);

    // check for illegal comma
    if (str[i] == ',') {
        HANDLE_ERROR(ERR_ILLEGAL_COMMA);
    }

    i = ignore_whitespaces(str, i);

    // check for extraneous text after end of command
    if (str[i])
        HANDLE_ERROR(ERR_EXTRANEOUS_TEXT);

    // check for missing parameter or multiple consecutive commas
    if (letter_count < 2 || comma_count < 1) {
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    } else if (comma_count > 1) {
        HANDLE_ERROR(ERR_MULTIPLE_CONSECUTIVE_COMMAS);
    }

    return 1;
}


/**
 * Validates a string with the format "L,D", where L is a letter A-F, and D is a decimal digit.
 *
 * @param str The string to be validated.
 *
 * @return Returns 1 if the string is valid, otherwise 0.
 */
int validate_string_letter_double(char *str) {
    int i = 0;
    int letter_count = 0, comma_count = 0;

    if (!str) {
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    }

    i = ignore_whitespaces(str, i);

    // check for A-F letter
    if (isalpha(str[i])) {
        char letter = str[i];
        if (letter < 'A' || letter > 'F') {
            HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
        }
        letter_count++;
    } else {
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    }
    i++;

    i = ignore_whitespaces(str, i);

    // check for comma after letter
    if (!validate_comma(str, &i)) {
        HANDLE_ERROR(ERR_MISSING_COMMA);
    }
    comma_count++;

    i = ignore_whitespaces(str, i);

    // check for number after comma
    if (!check_number(str, &i)) {
        HANDLE_ERROR(ERR_INVALID_PARAMETER);
    }

    i = ignore_whitespaces(str, i);

    // check for illegal comma
    if (str[i] == ',') {
        HANDLE_ERROR(ERR_ILLEGAL_COMMA);
    }

    i = ignore_whitespaces(str, i);

    // check for extraneous text after end of command
    if (str[i])
        HANDLE_ERROR(ERR_EXTRANEOUS_TEXT);

    // check for missing parameter or multiple consecutive commas
    if (letter_count == 0 || comma_count == 0) {
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    } else if (comma_count > 1) {
        HANDLE_ERROR(ERR_MULTIPLE_CONSECUTIVE_COMMAS);
    }

    return 1;
}


/**
 * Validates an empty string
 *
 * @param str The string to be validated.
 *
 * @return Returns 1 if the string is empty, otherwise 0.
 */
int validate_empty(char *str) {
    if (strlen(str) == 0) {
        HANDLE_ERROR(ERR_EXTRANEOUS_TEXT);
    }
    return 1;
}


void handle_read_comp(char *args[], complex **complex_pointers) {
    if (validate_string_letter_double_double(*args)) {
        double real, imag;
        char *letter = strtok(*args, " ,");
        parse_double(strtok(NULL, " ,"), &real);
        parse_double(strtok(NULL, " ,"), &imag);

        complex **ptr_to_complex = get_complex(letter, complex_pointers);
        read_comp(*ptr_to_complex, real, imag);
    }
}

void handle_print_comp(char *args[], complex **complex_pointers) {
    if (validate_string_letter(*args)) {
        char *letter = strtok(*args, " ");
        complex **ptr_to_complex = get_complex(letter, complex_pointers);
        print_comp(**ptr_to_complex);
    }
}

void handle_add_comp(char *args[], complex **complex_pointers) {
    if (validate_string_letter_letter(*args)) {
        char *letter1 = strtok(*args, " ,");
        char *letter2 = strtok(NULL, " ");

        complex **ptr_to_complex1 = get_complex(letter1, complex_pointers);
        complex **ptr_to_complex2 = get_complex(letter2, complex_pointers);
        add_comp(**ptr_to_complex1, **ptr_to_complex2);
    }
}

void handle_sub_comp(char *args[], complex **complex_pointers) {
    if (validate_string_letter_letter(*args)) {
        char *letter1 = strtok(*args, " ,");
        char *letter2 = strtok(NULL, " ");

        complex **ptr_to_complex1 = get_complex(letter1, complex_pointers);
        complex **ptr_to_complex2 = get_complex(letter2, complex_pointers);
        sub_comp(**ptr_to_complex1, **ptr_to_complex2);
    }
}

void handle_mult_comp_real(char *args[], complex **complex_pointers) {
    if (validate_string_letter_double(*args)) {
        double num;
        char *letter = strtok(*args, " ,");
        parse_double(strtok(NULL, " ,"), &num);

        complex **ptr_to_complex = get_complex(letter, complex_pointers);
        mult_comp_real(**ptr_to_complex, num);
    }
}

void handle_mult_comp_img(char *args[], complex **complex_pointers) {
    if (validate_string_letter_double(*args)) {
        double num;
        char *letter = strtok(*args, " ,");
        parse_double(strtok(NULL, " ,"), &num);

        complex **ptr_to_complex = get_complex(letter, complex_pointers);
        mult_comp_img(**ptr_to_complex, num);
    }
}


void handle_mult_comp_comp(char *args[], complex **complex_pointers) {
    if (validate_string_letter_letter(*args)) {
        char *letter1 = strtok(*args, " ,");
        char *letter2 = strtok(NULL, " ");

        complex **ptr_to_complex1 = get_complex(letter1, complex_pointers);
        complex **ptr_to_complex2 = get_complex(letter2, complex_pointers);
        mult_comp_comp(**ptr_to_complex1, **ptr_to_complex2);
    }
}

void handle_abs_comp(char *args[], complex **complex_pointers) {
    if (validate_string_letter(*args)) {
        char *letter = strtok(*args, " ");
        complex **ptr_to_complex = get_complex(letter, complex_pointers);
        abs_comp(**ptr_to_complex);
    }
}

void handle_stop(char *args[]) {
    if (validate_empty(*args)) {
        stop();
    }
}
