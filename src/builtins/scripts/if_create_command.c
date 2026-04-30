/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** if
*/

#include "../../../include/c_zsh.h"

char *append_buffer(command_ctx_t *ctx, int *i)
{
    char *buffer = calloc(1, BUFFER_SIZE);

    if (!buffer)
        return NULL;
    buffer = strcpy(buffer, ctx->argv[*i]);
    while (ctx->argv[*i + 1] && strcmp(ctx->argv[*i + 1], "else") &&
        (!is_command(ctx->argv[*i]) &&
            !is_command(ctx->argv[*i + 1]))) {
        buffer = strcat(buffer, " ");
        buffer = strcat(buffer, ctx->argv[*i + 1]);
        *i += 1;
    }
    *i += 2;
    return buffer;
}
