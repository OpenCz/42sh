/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** command_substitution
*/

#include "../../../include/c_zsh.h"

static void child_process(main_t *stock_main, char *command, int *fd)
{
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    execute_command(stock_main, command);
    exit(0);
}

static char *read_pipe(int fd)
{
    char *result = NULL;
    char c;
    int total = 0;

    while (read(fd, &c, 1) > 0) {
        result = realloc(result, total + 2);
        result[total] = c;
        total++;
        result[total] = '\0';
    }
    for (; total > 0 && result[total - 1] == '\n'; total--)
        result[total] = '\0';
    return result;
}

char *command_substitution(main_t *stock_main, char *command)
{
    int fd[2];
    pid_t pid;
    char *result = NULL;

    if (pipe(fd) == -1)
        return NULL;
    pid = fork();
    if (pid == -1)
        return NULL;
    if (pid == 0)
        child_process(stock_main, command, fd);
    close(fd[1]);
    result = read_pipe(fd[0]);
    close(fd[0]);
    waitpid(pid, NULL, 0);
    return result;
}
