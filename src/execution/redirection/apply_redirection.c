/*
** EPITECH PROJECT, 2026
** redirection
** File description:
** apply redirection
*/

#include "minishell.h"
#include <fcntl.h>

static int find_redirection_index(command_ctx_t *ctx)
{
    for (int i = 0; ctx->argv && ctx->argv[i]; i++) {
        if (my_strcmp(ctx->argv[i], ctx->redirection) == 0)
            return i;
    }
    return -1;
}

static int open_redirection_fd(command_ctx_t *ctx, int index)
{
    if (my_strcmp(ctx->redirection, ">") == 0)
        return open(ctx->argv[index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (my_strcmp(ctx->redirection, ">>") == 0)
        return open(ctx->argv[index + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (my_strcmp(ctx->redirection, "<") == 0)
        return open(ctx->argv[index + 1], O_RDONLY);
    return -1;
}

static int bind_redirection_fd(command_ctx_t *ctx, int fd)
{
    if (my_strcmp(ctx->redirection, "<") == 0)
        return dup2(fd, STDIN_FILENO);
    return dup2(fd, STDOUT_FILENO);
}

int apply_redirection(command_ctx_t *ctx)
{
    int index = 0;
    int fd = -1;

    if (!ctx->redirection)
        return 0;
    index = find_redirection_index(ctx);
    if (index < 0 || !ctx->argv[index + 1]) {
        my_putstrerror("Invalid null command.\n");
        return 1;
    }
    fd = open_redirection_fd(ctx, index);
    if (fd == -1)
        return 1;
    if (bind_redirection_fd(ctx, fd) == -1) {
        close(fd);
        return 1;
    }
    close(fd);
    ctx->argv[index] = NULL;
    return 0;
}
