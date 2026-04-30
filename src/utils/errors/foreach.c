/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** foreach error helper: put_error_var prints a tcsh-compatible
** error message to stderr when the foreach loop variable name
** is invalid (must start with a letter, alphanumeric + _ only).
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../../include/c_zsh.h"

int put_error_var(char *var)
{
    my_putstr(var);
    my_putstr(": Undefined variable.\n");
    return FAILURE;
}
