/*
** EPITECH PROJECT, 2026
** alias
** File description:
** alias
*/

#include "c_zsh.h"

char *concat_command(char **arg_command)
{
    char *result = NULL;
    int total_length = 0;

    for (int i = 0; arg_command[i] != NULL; i++)
        total_length += strlen(arg_command[i]) + 1;
    result = malloc(sizeof(char *) * (total_length + 1));
    if (!result)
        return NULL;
    result[0] = '\0';
    for (int i = 0; arg_command[i] != NULL; i++) {
        strcat(result, arg_command[i]);
        if (arg_command[i + 1] != NULL)
            strcat(result, " ");
    }
    return result;
}

int init_alias(main_t *main_stock, command_ctx_t *ctx, alias_stock_t *new_alias)
{
    new_alias->command = concat_command(&ctx->arg_command[1]);
    new_alias->new_name = strdup(ctx->arg_command[0]);
    new_alias->is_fixed = false;
    new_alias->next = NULL;
    return 0;
}

int builtin_alias(main_t *main_stock, command_ctx_t *ctx)
{
    alias_stock_t *new_alias = malloc(sizeof(alias_stock_t));

    if (!new_alias)
        return 1;
    if (!ctx->arg_command[0] || !ctx->arg_command[1])
        return 1;
    if (init_alias(main_stock, ctx, new_alias) != 0)
        return 1;
    new_alias->next = main_stock->alias_stock;
    main_stock->alias_stock = new_alias;
    return 0;
}
