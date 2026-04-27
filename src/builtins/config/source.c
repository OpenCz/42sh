/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** source
*/

#include "../../../include/c_zsh.h"

int source(main_t *stock_main, command_ctx_t *ctx)
{
    stock_main->czshrc = update_rc(ctx->argv[1]);
    return 0;
}
