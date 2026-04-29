/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** String length: iterates the string until the null terminator
** and returns the character count before it.
** Returns 0 if the input pointer is NULL.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
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
