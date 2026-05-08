/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/pre-release/minishell
** File description:
** mysh
*/

#ifndef CROCUS_H
    #define CROCUS_H

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

typedef struct number_s {
    char *line1;
    char *line2;
    char *line3;
    char *line4;
    char *line5;
} number_t;

typedef struct tables_s {
    char number;
    number_t* (*func)(void);
} tables_t;

typedef struct crocus_s {
    char *string;
    char *number;
    int is_string_arg;
    int is_number_arg;
} crocus_t;

int my_str_isnum(char const *str);
int free_crocus(crocus_t *crocus);
int my_str_isprintable(char const *str);
int fill_null_string(crocus_t *crocus);
int check_args(int argc, char **argv, crocus_t *crocus);
crocus_t *init_crocus(void);

number_t *zero(void);
number_t *one(void);
number_t *two(void);
number_t *three(void);
number_t *four(void);
number_t *five(void);
number_t *six(void);
number_t *seven(void);
number_t *eight(void);
number_t *nine(void);
int free_number(number_t *number);
int change_letter(crocus_t *crocus, number_t **numbers);
int crocus(int argc, char **argv);

#endif
