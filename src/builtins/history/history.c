/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** history builtin: opens ~/.c_zsh_history with openator() and prints
** its full content to stdout; entries are written by manage_history
** in the format "   ID\tHH:MM\tcommand" on each command execution.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

int builtin_history(main_t *main_stock, command_ctx_t *ctx)
{
    char *file = openator(".c_zsh_history");

    if (!file)
        return 1;
    printf("%s", file);
    free(file);
    return 0;
}
