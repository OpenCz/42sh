/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/42sh/src/utils/validation
** File description:
** my_str_is_alpha
*/

#include "c_zsh.h"

int my_str_is_alpha(char *key)
{
    int i = 0;

    while (key[i] != '\0') {
        if (key[i] < '0' || key[i] > '9')
            return 1;
        i++;
    }
    return SUCCESS;
}
