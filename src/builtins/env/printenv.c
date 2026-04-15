/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** The printenv.c
*/
/**
 * @file printenv.c
 * @brief The printenv.c
 * @author Erwan Lo Presti
 */

#include "c_zsh.h"

int printenv(main_t *main_stock, command_ctx_t *ctx)
{
    if (my_wordarray_len(ctx->arg_command) != 1) {
        my_putstrerror("printenv: Too many arguments.\n");
        return 1;
    }
    for (env_t *tmp = main_stock->stock_env; tmp != NULL; tmp = tmp->next) {
        if (strcmp(tmp->key, ctx->arg_command[0]) == 0) {
            my_putstr(tmp->value);
            my_putstr("\n");
            return SUCCESS;
        }
    }
    return 1;
}

int builtin_printenv(main_t *main_stock, command_ctx_t *ctx)
{
    if (!ctx->arg_command[0]) {
        my_env(main_stock);
        return SUCCESS;
    }
    return printenv(main_stock, ctx);
}
