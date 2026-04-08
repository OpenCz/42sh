/*
** EPITECH PROJECT, 2026
** my_ischar
** File description:
** num
*/

#include "minishell.h"

int my_char_isnum(char *str)
{
    int i = 0;

    if (str[i] >= 48 && str[i] <= 57)
        return 1;
    return SUCCESS;
}
