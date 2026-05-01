/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/42sh/src/builtins/limit
** File description:
** get_good_limit
*/

#include "c_zsh.h"

static int verif_name(char *name, char *lim_name, int lim, limit_t *limit)
{
    if (my_strncmp(name, lim_name, 1) == 0) {
        if (limit->good_name) {
            my_putstr("limit: Ambiguous.\n");
            return FAILURE;
        }
        limit->good_name = lim_name;
        limit->good_lim = lim;
    }
    return SUCCESS;
}

static int check_name(limit_t *limit, char *name, char *lim_name[], int lim[])
{
    limit->good_name = NULL;
    for (int i = 0; lim_name[i] != NULL; i++) {
        if (verif_name(name, lim_name[i], lim[i], limit) == FAILURE) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

static limit_t *return_value(limit_t *limit)
{
    free(limit);
    return NULL;
}

limit_t *get_good_limit(char *name)
{
    int lim[16] = {RLIMIT_CPU, RLIMIT_FSIZE, RLIMIT_DATA, RLIMIT_STACK,
        RLIMIT_CORE, RLIMIT_RSS, RLIMIT_AS, RLIMIT_NOFILE, RLIMIT_MEMLOCK,
        RLIMIT_NPROC, RLIMIT_LOCKS, RLIMIT_SIGPENDING, RLIMIT_MSGQUEUE,
        RLIMIT_NICE, RLIMIT_RTPRIO, RLIMIT_RTTIME};
    char *lim_name[17] = {"cputime", "filesize", "datasize", "stacksize",
        "coredumpsize", "memoryuse", "vmemoryuse", "descriptors",
        "memorylocked", "maxproc", "maxlocks", "maxsignal",
        "maxmessage", "maxnice", "maxrtprio", "maxrttime", NULL};
    limit_t *limit = malloc(sizeof(limit_t));

    if (!limit)
        return NULL;
    if (check_name(limit, name, lim_name, lim) == FAILURE) {
        return return_value(limit);
    }
    if (!limit->good_name) {
        my_putstr("limit: No such limit.\n");
        return return_value(limit);
    }
    return limit;
}
