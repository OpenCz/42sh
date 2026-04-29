/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Pipeline orchestrator: validates syntax, then calls
** parse_pipeline, init_pipeline_state, run_pipeline_segments
** (spawn loop) and finalize_pipeline (wait + free).
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

static int run_pipeline_segments(pipeline_state_t *state, int count)
{
    for (int i = 0; i < count; i++)
        if (push_segment(state, i))
            return close_and_free(state);
    return SUCCESS;
}

int execute_pipeline(main_t *stock_main, char *command)
{
    pipeline_state_t state;
    int count = init_pipeline_state(&state, stock_main, command);

    if (count < 0)
        return 1;
    if (run_pipeline_segments(&state, count))
        return 1;
    return finalize_pipeline(&state);
}
