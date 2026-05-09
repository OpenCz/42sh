/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** source / . builtin: reloads the shell config by calling update_rc()
** with ctx->argv[1] as the target file path, immediately applying
** RC settings to the running shell; command execution from file pending.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../../include/c_zsh.h"

int source(main_t *stock_main, command_ctx_t *ctx)
{
    czshrc_t *previous_rc = stock_main->czshrc;
    alias_stock_t *aliases = NULL;
    alias_stock_t *tail = NULL;

    stock_main->czshrc = update_rc(ctx->argv[1]);
    if (!stock_main->czshrc)
        return 1;
    if (stock_main->czshrc->aliases) {
        aliases = stock_main->czshrc->aliases;
        for (tail = aliases; tail->next; tail = tail->next);
        stock_main->czshrc->aliases = NULL;
        tail->next = stock_main->alias_stock;
        stock_main->alias_stock = aliases;
    }
    if (previous_rc) {
        free_alloc(previous_rc->prompt);
        free_alloc(previous_rc);
    }
    return 0;
}
