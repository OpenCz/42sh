/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/builtins/signal
** File description:
** my_foreground
*/

#include "c_zsh.h"

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
    kill(tmp->job->pid, SIGCONT);
    prev->next = tmp->next;
    free_array(tmp->job->command);
    free_alloc(tmp->job);
    free_alloc(tmp);
    tmp = NULL;
    return 0;
}
