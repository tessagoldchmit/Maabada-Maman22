#include "complex.h"
#include "utils.h"
#include <ctype.h>
#include <string.h>

void parse_user_input(char *str, complex **complex_pointers);

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

    /* Allocate memory for the variables */
    complex *A = (complex *) malloc(sizeof(complex));
    complex *B = (complex *) malloc(sizeof(complex));
    complex *C = (complex *) malloc(sizeof(complex));
    complex *D = (complex *) malloc(sizeof(complex));
    complex *E = (complex *) malloc(sizeof(complex));
    complex *F = (complex *) malloc(sizeof(complex));

    /* Initialize the variables */
    A->real = 0;
    A->imag = 0;
    B->real = 0;
    B->imag = 0;
    C->real = 0;
    C->imag = 0;
    D->real = 0;
    D->imag = 0;
    E->real = 0;
    E->imag = 0;
    F->real = 0;
    F->imag = 0;

    /* Allocate memory for the pointers and initialize them with zeros */
    complex_pointers = (complex **) calloc(6, sizeof(complex *));

    /* Initialize the pointers */
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

        printf("> %s\n", input);
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

void parse_user_input(char *str, complex **complex_pointers) {
    char* copy = copy_string(str);
    char *p = strtok(copy, " \n\t\v\f");

    char *command = p;
    char *args = strtok(NULL, "");

    if (str[0] == '\0') {
        printf(ERR_EMPTY_COMMAND);
        free(copy); /*  free the memory allocated by copy_string() */
        return;
    }

    if (command[strlen(command) - 1] == ',') {
        printf(ERR_ILLEGAL_COMMA);
        free(copy); /*  free the memory allocated by copy_string() */
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
        handle_stop(&args, complex_pointers);
    } else {
        printf(ERR_UNDEFINED_COMMAND);
        free(copy); /*  free the memory allocated by copy_string() */
        return;
    }
    free(copy); /*  free the memory allocated by copy_string() */
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

    /* check for A-F letter */
    if (isalpha(str[i])) {
        char letter = str[i];
        if (letter < 'A' || letter > 'F') {
            HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
        }
        letter_count++;
    } else if (validate_comma(str, &i)) {
        HANDLE_ERROR(ERR_ILLEGAL_COMMA);
    } else {
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    }
    i++;

    i = ignore_whitespaces(str, i);

    /* check for comma after letter */
    if (!validate_comma(str, &i)) {
        HANDLE_ERROR(ERR_MISSING_COMMA);
    }
    comma_count++;

    i = ignore_whitespaces(str, i);

    /* check for first number */
    if (!check_number(str, &i)) {
        HANDLE_ERROR(ERR_INVALID_PARAMETER);
    }

    i = ignore_whitespaces(str, i);

    /* check for comma after first number */
    if (!validate_comma(str, &i)) {
        HANDLE_ERROR(ERR_MISSING_COMMA);
    }
    comma_count++;

    i = ignore_whitespaces(str, i);

    /* check for second number */
    if (!check_number(str, &i)) {
        HANDLE_ERROR(ERR_INVALID_PARAMETER);
    }

    i = ignore_whitespaces(str, i);

    /* check for illegal comma */
    if (str[i] == ',') {
        HANDLE_ERROR(ERR_ILLEGAL_COMMA);
    }

    i = ignore_whitespaces(str, i);

    /* check for extraneous text after end of command */
    if (str[i])
        HANDLE_ERROR(ERR_EXTRANEOUS_TEXT);

    /* check for missing parameter or multiple consecutive commas */
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

    /* check for A-F letter */
    if (isalpha(str[i])) {
        char letter = str[i];
        if (letter < 'A' || letter > 'F') {
            HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
        }
    } else {
        HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
    }
    i++;

    i = ignore_whitespaces(str, i);

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
    int letter_count = 0, comma_count = 0;

    if (!str) {
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    }

    i = ignore_whitespaces(str, i);

    /* check for first A-F letter */
    if (isalpha(str[i])) {
        char letter = str[i];
        if (letter < 'A' || letter > 'F') {
            HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
        }
        letter_count++;
    } else if (validate_comma(str, &i)) {
        HANDLE_ERROR(ERR_MULTIPLE_CONSECUTIVE_COMMAS);
    } else {
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    }
    i++;

    i = ignore_whitespaces(str, i);

    /* check for comma after first letter */
    if (!validate_comma(str, &i)) {
        HANDLE_ERROR(ERR_MISSING_COMMA);
    }
    comma_count++;

    i = ignore_whitespaces(str, i);

    /* check for second A-F letter */
    if (isalpha(str[i])) {
        char letter = str[i];
        if (letter < 'A' || letter > 'F') {
            HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
        }
        letter_count++;
    } else if (validate_comma(str, &i)) {
        HANDLE_ERROR(ERR_MULTIPLE_CONSECUTIVE_COMMAS);
    } else {
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    }
    i++;

    i = ignore_whitespaces(str, i);

    /* check for illegal comma */
    if (str[i] == ',') {
        HANDLE_ERROR(ERR_ILLEGAL_COMMA);
    }

    i = ignore_whitespaces(str, i);

    /* check for extraneous text after end of command */
    if (str[i])
        HANDLE_ERROR(ERR_EXTRANEOUS_TEXT);

    /* check for missing parameter or multiple consecutive commas */
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

    /* check for A-F letter */
    if (isalpha(str[i])) {
        char letter = str[i];
        if (letter < 'A' || letter > 'F') {
            HANDLE_ERROR(ERR_UNDEFINED_COMPLEX_VAR);
        }
        letter_count++;
    } else if (validate_comma(str, &i)) {
        HANDLE_ERROR(ERR_MULTIPLE_CONSECUTIVE_COMMAS);
    } else {
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    }
    i++;

    i = ignore_whitespaces(str, i);

    /* check for comma after letter */
    if (!validate_comma(str, &i)) {
        HANDLE_ERROR(ERR_MISSING_COMMA);
    }
    comma_count++;

    i = ignore_whitespaces(str, i);

    /* check for number after comma */
    if (!check_number(str, &i)) {
        HANDLE_ERROR(ERR_INVALID_PARAMETER);
    }

    i = ignore_whitespaces(str, i);

    /* check for illegal comma */
    if (str[i] == ',') {
        HANDLE_ERROR(ERR_ILLEGAL_COMMA);
    }

    i = ignore_whitespaces(str, i);

    /* check for extraneous text after end of command */
    if (str[i])
        HANDLE_ERROR(ERR_EXTRANEOUS_TEXT);

    /* check for missing parameter or multiple consecutive commas */
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
        parse_double(strtok(NULL, " ,"), &real);
        parse_double(strtok(NULL, " ,"), &imag);

        ptr_to_complex = get_complex(letter, complex_pointers);
        read_comp(*ptr_to_complex, real, imag);
    }
}

void handle_print_comp(char *args[], complex **complex_pointers) {
    if (validate_string_letter(*args)) {
        complex **ptr_to_complex;
        char *letter = strtok(*args, " ");
        ptr_to_complex = get_complex(letter, complex_pointers);
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
        complex **ptr_to_complex;
        double num;
        char *letter = strtok(*args, " ,");
        parse_double(strtok(NULL, " ,"), &num);

        ptr_to_complex = get_complex(letter, complex_pointers);
        mult_comp_real(**ptr_to_complex, num);
    }
}

void handle_mult_comp_img(char *args[], complex **complex_pointers) {
    if (validate_string_letter_double(*args)) {
        complex **ptr_to_complex;

        double num;
        char *letter = strtok(*args, " ,");
        parse_double(strtok(NULL, " ,"), &num);

        ptr_to_complex = get_complex(letter, complex_pointers);
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

void handle_stop(char *args[], complex **complex_pointers) {
    if (validate_empty(*args)) {
        stop(complex_pointers);
    }
}
