/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** source / . builtin: reloads the shell config by calling update_rc()
** with ctx->argv[1] as the target file path, immediately applying
** RC settings to the running shell; command execution from file pending.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../../include/c_zsh.h"

int source(main_t *stock_main, command_ctx_t *ctx)
{
    stock_main->czshrc = update_rc(ctx->argv[1]);
    return 0;
}
