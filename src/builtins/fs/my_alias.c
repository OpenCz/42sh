/*
** EPITECH PROJECT, 2026
** alias
** File description:
** alias
*/

#include "c_zsh.h"

char *my_strdup_quote(char *str)
{
    char *dup = malloc(my_strlen(str) + 1);
    int j = 0;

    if (!dup)
        return NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[0] == '"' || str[my_strlen(str) - 1] == '"')
            continue;
        dup[j] = str[i];
        j++;
    }
    dup[j] = '\0';
    return dup;
}

int builtin_alias(main_t *main_stock, command_ctx_t *ctx)
{
    alias_stock_t *new_alias = malloc(sizeof(alias_stock_t));

    if (!new_alias)
        return 84;
    if (!ctx->arg_command[0] && !ctx->arg_command[1])
        return 84;
    new_alias->command = strdup(ctx->arg_command[0]);
    new_alias->new_name = strdup(ctx->arg_command[1]);
    return 0;
}
