/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** The foreach.c
*/
/**
 * @file foreach.c
 * @brief The foreach.c
 * @author Erwan Lo Presti
 */

#include "../../../include/c_zsh.h"


static int get_len_arg(command_ctx_t *ctx)
{
    int len = my_wordarray_len(ctx->arg_command);

    if (ctx->arg_command[len - 1]
        && strcmp(ctx->arg_command[len - 1], ")") == 0)
        len--;
    if (ctx->arg_command[1] && strcmp(ctx->arg_command[1], "(") == 0)
        len--;
    return len;
}

static int start_arg(command_ctx_t *ctx)
{
    int start = 0;

    if (strcmp(ctx->arg_command[1], "(") == 0)
        start++;
    return start;
}

static void fill_arg(char **arg, command_ctx_t *ctx, int i, int j)
{
    int start = start_arg(ctx);
    int len_array = my_wordarray_len(ctx->arg_command) - 1;
    int last = 0;

    if (i == start + 1 && ctx->arg_command[i][0] == '(') {
        arg[j] = ctx->arg_command[i] + 1;
        last = strlen(arg[j]) - 1;
        arg[j][last] *= (arg[j][last] != ')');
        return;
    }
    if (i == len_array
        && ctx->arg_command[len_array]
        [strlen(ctx->arg_command[len_array]) - 1] == ')') {
        arg[j] = ctx->arg_command[i];
        arg[j][strlen(arg[j]) - 1] = '\0';
        return;
    }
    arg[j] = ctx->arg_command[i];
}

static char **get_array_arg(command_ctx_t *ctx)
{
    int len = get_len_arg(ctx);
    int start = start_arg(ctx);
    int j = 0;
    char **arg = malloc(sizeof(char *) * (len + 1));

    if (arg == NULL)
        return NULL;
    arg[len] = NULL;
    arg[0] = ctx->arg_command[0];
    for (int i = start + 1; i < len + start + 1; i++) {
        j = i - start;
        fill_arg(arg, ctx, i, j);
    }
    return arg;
}

static void handle_var(command_ctx_t *new_ctx, char *var, char **arg, int i)
{
    for (int k = 0; new_ctx->argv[k] != NULL; k++) {
        if (strncmp(new_ctx->argv[k], "$", 1) == 0 && strcmp(new_ctx->argv[k] + 1, var) == 0)
            new_ctx->argv[k] = arg[i];
    }
}

static int foreach(command_ctx_t *ctx, char **cmd, main_t *main_stock)
{
    command_ctx_t new_ctx = *ctx;
    char **arg = get_array_arg(ctx);

    if (!arg)
        return FAILURE;
    for (int i = 1; arg[i] != NULL; i++) {
        for (int j = 0; cmd[j] != NULL; j++) {
            parse_command_context(cmd[j], &new_ctx);
            handle_var(&new_ctx, arg[0], arg, i);
            exec_any(main_stock, &new_ctx);
        }
    }
    free(arg);
    free_array(cmd);
    return SUCCESS;
}

int builtin_foreach(main_t *main_stock, command_ctx_t *ctx)
{
    char **cmd = NULL;

    if (handle_error(ctx) == FAILURE)
        return 1;
    cmd = foreach_read_commands();
    if (cmd == NULL)
        return FAILURE;
    return foreach(ctx, cmd, main_stock);
}
