/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Public API for utilities: string helpers (strlen, strdup,
** strcmp, strconcat, strstr, word arrays), I/O helpers
** (putstr, putnbr, openator), display and validation helpers.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#ifndef UTILS_H
    #define UTILS_H
    #include "../config/czshrc.h"
    #include <time.h>

int my_strlen(char *str);
void my_putstr(char *str);
void my_putstrerror(char *str);
char *my_strdup(char *str);
int my_strcmp(char *s1, char *s2);
int my_strncmp(char *s1, char *s2, int n);
char *my_strconcat(char *str1, char *str2);
const char *my_strstr(const char *str, const char *to_f);
char **my_str_to_word_array(char *str, char *separator);
char **my_str_to_word_array_quote(char *str, char *separator);
char ***my_str_to_array_of_word_array(char const *str, char const *sep_ext,
    char const *sep_int);
int my_wordarray_len(char **word_array);
int my_char_isnum(char *str);
int my_str_is_alphanum(char *key);
int get_file_size_stat(char const *filepath);
char *openator(char const *filepath);
char *get_folder(void);
char *get_branch_git(void);
int my_char_is_alpha(char key);
void display_prompt(prompt_t *prompt, char *user);
int my_putnbr(int nb);
void display_time(infos_t *time_info, infos_t *date, date_format_t date_format,
    int len_prompt);
int len_nb(int nb);
void display_zero(int nb);
char *my_itoa(int num);
void print_fg_color(int color);
void print_bg_color(int b_color);
void long_date_format(struct tm *tm);
void european_date_format(struct tm *tm);
void us_date_format(struct tm *tm);
void iso_date_format(struct tm *tm);
char *my_word_array_to_str(char **array);

#endif
