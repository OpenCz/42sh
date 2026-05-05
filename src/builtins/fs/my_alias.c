/*
** EPITECH PROJECT, 2026
** alias
** File description:
** alias
*/

#include "c_zsh.h"

int init_alias(main_t *main_stock, command_ctx_t *ctx, alias_stock_t *new_alias)
{
    int i = 2;
    int arg_len = my_wordarray_len(&ctx->arg_command[2]);

    new_alias->command = strdup(ctx->arg_command[0]);
    new_alias->new_name = strdup(ctx->arg_command[1]);
    new_alias->new_arg_command = malloc(sizeof(char *) * (arg_len + 1));
    if (!new_alias->new_arg_command)
        return 1;
    for (int k = 0; k < arg_len; k++) {
        new_alias->new_arg_command[k] = strdup(ctx->arg_command[i]);
        i++;
    }
    new_alias->new_arg_command[arg_len] = NULL;
    new_alias->is_fixed = false;
    new_alias->next = new_alias;
    return 0;
}

int builtin_alias(main_t *main_stock, command_ctx_t *ctx)
{
    alias_stock_t *new_alias = malloc(sizeof(alias_stock_t));

    if (!new_alias)
        return 1;
    if (!ctx->arg_command[0] || !ctx->arg_command[1])
        return 1;
    init_alias(main_stock, ctx, new_alias);
    return 0;
}
