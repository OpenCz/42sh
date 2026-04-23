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
            str[i] == '!')
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
    cmd = strcpy(cmd, "calc ");
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

static char *create_condition(main_t *main, command_ctx_t *ctx, char *cmd)
{
    char *buffer = calloc(1, BUFFER_SIZE);

    if (!buffer) {
        free_alloc(cmd);
        return NULL;
    }
    for (int i = 1; ctx->argv[i] && strcmp(ctx->argv[i], "endif") != 0; i++)
        buffer = strcat(buffer, verif_value(main, &ctx->argv[i]));
    return buffer;
}

int builtin_if(main_t *main_stock, command_ctx_t *ctx)
{
    char *cmd = init_cmd();
    char *condition = create_condition(main_stock, ctx, cmd);

    if (!cmd || !condition)
        return 1;
    cmd = strcat(cmd, condition);
    printf("%d\n", redirect_command(main_stock, cmd));
    free(cmd);
    free(condition);
    return 0;
}
