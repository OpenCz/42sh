/*
** EPITECH PROJECT, 2026
** error
** File description:
** error
*/

#include "minishell.h"

int child_exec(command_ctx_t *ctx, char *path, char **env)
{
    if (execve(path, ctx->argv, env) == -1) {
        my_putstrerror(ctx->command);
        if (errno == ENOEXEC) {
            my_putstr(": Exec format error. ");
            my_putstr("Binary file not executable.\n");
            return 126;
        }
        if (errno == EACCES) {
            my_putstr(": Permission denied.\n");
            return 126;
        }
    }
    return 0;
}

int get_seg(int status)
{
    int sig = WTERMSIG(status);
    int exit_value = 0;

    if (sig == SIGFPE) {
        write(1, "Floating exception", 18);
        exit_value = 136;
    }
    if (sig == SIGSEGV) {
        write(1, "Segmentation fault", 18);
        exit_value = 139;
    }
    if (WCOREDUMP(status))
        write(1, " (core dumped)", 14);
    write(1, "\n", 1);
    return exit_value;
}
