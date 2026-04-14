/*
** EPITECH PROJECT, 2026
** my_strlen
** File description:
** my_strlne
*/

#include "42sh.h"

int my_strlen(char *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++);
    return i;
}
