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

static char *build_command_with_equal(char **arg_command)
{
    char *command_part = concat_command(&arg_command[2]);
    char *result = NULL;
    int len = 0;

    if (!command_part)
        return NULL;
    len = strlen(command_part) + 3;
    result = malloc(sizeof(char) * len);
    if (result)
        snprintf(result, len, "= %s", command_part);
    free_alloc(command_part);
    return result;
}

static char *build_command_string(command_ctx_t *ctx)
{
    if (ctx->arg_command[1] && strcmp(ctx->arg_command[1], "=") == 0)
        return build_command_with_equal(ctx->arg_command);
    return concat_command(&ctx->arg_command[1]);
}

static int display_alias(alias_stock_t *alias)
{
    alias_stock_t *tmp = alias;

    for (; tmp; tmp = tmp->next) {
        if (tmp->command && tmp->command[0] == '=')
            printf("%s\t(%s)\n", tmp->new_name, tmp->command);
        else
            printf("%s\t%s\n", tmp->new_name, tmp->command);
    }
    return 0;
}

void split_arg(command_ctx_t *ctx, char separator)
{
    int len = 0;
    char **new_argv = NULL;
    char *ptr = strchr(ctx->arg_command[0], separator);

    if (!ptr)
        ptr = strchr(ctx->arg_command[1], separator);
    for (; ctx->argv[len]; len++);
    new_argv = malloc(sizeof(char *) * (len + 2));
    if (!new_argv)
        return;
    new_argv[0] = strdup(ctx->argv[0]);
    *ptr = '\0';
    new_argv[1] = strdup(ctx->arg_command[0]);
    new_argv[2] = strdup(ptr + 1);
    new_argv[len + 1] = NULL;
    free_array(ctx->argv);
    ctx->argv = new_argv;
    ctx->command = new_argv[0];
    ctx->arg_command = &new_argv[1];
}

static int check_and_split(command_ctx_t *ctx)
{
    int has_equal = strchr(ctx->arg_command[0], '=') != NULL;
    int second_has_equal = 0;

    if (!has_equal && ctx->arg_command[1])
        second_has_equal = strchr(ctx->arg_command[1], '=') != NULL;
    if (has_equal && !ctx->arg_command[1])
        split_arg(ctx, '=');
    else if (second_has_equal && !ctx->arg_command[2])
        split_arg(ctx, '=');
    return 0;
}

static int add_alias(main_t *main_stock, command_ctx_t *ctx)
{
    alias_stock_t *current = main_stock->alias_stock;
    char *new_cmd = build_command_string(ctx);

    while (current && strcmp(current->new_name, ctx->arg_command[0]) != 0)
        current = current->next;
    if (current) {
        free_alloc(current->command);
        current->command = new_cmd;
        return 0;
    }
    current = malloc(sizeof(alias_stock_t));
    if (!current)
        return 1;
    current->new_name = strdup(ctx->arg_command[0]);
    current->command = new_cmd;
    current->is_fixed = false;
    current->next = main_stock->alias_stock;
    main_stock->alias_stock = current;
    return 0;
}

int builtin_alias(main_t *main_stock, command_ctx_t *ctx)
{
    if (!ctx->arg_command[0])
        return display_alias(main_stock->alias_stock);
    check_and_split(ctx);
    if (!ctx->arg_command[1])
        return 1;
    return add_alias(main_stock, ctx);
}
