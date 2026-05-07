/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Fork/exec/wait: handle_child restores signals, setpgid(0,0),
** gives terminal, calls child_exec; handle_parent waits with
** WUNTRACED and restores the terminal to the shell on return.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/
#include "c_zsh.h"

static void check_fork_failure(pid_t pid)
{
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

static int handle_child(command_ctx_t *ctx, char *path, char **env)
{
    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    setpgid(0, 0);
    tcsetpgrp(STDIN_FILENO, getpid());
    if (apply_redirection(ctx) != 0)
        exit(1);
    exit(child_exec(ctx, path, env));
}

static void check_child_signals(int status)
{
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGXFSZ)
        my_putstrerror("filesize limit exceeded");
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGXCPU)
        my_putstrerror("cputime limit exceeded");
}

static void set_group_child(pid_t pid, int *status, struct termios *term)
{
    setpgid(pid, pid);
    tcsetpgrp(STDIN_FILENO, pid);
    waitpid(pid, status, WUNTRACED);
    check_child_signals(*status);
    tcsetpgrp(STDIN_FILENO, getpgrp());
    tcsetattr(STDIN_FILENO, TCSADRAIN, term);
}

static int exec_background(char **command, int pid, main_t *stock_main)
{
    int i = 0;
    job_controler_t *tmp = stock_main->controler->next;

    setpgid(pid, pid);
    if (append_jobs(command, pid, stock_main) == 0) {
        for (; tmp; i++)
            tmp = tmp->next;
        printf("[%d] %d\n", i, pid);
        return 0;
    }
    free_array(command);
    return 1;
}

static char **craft_command(command_ctx_t *ctx)
{
    int actual = 1;
    char **command = malloc(sizeof(char *) * (len_array(ctx->arg_command) + 2));

    if (command == NULL)
        return NULL;
    command[0] = strdup(ctx->command);
    for (int i = 0; ctx->arg_command[i] != NULL; i++) {
        command[actual] = strdup(ctx->arg_command[i]);
        actual++;
    }
    command[actual] = NULL;
    return command;
}

static int handle_parent(pid_t pid, struct termios *term,
    zipped_stock_t *zip, bool allow_background)
{
    int status = 0;
    main_t *main_stock = zip->main_stock;
    command_ctx_t *ctx = zip->ctx;
    char **command = craft_command(ctx);

    if (!command)
        return 1;
    if (allow_background)
        return exec_background(command, pid, main_stock);
    set_group_child(pid, &status, term);
    if (WIFEXITED(status)) {
        free_array(command);
        return WEXITSTATUS(status);
    }
    return get_seg(status, main_stock, pid, command);
}

int run_fork(zipped_stock_t *zip, char *path, char **env, bool allow_background)
{
    struct termios term;
    pid_t pid = 0;
    command_ctx_t *ctx = zip->ctx;

    tcgetattr(STDIN_FILENO, &term);
    pid = fork();
    check_fork_failure(pid);
    if (pid == 0)
        handle_child(ctx, path, env);
    return handle_parent(pid, &term, zip, allow_background);
}
