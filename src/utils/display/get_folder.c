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

static void *free_items(char *pwd, char **array)
{
    free_alloc(pwd);
    free_array(array);
    return NULL;
}

char *get_folder(void)
{
    char *pwd = getcwd(NULL, 0);
    char *folder = NULL;
    char **array = my_str_to_word_array(pwd, "/");

    if (!array || !pwd)
        return free_items(pwd, array);
    folder = my_strdup(array[my_wordarray_len(array) - 1]);
    if (!folder)
        return free_items(pwd, array);
    free_items(pwd, array);
    return folder;
}
