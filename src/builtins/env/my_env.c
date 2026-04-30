/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** env builtin (my_env + builtin_env wrapper).
** Iterates the stock_env linked list and prints each node
** as KEY=VALUE (or KEY= when value is NULL) to stdout.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

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
