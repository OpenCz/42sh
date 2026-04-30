/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Full key name check: my_str_is_alphanum returns 1 if every
** character is a letter, digit, or underscore, used by setenv
** to validate the complete variable key name.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

int my_str_is_alphanum(char *key)
{
    int i = 0;

    while (key[i] != '\0') {
        if (!((key[i] >= '0' && key[i] <= '9') ||
                (key[i] >= 'A' && key[i] <= 'Z') ||
                (key[i] >= 'a' && key[i] <= 'z'))) {
            return 1;
        }
        i++;
    }
    return SUCCESS;
}
