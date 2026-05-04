/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Builds command_ctx_t from a raw string: tokenizes input,
** calls convert_quotes and replace_env_vars on each token,
** detects redirection, fills command/argv/arg_command fields.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../../include/c_zsh.h"

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
        ctx->redirection = strdup(redirection);
}

static int convert_command_args(char **command_with_arg, main_t *stock_main)
{
    char *converted = NULL;

    for (int i = 0; command_with_arg[i]; i++) {
        converted = convert_quotes(command_with_arg[i]);
        if (!converted) {
            free_array(command_with_arg);
            return 1;
        }
        free(command_with_arg[i]);
        command_with_arg[i] = converted;
    }
    return 0;
}

static int set_command_fields(command_ctx_t *ctx,
    char **command_with_arg, char *command)
{
    ctx->command = command_with_arg[0];
    ctx->argv = command_with_arg;
    ctx->arg_command = &command_with_arg[1];
    set_redirection(ctx, command);
    return SUCCESS;
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

static int decode_command_args(char **args)
{
    char *decoded = NULL;

    for (int i = 0; args[i]; i++) {
        decoded = decode_literals(args[i]);
        if (!decoded) {
            free_array(args);
            return 1;
        }
        free(args[i]);
        args[i] = decoded;
    }
    return 0;
}

static char **process_expanded_command(char *expanded, main_t *stock_main)
{
    char **cmd_with_arg = my_str_to_word_array_quote(expanded, " \t");

    if (!cmd_with_arg || !cmd_with_arg[0]) {
        free_array(cmd_with_arg);
        return NULL;
    }
    if (convert_command_args(cmd_with_arg, stock_main) != 0)
        return NULL;
    replace_env_vars(cmd_with_arg, stock_main);
    if (decode_command_args(cmd_with_arg) != 0)
        return NULL;
    return cmd_with_arg;
}

int parse_command_context(char *command, command_ctx_t *ctx, main_t *stock_main)
{
    char *expanded_cmd = NULL;
    char **command_with_arg = NULL;

    if (!ctx)
        return 1;
    init_command_ctx(ctx);
    expanded_cmd = manage_backticks(command, stock_main);
    if (!expanded_cmd)
        return 1;
    command_with_arg = process_expanded_command(expanded_cmd, stock_main);
    if (expanded_cmd != command)
        free(expanded_cmd);
    if (!command_with_arg)
        return 2;
    return set_command_fields(ctx, command_with_arg, command);
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
    int status = parse_command_context(command, &ctx, stock_main);

    if (status != 0)
        return status;
    return bind_command_context(stock_main, &ctx);
}
