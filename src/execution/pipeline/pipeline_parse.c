/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Pipeline state builder: parse_pipeline splits on '|' into a
** pipeline_segment_t array; init_pipeline_state allocates pids[];
** close_and_free releases all pipeline resources.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

int parse_pipeline(char *command, pipeline_segment_t **segments, int *count)
{
    char **commands = NULL;

    if (has_pipe_syntax_error(command)) {
        my_putstrerror("Invalid null command.\n");
        return 1;
    }
    commands = my_str_to_word_array_quote(command, "|");
    if (!commands)
        return 1;
    *count = my_wordarray_len(commands);
    *segments = malloc(sizeof(pipeline_segment_t) * (*count));
    if (!*segments) {
        free_array(commands);
        return 1;
    }
    for (int i = 0; i < *count; i++)
        (*segments)[i].command = commands[i];
    free_alloc(commands);
    return SUCCESS;
}

int init_pipeline_state(pipeline_state_t *state,
    main_t *stock_main, char *command)
{
    int count = 0;

    state->segments = NULL;
    state->pids = NULL;
    state->count = 0;
    if (parse_pipeline(command, &state->segments, &count))
        return -1;
    state->pids = malloc(sizeof(pid_t) * count);
    if (!state->pids) {
        free_alloc(state->segments);
        return -1;
    }
    state->stock_main = stock_main;
    state->prev_read = -1;
    state->count = count;
    return count;
}

int close_and_free(pipeline_state_t *state)
{
    if (state->prev_read != -1)
        close(state->prev_read);
    free_alloc(state->pids);
    if (state->segments) {
        for (int i = 0; i < state->count; i++)
            free_alloc(state->segments[i].command);
        free_alloc(state->segments);
    }
    return 1;
}
