/*
** EPITECH PROJECT, 2026
** minishell
** File description:
** builtins api
*/

#ifndef BUILTINS_H
    #define BUILTINS_H

    #include "core/types.h"

typedef int (*builtin_handler_t)(main_t *main_stock, command_ctx_t *ctx);

typedef struct builtin_command_s {
    const char *name;
    builtin_handler_t func;
} builtin_command_t;

int execute_builtin(main_t *main_stock, command_ctx_t *ctx);
int builtin_env(main_t *main_stock, command_ctx_t *ctx);
int builtin_setenv(main_t *main_stock, command_ctx_t *ctx);
int builtin_unsetenv(main_t *main_stock, command_ctx_t *ctx);
int builtin_cd(main_t *main_stock, command_ctx_t *ctx);
int builtin_jobs(main_t *main_stock, command_ctx_t *ctx);
int builtin_foreground(main_t *main_stock, command_ctx_t *ctx);
int builtin_background(main_t *main_stock, command_ctx_t *ctx);
int builtin_repeat(main_t *main_stock, command_ctx_t *ctx);

int my_env(main_t *main_stock);
int my_setenv(main_t *main_stock);
int my_unsetenv(main_t *main_stock);
int my_chdir(main_t *main_stock);

#endif
