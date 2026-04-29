/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Bounded comparison: compares at most n characters of s1 and s2;
** returns 0 if the first n chars are identical, or the numeric
** difference at the first mismatch; stops at null terminator.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

int my_strncmp(char *s1, char *s2, int n)
{
    int i = 0;

    while (s1[i] == s2[i]) {
        if (s1[i] == '\0' || i == n - 1)
            return SUCCESS;
        i++;
    }
    return s1[i] - s2[i];
}
