/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** history builtin: iterates the history_cmd_t doubly-linked list
** from oldest to newest and prints each entry as:
**   ID  HH:MM  command
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
