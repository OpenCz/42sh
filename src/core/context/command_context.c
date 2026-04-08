/*
** EPITECH PROJECT, 2026
** execute
** File description:
** context
*/

#include "minishell.h"

static void init_command_ctx(command_ctx_t *ctx)
{
    ctx->command = NULL;
    ctx->argv = NULL;
    ctx->arg_command = NULL;
    ctx->redirection = NULL;
}

static void set_redirection(command_ctx_t *ctx, char *command)
{
    char *redirection = get_redirection(command);

    if (redirection)
        ctx->redirection = my_strdup(redirection);
}

void clear_command_ctx(command_ctx_t *ctx)
{
    if (!ctx)
        return;
    free_array(ctx->argv);
    ctx->argv = NULL;
    if (ctx->redirection)
        free(ctx->redirection);
    ctx->redirection = NULL;
    ctx->command = NULL;
    ctx->arg_command = NULL;
}

int parse_command_context(char *command, command_ctx_t *ctx)
{
    char **command_with_arg = my_str_to_word_array(command, " \t");

    if (!ctx)
        return 1;
    init_command_ctx(ctx);
    if (!command_with_arg)
        return 1;
    if (!command_with_arg[0]) {
        free_array(command_with_arg);
        return 2;
    }
    ctx->command = command_with_arg[0];
    ctx->argv = command_with_arg;
    ctx->arg_command = &command_with_arg[1];
    set_redirection(ctx, command);
    return SUCCESS;
}

int bind_command_context(main_t *stock_main, command_ctx_t *ctx)
{
    if (!stock_main || !ctx)
        return 1;
    free_array(stock_main->argv);
    stock_main->argv = NULL;
    if (stock_main->redirection)
        free(stock_main->redirection);
    stock_main->redirection = NULL;
    stock_main->command = ctx->command;
    stock_main->argv = ctx->argv;
    stock_main->arg_command = ctx->arg_command;
    stock_main->redirection = ctx->redirection;
    ctx->command = NULL;
    ctx->argv = NULL;
    ctx->arg_command = NULL;
    ctx->redirection = NULL;
    return SUCCESS;
}

int set_command_context(main_t *stock_main, char *command)
{
    command_ctx_t ctx;
    int status = parse_command_context(command, &ctx);

    if (status != 0)
        return status;
    return bind_command_context(stock_main, &ctx);
}
