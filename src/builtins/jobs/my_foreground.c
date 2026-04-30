/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/builtins/signal
** File description:
** my_foreground
*/

#include "c_zsh.h"

void set_foreground(job_controler_t *tmp, job_controler_t *prev)
{
    pid_t pgid = tmp->job->pgid;
    int status = 0;
    pid_t shell_pgid = getpgrp();
    struct termios shell_tmodes;

    tcgetattr(STDIN_FILENO, &shell_tmodes);
    tcsetpgrp(STDIN_FILENO, pgid);
    kill(-pgid, SIGCONT);
    waitpid(pgid, &status, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, shell_pgid);
    tcsetattr(STDIN_FILENO, TCSADRAIN, &shell_tmodes);
    if (!WIFSTOPPED(status)) {
        prev->next = tmp->next;
        free_array(tmp->job->command);
        free_alloc(tmp->job);
        free_alloc(tmp);
        tmp = NULL;
    }
}

int builtin_foreground(main_t *main_stock, command_ctx_t *ctx)
{
    job_controler_t *curr = main_stock->controler;
    job_controler_t *prev = curr;
    job_controler_t *tmp = curr ? curr->next : NULL;

    if (tmp == NULL) {
        printf("fg: No current job.\n");
        return 0;
    }
    while (tmp->next != NULL) {
        prev = tmp;
        tmp = tmp->next;
    }
    set_foreground(tmp, prev);
    return 0;
}
