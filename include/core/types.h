/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** All shell data structures: env_t, main_t, command_ctx_t,
** pipeline_segment_t, pipeline_state_t, history_t, history_cmd_t,
** loop_state_t, czshrc_t, prompt_t, infos_t, buffer_t.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#ifndef CORE_TYPES_H
    #define CORE_TYPES_H

    #include <sys/types.h>
    #include <stdbool.h>
    #include "../config/czshrc.h"

    #define CONTINUE -5
    #define TAB_WIDTH 4
    #define HISTORY 100

typedef struct alias_stock_s {
    char *new_name;
    char *command;
    bool is_fixed;
    struct alias_stock_s *next;
} alias_stock_t;

typedef struct history_cmd_s {
    int id;
    char *cmd;
    struct history_cmd_s *prev;
    struct history_cmd_s *next;
} history_cmd_t;

typedef struct history_s {
    history_cmd_t *history_cmd;
    history_cmd_t *curr_cmd;
    int id;
    char *curr;
} history_t;

typedef struct env_s {
    char *key;
    char *value;
    struct env_s *next;
} env_t;

typedef struct main_s {
    char *home;
    char *old_path;
    char **env;
    char **path;
    char *command;
    char **argv;
    char **arg_command;
    char *redirection;
    char *last_exit;
    history_t *history;
    alias_stock_t *alias_stock;
    struct env_s *stock_env;
    struct env_s *stock_local_var;
    czshrc_t *czshrc;
} main_t;

typedef struct command_ctx_s {
    char *command;
    char **argv;
    char **arg_command;
    char *redirection;
} command_ctx_t;

typedef struct pipeline_segment_s {
    char *command;
} pipeline_segment_t;

typedef struct pipeline_state_s {
    main_t *stock_main;
    pipeline_segment_t *segments;
    pid_t *pids;
    int prev_read;
    int count;
} pipeline_state_t;

typedef struct input_ctx_s {
    char *user;
    main_t *stock_main;
    char ch;
} input_ctx_t;

typedef struct loop_state_s {
    char *buffer;
    int last_exit;
    int cmd;
    bool prompt_displayed;
} loop_state_t;

typedef struct loop_env_state_s {
    env_t *existing_node;
    env_t *created_node;
    char *saved_value;
} loop_env_state_t;

typedef struct history_rc_s {
    int history;
    int savehist;
    bool enabled;
} history_rc_t;

#endif
