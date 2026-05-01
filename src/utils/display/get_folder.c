/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Working directory for the prompt: get_folder calls getcwd()
** then shortens the path to its last two components
** (e.g. 'project/src') for a compact prompt appearance.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"
#include <unistd.h>

static char *free_value(char *value, char **array, char *return_value)
{
    free(value);
    free_array(array);
    return return_value;
}

char *get_folder(void)
{
    char *pwd = getcwd(NULL, 0);
    char *folder = NULL;
    char **array = NULL;
    int len = 0;

    if (!pwd)
        return NULL;
    array = my_str_to_word_array(pwd, "/");
    if (!array) {
        free(pwd);
        return NULL;
    }
    len = my_wordarray_len(array);
    if (len == 0) {
        return free_value(pwd, array, NULL);
    }
    folder = my_strdup(array[len - 1]);
    if (!folder) {
        return free_value(pwd, array, NULL);
    }
    return free_value(pwd, array, folder);
}
