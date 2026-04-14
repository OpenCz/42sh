/*
** EPITECH PROJECT, 2026
** execute
** File description:
** pipeline wait
*/

#include "c_zsh.h"

int normalize_status(int status)
{
    if (WIFSIGNALED(status))
        return get_seg(status);
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return 1;
}

int wait_pipeline(pid_t *pids, int count)
{
    int status = 0;
    int last_status = 1;

    for (int i = 0; i < count; i++) {
        if (waitpid(pids[i], &status, 0) == pids[count - 1])
            last_status = normalize_status(status);
    }
    return last_status;
}

int finalize_pipeline(pipeline_state_t *state)
{
    int segment_count = state->count;
    int exit_status = 1;

    if (state->prev_read != -1)
        close(state->prev_read);
    exit_status = wait_pipeline(state->pids, segment_count);
    free(state->pids);
    for (int i = 0; i < segment_count; i++)
        free(state->segments[i].command);
    free(state->segments);
    return exit_status;
}
