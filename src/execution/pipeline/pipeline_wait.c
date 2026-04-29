/*
** EPITECH PROJECT, 2026
** execute
** File description:
** pipeline wait
*/

#include "c_zsh.h"

int normalize_status(int status, main_t *stock_main, int pid, char *command)
{
    int seg_status = 0;

    if (status == 0x7f)
        return 1;
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSTOPPED(status))
        return 1;
    if (WIFSIGNALED(status)) {
        seg_status = get_seg(status, stock_main, pid, &command);
        if (seg_status != 0)
            return seg_status;
        return 128 + WTERMSIG(status);
    }
    return 1;
}

int wait_pipeline(pid_t *pids, int count, main_t *stock_main, char *command)
{
    int status = 0;
    int last_status = 1;

    for (int i = 0; i < count; i++)
        if (waitpid(pids[i], &status, 0) == pids[count - 1])
            last_status = normalize_status(status,
                stock_main, pids[i], command);
    return last_status;
}

int finalize_pipeline(pipeline_state_t *state, char *command)
{
    int segment_count = state->count;
    int exit_status = 1;

    if (state->prev_read != -1)
        close(state->prev_read);
    exit_status = wait_pipeline(state->pids, segment_count,
        state->stock_main, command);
    free_alloc(state->pids);
    for (int i = 0; i < segment_count; i++)
        free_alloc(state->segments[i].command);
    free_alloc(state->segments);
    return exit_status;
}
