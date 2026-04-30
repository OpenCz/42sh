/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/42sh/src/builtins/limit
** File description:
** limit
*/

#include "c_zsh.h"
#include <sys/time.h>
#include <sys/resource.h>

static int display_limit(struct rlimit *rl)
{
    int lim[17] = {RLIMIT_CPU, RLIMIT_FSIZE, RLIMIT_DATA, RLIMIT_STACK,
        RLIMIT_CORE, RLIMIT_RSS, RLIMIT_NPROC, RLIMIT_NOFILE, RLIMIT_MEMLOCK,
        RLIMIT_AS, RLIMIT_LOCKS, RLIMIT_SIGPENDING, RLIMIT_MSGQUEUE,
        RLIMIT_NICE, RLIMIT_RTPRIO, RLIMIT_RTTIME};
    char *lim_name[17] = {"cputime", "filesize", "datasize", "stacksize",
        "coredumpsize", "memoryuse", "vmemoryuse", "descriptors",
        "memorylocked", "maxproc", "maxlocks", "maxsignal",
        "maxmessage", "maxnice", "maxrtprio", "maxrttime", NULL};
    int size = 0;

    for (int i = 0; lim_name[i] != NULL; i++) {
        size = getrlimit(lim[i], rl);
        if (size == -1)
            return FAILURE;
        my_putstr(lim_name[i]);
        my_putstr("\t");
        if (rl->rlim_cur == RLIM_INFINITY)
            my_putstr("unlimited\n");
        else {
            my_putnbr(rl->rlim_cur);
            my_putstr("\n");
        }
    }
    return SUCCESS;
}

int builtin_limit(main_t *main_stock, command_ctx_t *ctx)
{
    struct rlimit rl;

    if (!ctx->arg_command[0])
        return display_limit(&rl);
    return SUCCESS;
}
