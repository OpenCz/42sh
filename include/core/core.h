/*
** EPITECH PROJECT, 2026
** minishell
** File description:
** core api
*/

#ifndef CORE_H
    #define CORE_H

    #include "core/types.h"

env_t *init_env(char **env);
main_t *init_main(char **env);
int set_command_context(main_t *stock_main, char *command);
int parse_command_context(char *command, command_ctx_t *ctx,
    main_t *stock_main);
void clear_command_ctx(command_ctx_t *ctx);
int bind_command_context(main_t *stock_main, command_ctx_t *ctx);

#endif
