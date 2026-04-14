/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** The repeat.c
*/
/**
 * @file repeat.c
 * @brief The repeat.c
 * @author Erwan Lo Presti
 */

#include "../../../include/c_zsh.h"

int repeat(main_t *main_stock, command_ctx_t *ctx)
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
        value = exec_any(main_stock, &repeated_ctx);
    return value;
}

int builtin_repeat(main_t *main_stock, command_ctx_t *ctx)
{
    return repeat(main_stock, ctx);
}
