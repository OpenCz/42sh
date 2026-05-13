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

static alias_stock_t *find_alias_by_name(alias_stock_t *stock, char *name)
{
    for (; stock; stock = stock->next)
        if (strcmp(stock->new_name, name) == 0)
            return stock;
    return NULL;
}

static void merge_loaded_aliases(main_t *stock_main, alias_stock_t *aliases)
{
    alias_stock_t *current = aliases;
    alias_stock_t *next = NULL;
    alias_stock_t *existing = NULL;

    while (current) {
        next = current->next;
        existing = find_alias_by_name(stock_main->alias_stock,
            current->new_name);
        current->next = NULL;
        if (existing) {
            free_alloc(existing->command);
            existing->command = current->command;
            free_alloc(current->new_name);
            free_alloc(current);
        } else {
            current->next = stock_main->alias_stock;
            stock_main->alias_stock = current;
        }
        current = next;
    }
}

int source(main_t *stock_main, command_ctx_t *ctx)
{
    czshrc_t *previous_rc = stock_main->czshrc;

    stock_main->czshrc = update_rc(ctx->argv[1]);
    if (!stock_main->czshrc)
        return 1;
    if (stock_main->czshrc->aliases) {
        merge_loaded_aliases(stock_main, stock_main->czshrc->aliases);
        stock_main->czshrc->aliases = NULL;
    }
    if (previous_rc) {
        free_alloc(previous_rc->prompt);
        free_alloc(previous_rc);
    }
    return 0;
}
