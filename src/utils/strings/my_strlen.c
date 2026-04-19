/*
** EPITECH PROJECT, 2026
** my_strlen
** File description:
** my_strlne
*/

#include "c_zsh.h"

int my_strlen(char *str)
{
    int i = 0;

    if (!str)
        return 0;
    for (; str[i] != '\0'; i++);
    return i;
}
