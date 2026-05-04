/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** if
*/

#include "../../../include/c_zsh.h"
#include <fcntl.h>

static char *is_operator(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(' || str[i] == ')' || str[i] == '+' || str[i] == '=' ||
            (str[i] == '-' && str[i + 1] >= '0' && str[i + 1] <= '9') ||
            (str[i] == '/' && str[i - 1] != '.') ||
            str[i] == '!' || str[i] == '*' || str[i] == '|')
            return str;
    }
    return NULL;
}

char *is_command(char *str)
{
    if (is_operator(str))
        return str;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[0] == '-' && str[i + 1] >= '0' && str[i + 1] <= '9')
            continue;
        if (str[i] < '0' || str[i] > '9')
            return NULL;
    }
    return str;
}

static char *create_cmd(char *condition)
{
    char *cmd = calloc(1, BUFFER_SIZE);

    if (!cmd)
        return NULL;
    cmd = strcpy(cmd, "echo \"");
    cmd = strcat(cmd, condition);
    cmd = strcat(cmd, "\" | bc -l");
    return cmd;
}

static void handle_child(pid_t pid, main_t *main, int pipefd[2], char *str)
{
    if (pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        exit(execute_command(main, str));
    }
}

int redirect_command(main_t *main, char *str)
{
    int status = 0;
    int pipefd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE + 1];
    int size = 0;

    if (pipe(pipefd) == -1)
        return 0;
    pid = fork();
    handle_child(pid, main, pipefd, str);
    close(pipefd[1]);
    waitpid(pid, &status, 0);
    size = read(pipefd[0], buffer, BUFFER_SIZE);
    close(pipefd[0]);
    if (size <= 0)
        return -1;
    buffer[size] = '\0';
    return atoi(buffer);
}

static int check_if_format(command_ctx_t *ctx)
{
    int len = my_wordarray_len(ctx->argv);

    if (len == 1) {
        printf("if: Too few arguments.\n");
        return -1;
    }
    if (len == 2 || strcmp(ctx->argv[1], "else") == 0) {
        if (!is_command(ctx->argv[1]) || is_operator(ctx->argv[1]))
            printf("if: Expression Syntax.\n");
        else
            printf("Empty if.\n");
        return -1;
    }
    if (is_valid_formating(ctx->argv) == -1)
        return -1;
    return 0;
}

static void exec_if_command(main_t *main_stock, char *cmd,
    char *to_exec, char *else_cmd)
{
    if (redirect_command(main_stock, cmd) != 0)
        execute_command(main_stock, to_exec);
    else if (else_cmd) {
        execute_command(main_stock, else_cmd);
        free(else_cmd);
    }
    free(to_exec);
    free(cmd);
}

int builtin_if(main_t *main_stock, command_ctx_t *ctx)
{
    char *cmd = NULL;
    char *to_exec = NULL;
    char *else_cmd = NULL;
    char *condition = NULL;

    if (check_if_format(ctx) == -1)
        return 1;
    condition = create_condition(main_stock, ctx, &else_cmd, &to_exec);
    if (!condition || strlen(condition) < 1)
        return 1;
    cmd = create_cmd(condition);
    free(condition);
    exec_if_command(main_stock, cmd, to_exec, else_cmd);
    return 0;
}
