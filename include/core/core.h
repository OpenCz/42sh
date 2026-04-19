/*
** EPITECH PROJECT, 2026
** minishell
** File description:
** core api
*/

#ifndef CORE_H
    #define CORE_H

    #include "core/types.h"
    #define BUFFER_SIZE 4096
    #define ARROW_START '\x1b'

int manage_history(history_t *history, char *cmd);
int arrow_handling(history_t *history, char **buffer, int *cursor, int *len);
int get_command(char **buffer, history_t *history, char *user);
env_t *init_env(char **env);
main_t *init_main(char **env);
int set_command_context(main_t *stock_main, char *command);
int parse_command_context(char *command, command_ctx_t *ctx,
    main_t *stock_main);
void clear_command_ctx(command_ctx_t *ctx);
int bind_command_context(main_t *stock_main, command_ctx_t *ctx);

#endif
