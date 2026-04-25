/*
** EPITECH PROJECT, 2026
** minishell
** File description:
** core types
*/

#ifndef CORE_TYPES_H
    #define CORE_TYPES_H

    #include <sys/types.h>

    #define CONTINUE -5

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
    history_t *history;
    alias_stock_t *alias_stock;
    struct env_s *stock_env;
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


#endif
