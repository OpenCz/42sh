/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Digit-prefix check: my_char_isnum returns 1 if the first char
** of the string is in [0-9], used by the repeat builtin to
** validate the count argument before calling atoi().
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

int my_char_isnum(char *str)
{
    int i = 0;

    if (str[i] >= 48 && str[i] <= 57)
        return 1;
    return SUCCESS;
}
