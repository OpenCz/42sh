/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Public API for all builtin commands: declares builtin_handler_t,
** builtin_command_t registry type, execute_builtin(), and every
** handler (env, cd, foreach, repeat, history, source, jobs...).
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#ifndef BUILTINS_H
    #define BUILTINS_H

    #include "core/types.h"
    #include <sys/resource.h>

typedef int (*builtin_handler_t)(main_t *main_stock, command_ctx_t *ctx);

typedef struct builtin_command_s {
    const char *name;
    builtin_handler_t func;
} builtin_command_t;

typedef struct handle_arg_s {
    char *var;
    char *arg;
} handle_arg_t;

typedef struct condition_s {
    char *token;
    int status;
    struct condition_s **arr;
} condition_t;

typedef struct limit_s {
    char *good_name;
    int good_lim;
} limit_t;

int builtin_history(main_t *main_stock, command_ctx_t *ctx);
int execute_builtin(main_t *main_stock, command_ctx_t *ctx);
int builtin_env(main_t *main_stock, command_ctx_t *ctx);
int builtin_setenv(main_t *main_stock, command_ctx_t *ctx);
int builtin_unsetenv(main_t *main_stock, command_ctx_t *ctx);
int builtin_cd(main_t *main_stock, command_ctx_t *ctx);
int builtin_jobs(main_t *main_stock, command_ctx_t *ctx);
int append_jobs(char **command, int pid, main_t *main_stock);
int builtin_foreground(main_t *main_stock, command_ctx_t *ctx);
int builtin_background(main_t *main_stock, command_ctx_t *ctx);
int builtin_repeat(main_t *main_stock, command_ctx_t *ctx);
int builtin_if(main_t *main_stock, command_ctx_t *ctx);
int builtin_foreach(main_t *main_stock, command_ctx_t *ctx);
char **foreach_read_commands(void);
int handle_error(command_ctx_t *ctx);
int put_error_var(char *var);
char *is_command(char *str);
char *append_buffer(command_ctx_t *ctx, int *i);
int builtin_printenv(main_t *main_stock, command_ctx_t *ctx);
int is_valid_formating(char **arr);
char *create_condition(main_t *main, command_ctx_t *ctx,
    char **else_cmd, char **to_exec);
int redirect_command(main_t *main, char *str);
int source(main_t *stock_main, command_ctx_t *ctx);

int my_env(main_t *main_stock);
int my_setenv(main_t *main_stock);
int my_unsetenv(main_t *main_stock);
int my_chdir(main_t *main_stock);
int builtin_set(main_t *main_stock, command_ctx_t *ctx);
int builtin_unset(main_t *stock, command_ctx_t *ctx);
int builtin_limit(main_t *main_stock, command_ctx_t *ctx);
int builtin_unlimit(main_t *main_stock, command_ctx_t *ctx);
void verif_time(char *name, struct rlimit *rl);
limit_t *get_good_limit(char *name);

#endif
