/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/42sh/src/builtins/limit
** File description:
** unlimit
*/

#include "c_zsh.h"
#include <sys/time.h>
#include <sys/resource.h>

static int change_unlimited_all(struct rlimit *rl)
{
    int lim[16] = {RLIMIT_CPU, RLIMIT_FSIZE, RLIMIT_DATA, RLIMIT_STACK,
        RLIMIT_CORE, RLIMIT_RSS, RLIMIT_AS, RLIMIT_NOFILE, RLIMIT_MEMLOCK,
        RLIMIT_NPROC, RLIMIT_LOCKS, RLIMIT_SIGPENDING, RLIMIT_MSGQUEUE,
        RLIMIT_NICE, RLIMIT_RTPRIO, RLIMIT_RTTIME};
    char *lim_name[17] = {"cputime", "filesize", "datasize", "stacksize",
        "coredumpsize", "memoryuse", "vmemoryuse", "descriptors",
        "memorylocked", "maxproc", "maxlocks", "maxsignal",
        "maxmessage", "maxnice", "maxrtprio", "maxrttime", NULL};

    rl->rlim_cur = RLIM_INFINITY;
    rl->rlim_max = RLIM_INFINITY;
    for (int i = 0; lim_name[i] != NULL; i++)
        if (setrlimit(lim[i], rl) == -1)
            return 1;
    return SUCCESS;
}

static int change_unlimited_one(command_ctx_t *ctx, struct rlimit *rl)
{
    limit_t *limit = get_good_limit(ctx->arg_command[0]);

    if (!limit || limit->good_name == NULL)
        return 1;
    rl->rlim_cur = RLIM_INFINITY;
    rl->rlim_max = RLIM_INFINITY;
    if (setrlimit(limit->good_lim, rl) == -1) {
        my_putstr("unlimit: Can't set limit.\n");
        free(limit);
        return 1;
    }
    free(limit);
    return SUCCESS;
}

int builtin_unlimit(main_t *main_stock, command_ctx_t *ctx)
{
    struct rlimit rl;

    if (!ctx->arg_command[0]) {
        if (change_unlimited_all(&rl) == 1)
            return 1;
        return SUCCESS;
    }
    if (my_wordarray_len(ctx->arg_command) == 1) {
        return change_unlimited_one(ctx, &rl);
    }
    my_putstr("unlimit: Bad scaling factor.\n");
    return 1;
}
