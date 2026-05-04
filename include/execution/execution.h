/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Public API for the execution layer: execute_command (;-dispatch),
** execute_single_command, execute_pipeline,
** parse_pipeline, init_pipeline_state, close_and_free, create_pipe.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#ifndef EXECUTION_H
    #define EXECUTION_H

    #include <stdbool.h>
    #include "core/types.h"

int execute_command(main_t *stock_main, char *command);
int execute_single_command(main_t *stock_main,
    char *command, bool allow_builtin, bool allow_background);

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
int normalize_status(int status, main_t *stock_main, int pid, char *command);
int wait_pipeline(pid_t *pids, int count, main_t *stock_main, char *command);
int finalize_pipeline(pipeline_state_t *state, char *command);

int exec_any(main_t *main_stock, command_ctx_t *ctx, bool allow_background);
int run_fork(zipped_stock_t *zip, char *path, char **env, bool allow_background);
int child_exec(command_ctx_t *ctx, char *path, char **env);
int get_seg(int status, main_t *stock_main, int pid, char **command);
int append_jobs(char **command, int pid, main_t *main_stock);

int apply_redirection(command_ctx_t *ctx);

int execute_operator(main_t *stock_main, char *command);
int has_pipeline_operator(char *command);
char **get_array_arg(command_ctx_t *ctx);
void fill_arg(char **arg, command_ctx_t *ctx, int i, int j);
int get_len_arg(command_ctx_t *ctx);

int builtin_where(main_t *main_stock, command_ctx_t *ctx);
int builtin_which(main_t *main_stock, command_ctx_t *ctx);

int builtin_alias(main_t *main_stock, command_ctx_t *ctx);

#endif
