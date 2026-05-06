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
    char c;

    for (int i = 0; str[i] != '\0'; i++) {
        c = str[i];
        if (c == '(' || c == ')' || c == '+' || c == '=' ||
            c == '-' ||
            (c == '/' && str[i - 1] != '.') || c == '!' ||
            c == '*' || c == '|' || c == '>' || c == '<')
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

    if (!cmd || (strlen(condition) + strlen("echo \"")
            + strlen("\" | bc -l") > BUFFER_SIZE))
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

static int wait_pipe(pid_t pid, FILE **fd, int *status, int pipefd[2])
{
    close(pipefd[1]);
    waitpid(pid, status, 0);
    *fd = fdopen(pipefd[0], "r");
    if (!(*fd)) {
        close(pipefd[0]);
        return 0;
    }
    return 1;
}

int redirect_command(main_t *main, char *str)
{
    int status = 0;
    int pipefd[2] = {0, 0};
    pid_t pid = 0;
    char *buffer = NULL;
    size_t size = 0;
    FILE *fd = NULL;
    int result = 0;

    if (pipe(pipefd) == -1)
        return 0;
    pid = fork();
    handle_child(pid, main, pipefd, str);
    if (!wait_pipe(pid, &fd, &status, pipefd))
        return 0;
    getline(&buffer, &size, fd);
    fclose(fd);
    result = atoi(buffer);
    free_alloc(buffer);
    return result;
}

static int check_keywords(char **argv)
{
    int has_then = 0;
    int has_endif = 0;

    for (int i = 1; argv[i]; i++) {
        if (strcmp(argv[i], "then") == 0)
            has_then = 1;
        if (strcmp(argv[i], "endif") == 0)
            has_endif = 1;
    }
    if (!has_then) {
        printf("if: Missing 'then'.\n");
        return -1;
    }
    if (!has_endif) {
        printf("if: Missing 'endif'.\n");
        return -1;
    }
    return 0;
}

static int check_if_format(command_ctx_t *ctx)
{
    if (my_wordarray_len(ctx->argv) == 1) {
        printf("if: Too few arguments.\n");
        return -1;
    }
    if (check_keywords(ctx->argv) == -1)
        return -1;
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
    }
    free_alloc(to_exec);
    free_alloc(else_cmd);
    free_alloc(cmd);
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
    free_alloc(condition);
    exec_if_command(main_stock, cmd, to_exec, else_cmd);
    return 0;
}
