/*
** EPITECH PROJECT, 2026
** minishell
** File description:
** shell
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
