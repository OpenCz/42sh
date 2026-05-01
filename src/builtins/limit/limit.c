/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/42sh/src/builtins/limit
** File description:
** limit
*/

#include "c_zsh.h"
#include <sys/time.h>
#include <sys/resource.h>

static int display_infos(int lim[], char *lim_name[], struct rlimit *rl, int i)
{
    int size = 0;

    size = getrlimit(lim[i], rl);
    if (size == -1)
        return FAILURE;
    my_putstr(lim_name[i]);
    for (int j = my_strlen(lim_name[i]); j < 13; j++)
        write(1, " ", 1);
    if (rl->rlim_cur == RLIM_INFINITY) {
        my_putstr("unlimited\n");
        return SUCCESS;
    }
    if (lim[i] == RLIMIT_STACK || lim[i] == RLIMIT_MEMLOCK) {
        my_putnbr(rl->rlim_cur / 1024);
        my_putstr(" kbytes\n");
    } else {
        verif_time(lim_name[i], rl);
        my_putstr(" \n");
    }
    return SUCCESS;
}

static int display_limit(struct rlimit *rl)
{
    int lim[16] = {RLIMIT_CPU, RLIMIT_FSIZE, RLIMIT_DATA, RLIMIT_STACK,
        RLIMIT_CORE, RLIMIT_RSS, RLIMIT_AS, RLIMIT_NOFILE, RLIMIT_MEMLOCK,
        RLIMIT_NPROC, RLIMIT_LOCKS, RLIMIT_SIGPENDING, RLIMIT_MSGQUEUE,
        RLIMIT_NICE, RLIMIT_RTPRIO, RLIMIT_RTTIME};
    char *lim_name[17] = {"cputime", "filesize", "datasize", "stacksize",
        "coredumpsize", "memoryuse", "vmemoryuse", "descriptors",
        "memorylocked", "maxproc", "maxlocks", "maxsignal",
        "maxmessage", "maxnice", "maxrtprio", "maxrttime", NULL};

    for (int i = 0; lim_name[i] != NULL; i++)
        if (display_infos(lim, lim_name, rl, i) == FAILURE)
            return FAILURE;
    return SUCCESS;
}

static int check_limit_name(char *name, struct rlimit *rl, limit_t *limit)
{
    if (getrlimit(limit->good_lim, rl) == -1)
        return 1;
    my_putstr(limit->good_name);
    for (int j = my_strlen(limit->good_name); j < 13; j++)
        write(1, " ", 1);
    if (rl->rlim_cur == RLIM_INFINITY) {
        my_putstr("unlimited\n");
        return SUCCESS;
    }
    if (limit->good_lim == RLIMIT_STACK || limit->good_lim == RLIMIT_MEMLOCK) {
        my_putnbr(rl->rlim_cur / 1024);
        my_putstr(" kbytes\n");
    } else {
        verif_time(limit->good_name, rl);
        my_putstr(" \n");
    }
    return SUCCESS;
}

static int handle_infinity(struct rlimit *rl, limit_t *limit)
{
    if (rl->rlim_max == RLIM_INFINITY)
        rl->rlim_cur = RLIM_INFINITY;
    else
        rl->rlim_cur = rl->rlim_max;
    if (setrlimit(limit->good_lim, rl) == -1)
        return 1;
    return SUCCESS;
}

static int change_limit(char *name, char *new_lim, struct rlimit *rl,
    limit_t *limit)
{
    unsigned long long nbr = 0;

    if (getrlimit(limit->good_lim, rl) == -1)
        return 1;
    if (my_strcmp(new_lim, "unlimited") == 0) {
        if (handle_infinity(rl, limit) == 1)
            return 1;
        return SUCCESS;
    }
    if (my_str_is_alpha(new_lim) == 1) {
        my_putstr("limit: Bad scaling factor.\n");
        return 1;
    }
    nbr = strtoull(new_lim, NULL, 10);
    rl->rlim_cur = nbr;
    if (setrlimit(limit->good_lim, rl) == -1)
        return 1;
    return SUCCESS;
}

static int return_value(int value, limit_t *limit)
{
    free(limit);
    return value;
}

static int handle_limit(command_ctx_t *ctx, struct rlimit *rl, limit_t *limit)
{
    if (my_wordarray_len(ctx->arg_command) == 1) {
        if (check_limit_name(ctx->arg_command[0], rl, limit) == 1) {
            return 1;
        }
        return SUCCESS;
    }
    if (change_limit(ctx->arg_command[0], ctx->arg_command[1], rl, limit)
        == 1) {
        return 1;
    }
    return SUCCESS;
}

int builtin_limit(main_t *main_stock, command_ctx_t *ctx)
{
    struct rlimit rl;
    limit_t *limit = NULL;

    if (!ctx->arg_command[0])
        return display_limit(&rl);
    if (my_strlen(ctx->arg_command[0]) == 1) {
        my_putstr("limit: No such limit.\n");
        return FAILURE;
    }
    limit = get_good_limit(ctx->arg_command[0]);
    if (!limit || limit->good_name == NULL)
        return 1;
    if (handle_limit(ctx, &rl, limit) == 1)
        return return_value(1, limit);
    return return_value(SUCCESS, limit);
}
