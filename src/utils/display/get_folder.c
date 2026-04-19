/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** The get_folder.c
*/

#include "c_zsh.h"
#include <unistd.h>

char *get_folder(void)
{
    char *pwd = getcwd(NULL, 0);
    char *folder = NULL;
    char **array = my_str_to_word_array(pwd, "/");

    if (!array || !pwd) {
        if (pwd)
            free(pwd);
        if (array)
            free_array(array);
        return NULL;
    }
    folder = my_strdup(array[my_wordarray_len(array) - 1]);
    if (!folder) {
        free_array(array);
        free(pwd);
        return NULL;
    }
    free_array(array);
    free(pwd);
    return folder;
}
