/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** source / . builtin stub: currently only reloads the czshrc config
** via update_rc(); file execution (open, split lines, run each via
** exec_any) is not yet implemented — the builtin is registered but empty.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../../include/c_zsh.h"

int source(main_t *stock_main, command_ctx_t *ctx)
{
    stock_main->czshrc = update_rc();
    return 0;
}
