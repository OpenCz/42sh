/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/utils/strings
** File description:
** error.c
*/

#include "c_zsh.h"

void *unmatched_quote(int in_quotes, char **word_array)
{
    free_array(word_array);
    if (in_quotes == 2)
        my_putstrerror("Unmatched '''.\n");
    else
        my_putstrerror("Unmatched '\"'.\n");
    return NULL;
}
