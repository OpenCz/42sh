/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** if
*/

#include "../../../include/c_zsh.h"
#include <fcntl.h>

static char *is_command(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(' || str[i] == ')' || str[i] == '+' || str[i] == '=' ||
            str[i] == '-' || (str[i] == '/' && str[i - 1] != '.') ||
            str[i] == '!' || str[i] == '*' || str[i] == '|')
            return str;
        if (str[0] == '-')
            continue;
        if (str[i] < '0' || str[i] > '9')
            return NULL;
    }
    return str;
}

static char *init_cmd(void)
{
    char *cmd = calloc(1, BUFFER_SIZE);

    if (!cmd)
        return NULL;
    cmd = strcpy(cmd, "/bin/calc ");
    return cmd;
}

static int redirect_command(main_t *main, char *str)
{
    int status = 0;
    int pipefd[2];
    pid_t pid;
    char buffer[2];

    if (pipe(pipefd) == -1)
        return 0;
    pid = fork();
    if (pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        exit(execute_command(main, str));
    }
    if (read(pipefd[0], buffer, 2) == -1)
        return -1;
    close(pipefd[1]);
    close(pipefd[0]);
    waitpid(pid, &status, 0);
    return atoi(buffer);
}

static char *verif_value(main_t *main, char **str)
{
    if (!is_command(*str))
        sprintf(*str, "%d", redirect_command(main, *str));
    return *str;
}

static char *create_condition(main_t *main, command_ctx_t *ctx,
    char **else_cmd, char **to_exec)
{
    char *buffer = calloc(1, BUFFER_SIZE);
    int i = 1;

    if (!buffer)
        return NULL;
    for (; ctx->argv[i + 1] && strcmp(ctx->argv[i + 1], "endif") != 0; i++) {
        if (strcmp(ctx->argv[i + 1], "else") == 0) {
            *to_exec = strdup(ctx->argv[i]);
            *else_cmd = strdup(ctx->argv[i + 2]);
            return buffer;
        }
        buffer = strcat(buffer, verif_value(main, &ctx->argv[i]));
    }
    *to_exec = strdup(ctx->argv[i]);
    return buffer;
}

int builtin_if(main_t *main_stock, command_ctx_t *ctx)
{
    char *cmd = init_cmd();
    char *to_exec = NULL;
    char *else_cmd;
    char *condition = create_condition(main_stock, ctx, &else_cmd, &to_exec);

    if (!cmd || !condition) {
        if (cmd)
            free(cmd);
        return 1;
    }
    cmd = strcat(cmd, condition);
    if (redirect_command(main_stock, cmd) != 0)
        execute_command(main_stock, to_exec);
    else if (else_cmd)
        execute_command(main_stock, else_cmd);
    free(to_exec);
    free(cmd);
    free(condition);
    return 0;
}
