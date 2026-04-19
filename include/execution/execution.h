/*
** EPITECH PROJECT, 2026
** minishell
** File description:
** execution api
*/

#ifndef EXECUTION_H
    #define EXECUTION_H

    #include <stdbool.h>
    #include "core/types.h"

int execute_command(main_t *stock_main, char *command);
int execute_single_command(main_t *stock_main,
    char *command, bool allow_builtin);

int execute_pipeline(main_t *stock_main, char *command);
int has_pipe_syntax_error(char *command);
int parse_pipeline(char *command, pipeline_segment_t **segments, int *count);
int init_pipeline_state(pipeline_state_t *state,
    main_t *stock_main, char *command);
int close_and_free(pipeline_state_t *state);
int create_pipe(int segment_count, int i, int pipefd[2]);
pid_t launch_segment(main_t *stock_main,
    char *command, int in_fd, int out_fd);
int push_segment(pipeline_state_t *state, int i);
int normalize_status(int status);
int wait_pipeline(pid_t *pids, int count);
int finalize_pipeline(pipeline_state_t *state);

int exec_any(main_t *main_stock, command_ctx_t *ctx);
int run_fork(main_t *main_stock, command_ctx_t *ctx, char *path, char **env);
int child_exec(command_ctx_t *ctx, char *path, char **env);
int get_seg(int status);

int apply_redirection(command_ctx_t *ctx);

int execute_operator(main_t *stock_main, char *command);

int builtin_where(main_t *main_stock, command_ctx_t *ctx);
int builtin_which(main_t *main_stock, command_ctx_t *ctx);

#endif
