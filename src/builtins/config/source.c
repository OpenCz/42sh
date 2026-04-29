/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** source / . builtin: opens the file with openator(), splits it
** into lines with str_to_array_of_word_array(), then executes
** each line via exec_any() in the current shell context.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../../include/c_zsh.h"

int source(main_t *stock_main, command_ctx_t *ctx)
{
    stock_main->czshrc = update_rc(ctx->argv[1]);
    return 0;
}
