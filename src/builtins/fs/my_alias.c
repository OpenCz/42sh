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
    result = malloc(sizeof(char) * (total_length + 1));
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

static int display_alias(alias_stock_t *alias)
{
    alias_stock_t *tmp = alias;

    for (; tmp; tmp = tmp->next)
        printf("%s\t%s\n", tmp->new_name, tmp->command);
    return 0;
}

void split_arg(command_ctx_t *ctx, char separator)
{
    int len = 0;
    char **new_argv = NULL;
    char *ptr = strchr(ctx->arg_command[0], separator);

    for (; ctx->argv[len]; len++);
    new_argv = malloc(sizeof(char *) * (len + 2));
    if (!new_argv)
        return;
    new_argv[0] = strdup(ctx->argv[0]);
    *ptr = '\0';
    new_argv[1] = strdup(ctx->arg_command[0]);
    new_argv[2] = strdup(ptr + 1);
    for (int i = 2; ctx->arg_command[i - 1] != NULL; i++)
        new_argv[i + 1] = strdup(ctx->arg_command[i - 1]);
    new_argv[len + 1] = NULL;
    free_array(ctx->argv);
    ctx->argv = new_argv;
    ctx->command = new_argv[0];
    ctx->arg_command = &new_argv[1];
}

int builtin_alias(main_t *main_stock, command_ctx_t *ctx)
{
    alias_stock_t *new_alias = NULL;

    if (!ctx->arg_command[0])
        return display_alias(main_stock->alias_stock);
    if (strchr(ctx->arg_command[0], '=') && !ctx->arg_command[1])
        split_arg(ctx, '=');
    if (!ctx->arg_command[1])
        return 1;
    new_alias = malloc(sizeof(alias_stock_t));
    if (!new_alias)
        return 1;
    if (init_alias(main_stock, ctx, new_alias) != 0) {
        free_alloc(new_alias);
        return 1;
    }
    new_alias->next = main_stock->alias_stock;
    main_stock->alias_stock = new_alias;
    return 0;
}
