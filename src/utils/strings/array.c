/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/utils/strings
** File description:
** array.c
*/

#include "c_zsh.h"

int len_array(char **array)
{
    int i = 0;

    if (!array)
        return 0;
    for (; array[i] != NULL; i++);
    return i;
}

void append_array(char ***array, char *name)
{
    char **new_array = NULL;
    int len = len_array(*array);

    if (!(*array)) {
        *array = malloc(sizeof(char *) * 2);
        if (!*array)
            return;
        (*array)[0] = strdup(name);
        (*array)[1] = NULL;
    } else {
        new_array = realloc(*array, sizeof(char *) * (len + 2));
        if (!new_array)
            return;
        *array = new_array;
        (*array)[len] = strdup(name);
        (*array)[len + 1] = NULL;
    }
}

void append_array_to_array(char ***array, char **array2)
{
    char **new_array = NULL;
    int idx = 0;
    int len_array1 = len_array(*array);
    int len_array2 = len_array(array2);

    if (!array2)
        return;
    if (!(*array)) {
        *array = array2;
        return;
    }
    new_array = realloc(*array, sizeof(char *) * (len_array1 + len_array2 + 1));
    if (!new_array)
        return;
    *array = new_array;
    for (; array2[idx] != NULL; idx++)
        (*array)[len_array1 + idx] = array2[idx];
    (*array)[len_array1 + idx] = NULL;
    free_alloc(array2);
}
