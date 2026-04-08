/*
** EPITECH PROJECT, 2026
** execute
** File description:
** pipeline spawn
*/

#include "minishell.h"

int create_pipe(int segment_count, int i, int pipefd[2])
{
    pipefd[0] = -1;
    pipefd[1] = -1;
    if (i + 1 >= segment_count)
        return SUCCESS;
    return pipe(pipefd) == -1;
}

pid_t launch_segment(main_t *stock_main,
    char *command, int in_fd, int out_fd)
{
    pid_t pid = fork();

    if (pid < 0)
        return -1;
    if (pid == 0) {
        if (in_fd != -1 && dup2(in_fd, STDIN_FILENO) == -1)
            exit(1);
        if (out_fd != -1 && dup2(out_fd, STDOUT_FILENO) == -1)
            exit(1);
        if (in_fd != -1)
            close(in_fd);
        if (out_fd != -1)
            close(out_fd);
        exit(execute_single_command(stock_main, command, true));
    }
    return pid;
}

int push_segment(pipeline_state_t *state, int i)
{
    int pipefd[2];

    if (create_pipe(state->count, i, pipefd))
        return 1;
    state->pids[i] = launch_segment(state->stock_main,
        state->segments[i].command, state->prev_read, pipefd[1]);
    if (state->pids[i] < 0)
        return 1;
    if (state->prev_read != -1)
        close(state->prev_read);
    if (pipefd[1] != -1)
        close(pipefd[1]);
    state->prev_read = pipefd[0];
    return SUCCESS;
}
