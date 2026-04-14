/*
** EPITECH PROJECT, 2026
** run fork
** File description:
** run
*/

#include "42sh.h"

int run_fork(main_t *main_stock, command_ctx_t *ctx, char *path, char **env)
{
    pid_t pid = fork();
    int status = 0;

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        if (apply_redirection(ctx) != 0)
            exit(1);
        exit(child_exec(ctx, path, env));
    } else {
        waitpid(pid, &status, 0);
        status = get_seg(status);
    }
    return status;
}
