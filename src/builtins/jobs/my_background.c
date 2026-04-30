/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/builtins/signal
** File description:
** my_background
*/

#include "c_zsh.h"

void set_background(job_controler_t *tmp, job_controler_t *prev)
{
    pid_t pgid = tmp->job->pgid;
    int status = 0;

    kill(-pgid, SIGCONT);
    waitpid(pgid, &status, WUNTRACED);
    if (!WIFSTOPPED(status))
        tmp->job->status = 1;
}

int builtin_background(main_t *main_stock, command_ctx_t *ctx)
{
    job_controler_t *curr = main_stock->controler;
    job_controler_t *prev = curr;
    job_controler_t *tmp = curr ? curr->next : NULL;

    if (tmp == NULL) {
        printf("bg: No current job.\n");
        return 0;
    }
    while (tmp->next != NULL) {
        prev = tmp;
        tmp = tmp->next;
    }
    set_background(tmp, prev);
    return 0;
}
