/*
** EPITECH PROJECT, 2026
** which
** File description:
** which
*/

#include "c_zsh.h"

int builtin_which(main_t *main_stock, command_ctx_t *ctx)
{
    int i = 0;
    char *bin_place = NULL;

    for (; main_stock->path[i] != NULL; i++) {
        bin_place = check_bin(ctx->arg_command[0], main_stock->path[i]);
        if (bin_place != NULL)
            printf("%s\n", bin_place);
    }
    return 0;
}
