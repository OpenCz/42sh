/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** foreach error helper: put_error_var prints "VAR: Undefined variable."
** to stdout via my_putstr and returns FAILURE; called when a loop
** variable cannot be resolved during foreach execution.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../../include/c_zsh.h"

int put_error_var(char *var)
{
    my_putstr(var);
    my_putstr(": Undefined variable.\n");
    return FAILURE;
}
