/*
** EPITECH PROJECT, 2026
** error
** File description:
** error
*/

#include "c_zsh.h"

static void setup_child_signal(void)
{
    sigset_t mask;

    sigemptyset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGXFSZ, SIG_DFL);
    signal(SIGXCPU, SIG_DFL);
}

int child_exec(command_ctx_t *ctx, char *path, char **env)
{
    setup_child_signal();
    if (execve(path, ctx->argv, env) == -1) {
        my_putstrerror(ctx->command);
        if (errno == ENOEXEC) {
            my_putstr(": Exec format error. ");
            my_putstr("Binary file not executable.\n");
            return 126;
        }
        if (errno == EACCES) {
            my_putstr(": Permission denied.\n");
            return 126;
        }
    }
    return SUCCESS;
}

void wait_stop(int status, main_t *stock_main, int pid, char **command)
{
    if (WIFSTOPPED(status)) {
        my_putstr("\nSuspended\n");
        append_jobs(command, pid, stock_main);
    } else {
        free_array(command);
    }
}

int get_seg(int status, main_t *stock_main, int pid, char **command)
{
    int sig = WTERMSIG(status);
    int exit_value = 0;

    if (sig == SIGINT) {
        write(1, "\n", 1);
        return 130;
    }
    if (sig == SIGFPE) {
        write(1, "Floating exception\n", 19);
        exit_value = 136;
    }
    if (sig == SIGSEGV) {
        write(1, "Segmentation fault\n", 19);
        exit_value = 139;
    }
    if (WCOREDUMP(status))
        write(1, " (core dumped)\n", 15);
    wait_stop(status, stock_main, pid, command);
    return exit_value;
}
