/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Alphabetic check: my_char_is_alpha returns SUCCESS(0) if the
** character is in [a-z] or [A-Z], used by setenv to validate
** that the key name starts with a letter (tcsh rule).
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../../include/c_zsh.h"

int my_char_is_alpha(char key)
{
    if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z'))
        return SUCCESS;
    return 1;
}
