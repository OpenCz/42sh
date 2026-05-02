/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/42sh/src/builtins/limit
** File description:
** verif_time
*/

#include <sys/resource.h>
#include "c_zsh.h"

void verif_time(char *name, struct rlimit *rl)
{
    if (my_strcmp(name, "cputime") == 0) {
        if (rl->rlim_cur / 3600 > 0) {
            my_putnbr(rl->rlim_cur / 3600);
            my_putstr(":");
        }
        if (rl->rlim_cur / 3600 > 0
            && (rl->rlim_cur / 60) % 60 < 10)
            my_putstr("0");
        my_putnbr((rl->rlim_cur / 60) % 60);
        my_putstr(":");
        if (rl->rlim_cur % 60 < 10)
            my_putstr("0");
        my_putnbr(rl->rlim_cur % 60);
    } else
        my_putnbr(rl->rlim_cur);
}
