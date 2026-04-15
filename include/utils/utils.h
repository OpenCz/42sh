/*
** EPITECH PROJECT, 2026
** minishell
** File description:
** utils api
*/

#ifndef UTILS_H
    #define UTILS_H

typedef struct word_state_s {
    int in_word;
    int count;
    int in_quotes;
} word_state_t;
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
int my_wordarray_len(char **word_array);
int my_char_isnum(char *str);
int my_str_is_alphanum(char *key);
int get_file_size_stat(char const *filepath);
char *openator(char const *filepath);
char *get_folder(void);
char *get_branch_git(void);
void display_prompt(void);

#endif
