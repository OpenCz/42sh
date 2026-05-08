/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** utils
*/

#ifndef UTILS_H
    #define UTILS_H
char *openator(char const *filepath);
void free_alloc(void *object);
void free_array(char **array);
int get_file_size_stat(char const *filepath);
char **my_str_to_word_array(char *str, char *separator);
char ***my_str_to_array_of_word_array(char const *str, char const *sep_ext,
    char const *sep_int);
#endif
