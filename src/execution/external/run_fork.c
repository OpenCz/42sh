/*
** EPITECH PROJECT, 2026
** run fork
** File description:
** run
*/
#include "c_zsh.h"

static void check_fork_failure(pid_t pid)
{
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

static int len_array(char **array)
{
    int i = 0;

    for (; array[i] != NULL; i++);
    return i;
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

static int handle_parent(pid_t pid, struct termios *term,
    main_t *stock_main, command_ctx_t *ctx)
{
    int status = 0;
    int actual = 1;
    char **command = malloc(sizeof(char *) * (len_array(ctx->arg_command) + 2));

    if (command == NULL)
        return 1;
    command[0] = strdup(ctx->command);
    for (int i = 0; ctx->arg_command[i] != NULL; i++) {
        command[actual] = strdup(ctx->arg_command[i]);
        actual++;
    }
    command[actual] = NULL;
    setpgid(pid, pid);
    tcsetpgrp(STDIN_FILENO, pid);
    waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, getpgrp());
    tcsetattr(STDIN_FILENO, TCSADRAIN, term);
    return get_seg(status, stock_main, pid, command);
}

int run_fork(main_t *main_stock, command_ctx_t *ctx, char *path, char **env)
{
    struct termios term;
    pid_t pid = 0;

    tcgetattr(STDIN_FILENO, &term);
    pid = fork();
    check_fork_failure(pid);
    if (pid == 0)
        handle_child(ctx, path, env);
    return handle_parent(pid, &term, main_stock, ctx);
}
