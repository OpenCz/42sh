/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/builtins/signal
** File description:
** my_jobs
*/

#include "c_zsh.h"

void assign_job(job_t *job, char **command, int pid)
{
    job->command = command;
    job->pid = pid;
    job->pgid = getpgid(pid);
    job->sign = '+';
}

int append_jobs(char **command, int pid, main_t *main_stock)
{
    job_controler_t *new_controler = malloc(sizeof(job_controler_t));
    job_t *job = malloc(sizeof(job_t));
    job_controler_t *tmp = NULL;

    if (!job || !new_controler || !command)
        return 1;
    assign_job(job, command, pid);
    new_controler->job = job;
    new_controler->next = NULL;
    if (!main_stock->controler) {
        main_stock->controler = new_controler;
        return 0;
    }
    tmp = main_stock->controler;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_controler;
    return 0;
}

int builtin_jobs(main_t *main_stock, command_ctx_t *ctx)
{
    job_controler_t *controler = main_stock->controler;
    job_controler_t *tmp = controler->next;

    for (int i = 1; tmp && tmp->job != NULL; i++) {
        printf("[%i]  %c Suspended\t\t\t", i, tmp->job->sign);
        for (int j = 0; tmp->job->command[j] != NULL; j++)
            printf(" %s", tmp->job->command[j]);
        printf("\n");
        tmp = tmp->next;
    }
    return 0;
}
