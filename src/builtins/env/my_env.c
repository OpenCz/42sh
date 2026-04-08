/*
** EPITECH PROJECT, 2026
** my_env
** File description:
** my_env
*/

#include "minishell.h"

int my_env(main_t *main_stock)
{
    for (env_t *tmp = main_stock->stock_env; tmp; tmp = tmp->next) {
        my_putstr(tmp->key);
        my_putstr("=");
        if (tmp->value)
            my_putstr(tmp->value);
        my_putstr("\n");
    }
    return SUCCESS;
}

int builtin_env(main_t *main_stock, command_ctx_t *ctx)
{
    (void)ctx;
    return my_env(main_stock);
}
