/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** String comparison (NULL-safe): iterates both strings and
** returns 0 when all chars match through the null terminator,
** or the difference of the first differing characters.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

int my_strcmp(char *s1, char *s2)
{
    int i = 0;

    if (s1 == NULL || s2 == NULL)
        return -1;
    while (s1[i] == s2[i]) {
        if (s1[i] == '\0')
            return SUCCESS;
        i++;
    }
    return s1[i] - s2[i];
}
