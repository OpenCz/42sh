/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** source / . builtin: opens the file with openator(), splits it
** into lines with str_to_array_of_word_array(), then executes
** each line via exec_any() in the current shell context.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../../include/c_zsh.h"

int source(main_t *stock_main, command_ctx_t *ctx)
{
    czshrc_t *previous_rc = stock_main->czshrc;

    stock_main->czshrc = update_rc(ctx->argv[1]);
    if (!stock_main->czshrc)
        return 1;
    if (stock_main->czshrc->aliases) {
        alias_stock_t *aliases = stock_main->czshrc->aliases;

        stock_main->czshrc->aliases = NULL;
        aliases->next = stock_main->alias_stock;
        stock_main->alias_stock = aliases;
    }
    if (previous_rc) {
        free_alloc(previous_rc->prompt);
        free_alloc(previous_rc);
    }
    return 0;
}
