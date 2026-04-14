/*
** EPITECH PROJECT, 2026
** redirection
** File description:
** apply redirection
*/

#include "c_zsh.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static int read_heredoc_line(char **line, size_t *size, ssize_t *read_len)
{
    if (isatty(STDIN_FILENO))
        my_putstr("> ");
    *read_len = getline(line, size, stdin);
    return *read_len != -1;
}

static int write_heredoc_line(int fd, char *line)
{
    if (write(fd, line, my_strlen(line)) == -1)
        return 1;
    if (write(fd, "\n", 1) == -1)
        return 1;
    return SUCCESS;
}

static int write_heredoc_content(int fd, const char *delimiter)
{
    char *line = NULL;
    size_t size = 0;
    ssize_t read_len = 0;

    while (1) {
        if (!read_heredoc_line(&line, &size, &read_len)) {
            free(line);
            return 1;
        }
        if (read_len > 0 && line[read_len - 1] == '\n')
            line[read_len - 1] = '\0';
        if (my_strcmp(line, (char *)delimiter) == 0)
            break;
        if (write_heredoc_line(fd, line)) {
            free(line);
            return 1;
        }
    }
    free(line);
    return SUCCESS;
}

static int open_heredoc_fd(command_ctx_t *ctx, int index)
{
    char template[] = "/tmp/42sh_heredoc_XXXXXX";
    int fd = mkstemp(template);

    if (fd == -1)
        return -1;
    unlink(template);
    if (write_heredoc_content(fd, ctx->argv[index + 1]) != 0) {
        close(fd);
        return -1;
    }
    if (lseek(fd, 0, SEEK_SET) == -1) {
        close(fd);
        return -1;
    }
    return fd;
}

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
    if (my_strcmp(ctx->redirection, "<<") == 0)
        return open_heredoc_fd(ctx, index);
    return -1;
}

static int bind_redirection_fd(command_ctx_t *ctx, int fd)
{
    if (my_strcmp(ctx->redirection, "<") == 0 ||
        my_strcmp(ctx->redirection, "<<") == 0)
        return dup2(fd, STDIN_FILENO);
    return dup2(fd, STDOUT_FILENO);
}

int apply_redirection(command_ctx_t *ctx)
{
    int index = 0;
    int fd = -1;

    if (!ctx->redirection)
        return SUCCESS;
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
    return SUCCESS;
}
