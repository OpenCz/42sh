/*
** EPITECH PROJECT, 2026
** minishell
** File description:
** shell
*/

#include "minishell.h"

int builtin_history(main_t *main_stock, command_ctx_t *ctx)
{
    char *file = openator("history.txt");

    if (!file)
        return 1;
    printf("%s", file);
    return 0;
}
