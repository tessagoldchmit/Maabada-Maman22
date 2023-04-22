#include "complex.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void parse_user_input(char *str, complex **complex_pointers);

void handle_read_comp(char *args[], complex **complex_pointers);


int main() {
    complex A = {0, 0};
    complex B = {0, 0};
    complex C = {0, 0};
    complex D = {0, 0};
    complex E = {0, 0};
    complex F = {0, 0};
    complex *complex_pointers[] = {&A, &B, &C, &D, &E, &F};

/*    char str1[] = "read_comp A, 2.4, 3.2";
    printf("%s\n", str1);
    parse_user_input(str1, complex_pointers);
    printf("\n");*/

    char str2[] = "read_comp D, a, 3";
    printf("%s\n", str2);
    parse_user_input(str2, complex_pointers);
    printf("\n");

    char str3[] = "read_comp A, 2";
    printf("%s\n", str3);
    parse_user_input(str3, complex_pointers);
    printf("\n");

    char str4[] = "read_comp A, 2 3";
    printf("%s\n", str4);
    parse_user_input(str4, complex_pointers);
    printf("\n");

    char str5[] = "read_comp A 2, 3";
    printf("%s\n", str5);
    parse_user_input(str5, complex_pointers);
    printf("\n");

    char str6[] = "read_comp G, 2, 3";
    printf("%s\n", str6);
    parse_user_input(str6, complex_pointers);
    printf("\n");

    char str7[] = "read_comp, A, 2, 3";
    printf("%s\n", str7);
    parse_user_input(str7, complex_pointers);
    printf("\n");


    char str8[] = "read_comp";
    printf("%s\n", str8);
    parse_user_input(str8, complex_pointers);
    printf("\n");

    return 0;
}


void parse_user_input(char *str, complex **complex_pointers) {
    char *p = strtok(str, " \n\t\v\f");
    char *command = p;
    char *args = strtok(NULL, "");

    if (str[0] == '\0') {
        printf(ERR_EMPTY_COMMAND);
        return;
    }
    if (strcmp(command, "read_comp") == 0) {
        handle_read_comp(&args, complex_pointers);
    } else {
        printf(ERR_UNDEFINED_COMMAND);
        return;
    }
}


int validate_string(char *str) {
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
    if (str[i]) {
        HANDLE_ERROR(ERR_EXTRANEOUS_TEXT);
    }

    // check for missing parameter or multiple consecutive commas
    if (letter_count == 0 || comma_count < 2) {
        HANDLE_ERROR(ERR_MISSING_PARAMETER);
    } else if (comma_count > 2) {
        HANDLE_ERROR(ERR_MULTIPLE_CONSECUTIVE_COMMAS);
    }

    return 1;
}

void handle_read_comp(char *args[], complex **complex_pointers) {
    if (validate_string(*args)) {
        double real, imag;
        char *letter = strtok(*args, " ,");
        parse_double(strtok(NULL, " ,"), &real);
        parse_double(strtok(NULL, " ,"), &imag);

        complex **ptr_to_complex = get_complex(letter, complex_pointers);
        read_comp(*ptr_to_complex, real, imag);
    }
}