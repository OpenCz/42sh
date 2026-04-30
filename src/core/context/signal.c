/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Shell signal init: setup_shell_signals ignores SIGINT, SIGTSTP,
** SIGTTOU, SIGTTIN and SIGQUIT; calls setpgid and tcsetpgrp to
** make the shell the foreground process-group leader.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

void setup_shell_signals(void)
{
    pid_t shell_pgid;

    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    shell_pgid = getpid();
    setpgid(shell_pgid, shell_pgid);
    tcsetpgrp(STDIN_FILENO, shell_pgid);
}
