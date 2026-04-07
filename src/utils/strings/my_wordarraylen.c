/*
** EPITECH PROJECT, 2026
** wordarray
** File description:
** len
*/

#include "minishell.h"

int my_wordarray_len(char **word_array)
{
    int i = 0;

    for (i = 0; word_array[i] != NULL; i++);
    return i;
}
