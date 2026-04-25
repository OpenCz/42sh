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
    char **arg_alias = NULL;

    if (!new_alias || !ctx->arg_command[0])
        return 1;
    arg_alias = my_str_to_word_array(ctx->arg_command[0], "=");
    if (!arg_alias || !arg_alias[0] || !arg_alias[1])
        return 1;
    new_alias->new_name = my_strdup(arg_alias[0]);
    new_alias->command = my_strdup(arg_alias[1]);
    new_alias->is_fixed = false;
    new_alias->next = main_stock->alias_stock;
    main_stock->alias_stock = new_alias;
    return 0;
}
