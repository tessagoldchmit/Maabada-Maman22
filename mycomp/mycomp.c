#include "complex.h"
#include "utils.h"
#include <ctype.h>
#include <string.h>

int parse_user_input(char *str, complex **complex_pointers);

void handle_read_comp(char *args[], complex **complex_pointers);

void handle_print_comp(char *args[], complex **complex_pointers);

void handle_add_comp(char *args[], complex **complex_pointers);

void handle_sub_comp(char *args[], complex **complex_pointers);

void handle_mult_comp_real(char *args[], complex **complex_pointers);

void handle_mult_comp_img(char *args[], complex **complex_pointers);

void handle_mult_comp_comp(char *args[], complex **complex_pointers);

void handle_abs_comp(char *args[], complex **complex_pointers);

void handle_stop(char *args[], complex **complex_pointers);

int main() {
    complex **complex_pointers;
    char input[100];
    int i;

/* Allocate memory for the variables and initialize them to zero */
    complex *A = (complex *) calloc(1, sizeof(complex));
    complex *B = (complex *) calloc(1, sizeof(complex));
    complex *C = (complex *) calloc(1, sizeof(complex));
    complex *D = (complex *) calloc(1, sizeof(complex));
    complex *E = (complex *) calloc(1, sizeof(complex));
    complex *F = (complex *) calloc(1, sizeof(complex));

/* Allocate memory for the pointers and initialize them with the variable addresses */
    complex_pointers = (complex **) calloc(6, sizeof(complex *));
    complex_pointers[0] = A;
    complex_pointers[1] = B;
    complex_pointers[2] = C;
    complex_pointers[3] = D;
    complex_pointers[4] = E;
    complex_pointers[5] = F;

    while (1) {
        printf("> ");
        if (!fgets(input, sizeof(input), stdin)) {
            break;  /* End of file or error occurred */
        }

        /* Trim trailing newline character */
        input[strcspn(input, "\n")] = 0;

        printf("%s\n", input);
        parse_user_input(input, complex_pointers);
        printf("\n");
    }

    /* Free the memory */
    for (i = 0; i < 6; i++) {
        free(complex_pointers[i]);
    }
    free(complex_pointers);

    return 0;
}

int parse_user_input(char *str, complex **complex_pointers) {
    char *command = strtok(str, " \n\t\v\f");
    char *args = strtok(NULL, "");
    char *valid_commands[NUM_COMMANDS] = VALID_COMMANDS;
    int i;

    if (command == NULL || command[0] == '\0') {
        HANDLE_ERROR(ERR_EMPTY_COMMAND);
    }

    if (command[strlen(command) - 1] == ',') {
        for (i = 0; i < NUM_COMMANDS; i++) {
            if (strncmp(command, valid_commands[i], strlen(valid_commands[i]) - 1) == 0) {
                HANDLE_ERROR(ERR_ILLEGAL_COMMA_AFTER_COMMAND_NAME);
            }
        }
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
        handle_stop(&args, complex_pointers);
    } else {
        HANDLE_ERROR(ERR_UNDEFINED_COMMAND);
    }
    return 1;
}

/**
 * Validates a string with the format "L,D,D", where L is a letter A-F, and D are decimal digits.
 *
 * @param str The string to be validated.
 *
 * @return Returns 1 if the string is valid, otherwise 0.
 */
int validate_string_letter_double_double(char *str) {
    int i = 0, j;

    if (!str) {
        HANDLE_ERROR(ERR_ALL_PARAMETERS_MISSING);
    }

    i = ignore_whitespaces(str, i);

    /* check for A-F letter */
    if (isalpha(str[i])) {
        char letter = str[i];
        if (letter < 'A' || letter > 'F') {
            HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
        }
    } else if (is_comma(str, &i)) {
        HANDLE_ERROR(ERR_ILLEGAL_COMMA_AFTER_COMMAND_NAME);
    } else {
        HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
    }
    i++;
    i = ignore_whitespaces(str, i);

    /* check for comma after letter */
    if (!is_comma(str, &i))
        HANDLE_ERROR(ERR_MISSING_COMMA);
    i = ignore_whitespaces(str, i);

    /* check for first number */
    if (i > strlen(str) - 1)
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    if (is_comma(str, &i))
        HANDLE_ERROR(ERR_MULTIPLE_CONSECUTIVE_COMMAS);
    else if (!is_number(str, &i))
        HANDLE_ERROR(ERR_INVALID_REAL_PARAMETER);
    i = ignore_whitespaces(str, i);

    /* check for comma after first number */
    if (!is_comma(str, &i)) {
        if (i >= strlen(str) - 1)
            HANDLE_ERROR(ERR_MISSING_COMMA);
        HANDLE_ERROR(ERR_INVALID_REAL_PARAMETER);
    }
    i = ignore_whitespaces(str, i);

    /* check for second number */
    if (is_comma(str, &i))
        HANDLE_ERROR(ERR_MULTIPLE_CONSECUTIVE_COMMAS);
    else if (!is_number(str, &i))
        HANDLE_ERROR(ERR_INVALID_IMAGINARY_PARAMETER);
    if (i != strlen(str)) {
        j = i;
        i = ignore_whitespaces(str, i);

        if (str[i]==',')
            HANDLE_ERROR(ERR_ILLEGAL_COMMA);

        if (i == j)
            HANDLE_ERROR(ERR_INVALID_IMAGINARY_PARAMETER);

        /* check for extraneous text after end of command */
        if (str[i])
            HANDLE_ERROR(ERR_EXTRANEOUS_TEXT);
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
        HANDLE_ERROR(ERR_ALL_PARAMETERS_MISSING);
    }

    i = ignore_whitespaces(str, i);

    /* check for A-F letter */
    if (isalpha(str[i])) {
        char letter = str[i];
        if (letter < 'A' || letter > 'F') {
            HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
        }
    } else if (is_comma(str, &i)) {
        HANDLE_ERROR(ERR_ILLEGAL_COMMA_AFTER_COMMAND_NAME);
    } else {
        HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
    }
    i = ignore_whitespaces(str, ++i);

    /* check for extraneous text after end of command */
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

    if (!str)
        HANDLE_ERROR(ERR_ALL_PARAMETERS_MISSING);
    i = ignore_whitespaces(str, i);

    /* check for A-F letter */
    if (isalpha(str[i])) {
        char letter = str[i];
        if (letter < 'A' || letter > 'F')
            HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
    } else if (is_comma(str, &i)) {
        HANDLE_ERROR(ERR_ILLEGAL_COMMA_AFTER_COMMAND_NAME);
    } else {
        HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
    }
    i = ignore_whitespaces(str, ++i);

    /* check for comma after letter */
    if (!is_comma(str, &i)) {
        if (i >= strlen(str) - 1)
            HANDLE_ERROR(ERR_MISSING_COMMA);
        HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
    }
    i = ignore_whitespaces(str, i);

    if (i > strlen(str) - 1)
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    if (is_comma(str, &i))
        HANDLE_ERROR(ERR_MULTIPLE_CONSECUTIVE_COMMAS);

    /* check for A-F letter */
    if (isalpha(str[i])) {
        char letter = str[i];
        if (letter < 'A' || letter > 'F')
            HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
    } else if (is_comma(str, &i)) {
        HANDLE_ERROR(ERR_ILLEGAL_COMMA_AFTER_COMMAND_NAME);
    } else {
        HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
    }
    i = ignore_whitespaces(str, ++i);

    /* check for extraneous text after end of command */
    if (str[i])
        HANDLE_ERROR(ERR_EXTRANEOUS_TEXT);

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

    if (!str)
        HANDLE_ERROR(ERR_ALL_PARAMETERS_MISSING);
    i = ignore_whitespaces(str, i);

    /* check for A-F letter */
    if (isalpha(str[i])) {
        char letter = str[i];
        if (letter < 'A' || letter > 'F') {
            HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
        }
    } else if (is_comma(str, &i)) {
        HANDLE_ERROR(ERR_ILLEGAL_COMMA_AFTER_COMMAND_NAME);
    } else {
        HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
    }
    i++;
    i = ignore_whitespaces(str, i);

    /* check for comma after letter */
    if (!is_comma(str, &i))
        HANDLE_ERROR(ERR_MISSING_COMMA);
    i = ignore_whitespaces(str, i);

    /* check for first number */
    if (i > strlen(str) - 1)
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    if (is_comma(str, &i))
        HANDLE_ERROR(ERR_MULTIPLE_CONSECUTIVE_COMMAS);
    else if (!is_number(str, &i))
        HANDLE_ERROR(ERR_INVALID_PARAMETER);
    i = ignore_whitespaces(str, i);

    /* check for extraneous text after end of command */
    if (str[i])
        HANDLE_ERROR(ERR_EXTRANEOUS_TEXT);

    return 1;
}


/**
 * Validates an empty string
 *
 * @param str The string to be validated.
 *
 * @return Returns 1 if the string is empty, otherwise 0.
 */
int validate_empty(const char *str) {
    if (str != NULL) {
        HANDLE_ERROR(ERR_EXTRANEOUS_TEXT);
    }
    return 1;
}


void handle_read_comp(char *args[], complex **complex_pointers) {
    if (validate_string_letter_double_double(*args)) {
        complex **ptr_to_complex;
        double real, imag;
        char *letter = strtok(*args, " ,");
        char *endptr;
        real = strtod(strtok(NULL, " ,"), &endptr);
        imag = strtod(strtok(NULL, " ,"), &endptr);

        ptr_to_complex = get_complex(letter, complex_pointers);
        read_comp(*ptr_to_complex, real, imag);
        LOG_INFO("read_comp");
    }
}

void handle_print_comp(char *args[], complex **complex_pointers) {
    if (validate_string_letter(*args)) {
        complex **ptr_to_complex;
        char *letter = strtok(*args, " ");
        ptr_to_complex = get_complex(letter, complex_pointers);
        print_comp(**ptr_to_complex);
        LOG_INFO("print_comp");
    }
}

void handle_add_comp(char *args[], complex **complex_pointers) {
    if (validate_string_letter_letter(*args)) {
        char *letter1 = strtok(*args, " ,");
        char *letter2 = strtok(NULL, " ");

        complex **ptr_to_complex1 = get_complex(letter1, complex_pointers);
        complex **ptr_to_complex2 = get_complex(letter2, complex_pointers);
        add_comp(**ptr_to_complex1, **ptr_to_complex2);
        LOG_INFO("add_comp");
    }
}

void handle_sub_comp(char *args[], complex **complex_pointers) {
    if (validate_string_letter_letter(*args)) {
        char *letter1 = strtok(*args, " ,");
        char *letter2 = strtok(NULL, " ");

        complex **ptr_to_complex1 = get_complex(letter1, complex_pointers);
        complex **ptr_to_complex2 = get_complex(letter2, complex_pointers);
        sub_comp(**ptr_to_complex1, **ptr_to_complex2);
        LOG_INFO("sub_comp");
    }
}

void handle_mult_comp_real(char *args[], complex **complex_pointers) {
    if (validate_string_letter_double(*args)) {
        complex **ptr_to_complex;
        double num;
        char *letter = strtok(*args, " ,");
        char *endptr;
        num = strtod(strtok(NULL, " ,"), &endptr);

        ptr_to_complex = get_complex(letter, complex_pointers);
        mult_comp_real(**ptr_to_complex, num);
        LOG_INFO("mult_comp_real");
    }
}

void handle_mult_comp_img(char *args[], complex **complex_pointers) {
    if (validate_string_letter_double(*args)) {
        complex **ptr_to_complex;

        double num;
        char *letter = strtok(*args, " ,");
        char *endptr;
        num = strtod(strtok(NULL, " ,"), &endptr);

        ptr_to_complex = get_complex(letter, complex_pointers);
        mult_comp_img(**ptr_to_complex, num);
        LOG_INFO("mult_comp_img");
    }
}


void handle_mult_comp_comp(char *args[], complex **complex_pointers) {
    if (validate_string_letter_letter(*args)) {
        char *letter1 = strtok(*args, " ,");
        char *letter2 = strtok(NULL, " ");

        complex **ptr_to_complex1 = get_complex(letter1, complex_pointers);
        complex **ptr_to_complex2 = get_complex(letter2, complex_pointers);
        mult_comp_comp(**ptr_to_complex1, **ptr_to_complex2);
        LOG_INFO("mult_comp_comp");
    }
}

void handle_abs_comp(char *args[], complex **complex_pointers) {
    if (validate_string_letter(*args)) {
        char *letter = strtok(*args, " ");
        complex **ptr_to_complex = get_complex(letter, complex_pointers);
        abs_comp(**ptr_to_complex);
        LOG_INFO("abs_comp");
    }
}

void handle_stop(char *args[], complex **complex_pointers) {
    if (validate_empty(*args)) {
        stop(complex_pointers);
    }
}
