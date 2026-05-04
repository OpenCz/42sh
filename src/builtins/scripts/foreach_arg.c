/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/builtins/scripts
** File description:
** foreach_arg.c
*/

#include "c_zsh.h"

int get_len_arg(command_ctx_t *ctx)
{
    int len = my_wordarray_len(ctx->arg_command);

    if (ctx->arg_command[len - 1]
        && strcmp(ctx->arg_command[len - 1], ")") == 0)
        len--;
    if (ctx->arg_command[1] && strcmp(ctx->arg_command[1], "(") == 0)
        len--;
    return len;
}

void fill_arg(char **arg, command_ctx_t *ctx, int i, int j)
{
    int start = strcmp(ctx->arg_command[1], "(") == 0;
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

char **get_array_arg(command_ctx_t *ctx)
{
    int len = get_len_arg(ctx);
    int start = strcmp(ctx->arg_command[1], "(") == 0;
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
