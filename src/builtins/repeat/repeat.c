/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** repeat builtin: parses the count with atoi(), sets up a shifted
** command_ctx_t pointing to the command after N, then runs exec_any()
** in a loop 0..N-1 and returns the exit code of the last iteration.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../../include/c_zsh.h"

int builtin_repeat(main_t *main_stock, command_ctx_t *ctx)
{
    int nbr = 0;
    int value = 0;
    command_ctx_t repeated_ctx = *ctx;

    if (ctx->arg_command != NULL && ctx->arg_command[0] != NULL)
        nbr = atoi(ctx->arg_command[0]);
    if (nbr == 0)
        return SUCCESS;
    repeated_ctx.command = ctx->arg_command[1];
    repeated_ctx.argv = &ctx->arg_command[1];
    repeated_ctx.arg_command = ctx->arg_command + 2;
    for (int i = 0; i < nbr; i++)
        value = exec_any(main_stock, &repeated_ctx, false);
    return value;
}
