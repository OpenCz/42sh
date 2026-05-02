/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Signal handlers for resource limit signals (SIGXCPU, SIGXFSZ)
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/
#include "c_zsh.h"
#include <sys/signalfd.h>
#include <errno.h>

int setup_signalfd(void)
{
    sigset_t mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGXCPU);
    sigprocmask(SIG_BLOCK, &mask, NULL);
    return signalfd(-1, &mask, SFD_CLOEXEC | SFD_NONBLOCK);
}

void handle_limit_signals(int sfd, signal_t *signals)
{
    struct signalfd_siginfo info;
    ssize_t ret;

    if (sfd < 0)
        return;
    ret = read(sfd, &info, sizeof(info));
    if (ret < 0 && errno == EAGAIN)
        return;
    if (ret != (ssize_t)sizeof(info))
        return;
    if (info.ssi_signo == SIGXCPU)
        signals->g_sigxcpu = 1;
}

static int cpu_limit_is_zero(void)
{
    struct rlimit rl;

    if (getrlimit(RLIMIT_CPU, &rl) < 0)
        return false;
    return rl.rlim_cur == 1;
}

int check_limit_signals(signal_t *signals)
{
    if (signals->g_sigxcpu || cpu_limit_is_zero()) {
        my_putstrerror("cputime limit exceeded\n");
        return 1;
    }
    return 0;
}

void setup_shell_signals(signal_t *signals)
{
    pid_t shell_pgid;

    signals->g_sigxcpu = 0;
    signals->sfd = setup_signalfd();
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    shell_pgid = getpid();
    setpgid(shell_pgid, shell_pgid);
    tcsetpgrp(STDIN_FILENO, shell_pgid);
}
