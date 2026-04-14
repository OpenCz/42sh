/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_pipeline
*/

#include <criterion/criterion.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/42sh.h"

Test(pipeline_syntax, detects_invalid_and_valid_pipes)
{
    cr_assert_eq(has_pipe_syntax_error("| cmd"), 1);
    cr_assert_eq(has_pipe_syntax_error("cmd |"), 1);
    cr_assert_eq(has_pipe_syntax_error("cmd || next"), 1);
    cr_assert_eq(has_pipe_syntax_error("cmd | next"), SUCCESS);
}

Test(pipeline_parse, parses_and_cleans_valid_pipeline)
{
    pipeline_segment_t *segments = NULL;
    int count = 0;
    pipeline_state_t state = {0};

    cr_assert_eq(parse_pipeline("true|false", &segments, &count), SUCCESS);
    cr_assert_eq(count, 2);
    cr_assert_str_eq(segments[0].command, "true");
    cr_assert_str_eq(segments[1].command, "false");
    state.segments = segments;
    state.count = count;
    cr_assert_eq(close_and_free(&state), 1);
}

Test(pipeline_parse, rejects_invalid_syntax)
{
    pipeline_segment_t *segments = NULL;
    int count = 0;

    cr_assert_eq(parse_pipeline("|true", &segments, &count), 1);
}

Test(pipeline_state, init_pipeline_state_success_and_cleanup)
{
    pipeline_state_t state = {0};
    main_t stock = {0};
    int count = init_pipeline_state(&state, &stock, "true|false");

    cr_assert_eq(count, 2);
    cr_assert_not_null(state.segments);
    cr_assert_not_null(state.pids);
    cr_assert_str_eq(state.segments[0].command, "true");
    cr_assert_str_eq(state.segments[1].command, "false");
    state.prev_read = open("/dev/null", O_RDONLY);
    cr_assert(state.prev_read != -1);
    cr_assert_eq(close_and_free(&state), 1);
}

Test(pipeline_state, init_pipeline_state_rejects_invalid_command)
{
    pipeline_state_t state = {0};
    main_t stock = {0};

    cr_assert_eq(init_pipeline_state(&state, &stock, "|true"), -1);
}

Test(pipeline_spawn, create_pipe_handles_last_and_non_last_segments)
{
    int pipefd[2];
    int last_pipefd[2];

    cr_assert_eq(create_pipe(2, 0, pipefd), SUCCESS);
    cr_assert_geq(pipefd[0], 0);
    cr_assert_geq(pipefd[1], 0);
    close(pipefd[0]);
    close(pipefd[1]);
    cr_assert_eq(create_pipe(2, 1, last_pipefd), SUCCESS);
    cr_assert_eq(last_pipefd[0], -1);
    cr_assert_eq(last_pipefd[1], -1);
}

Test(pipeline_wait, normalizes_exit_and_signal_statuses)
{
    cr_assert_eq(normalize_status(W_EXITCODE(7, 0)), 7);
    cr_assert_eq(normalize_status(0x7f), 1);
    cr_assert_eq(normalize_status(SIGSEGV | 0x80), 139);
    cr_assert_eq(normalize_status(SIGFPE | 0x80), 136);
}

Test(pipeline_wait, waits_for_last_child_status)
{
    pid_t pids[2];
    int status = 0;

    pids[0] = fork();
    cr_assert_geq(pids[0], 0);
    if (pids[0] == 0)
        _exit(0);
    pids[1] = fork();
    cr_assert_geq(pids[1], 0);
    if (pids[1] == 0)
        _exit(3);
    status = wait_pipeline(pids, 2);
    cr_assert_eq(status, 3);
}

Test(pipeline_execute, runs_valid_pipeline_and_returns_last_status)
{
    main_t stock = {0};

    cr_assert_eq(execute_pipeline(&stock, "true|true"), 0);
}

Test(pipeline_execute, rejects_invalid_pipeline_syntax)
{
    main_t stock = {0};

    cr_assert_eq(execute_pipeline(&stock, "true||false"), 1);
}

