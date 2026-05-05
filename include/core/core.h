/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Public API for the shell core: init_main, init_env, get_command
** (interactive input), manage_history, arrow_handling,
** parse_command_context, set_command_context, clear_command_ctx.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#ifndef CORE_H
    #define CORE_H

    #include "core/types.h"
    #define BUFFER_SIZE 4096
    #define ARROW_START '\x1b'

int manage_history(history_t *history, char **cmd);
int arrow_handling(history_t *history, char **buffer, int *cursor, int *len);
int get_command(main_t *stock_main, char **buffer, history_t *history,
    char *user);
env_t *init_env(char **env);
main_t *init_main(char **env);
int set_command_context(main_t *stock_main, char *command);
int parse_command_context(char *command, command_ctx_t *ctx,
    main_t *stock_main);
void clear_command_ctx(command_ctx_t *ctx);
int bind_command_context(main_t *stock_main, command_ctx_t *ctx);
void init_termios(struct termios *tr, struct termios *old);
void setup_shell_signals(signal_t *signals);
void write_tty(char *buffer);
void write_print(main_t *stock);
int handle_ctrl_l(main_t *stock_main, char *user);
int handle_ctrl_d(int *len, char *user, main_t *stock_main);
int handle_ctrl_c(buffer_t *buff, int *cursor, char *user, main_t *stock_main);
int handle_input_char(history_t *history, buffer_t *buff,
    int *cursor, input_ctx_t *ctx);
int append_char(char **buffer, char ch, int *len, int *cursor);
int get_display_width(char ch);
void write_tab_spaces(void);
int get_buffer_display_width(char *buffer, int len);
int check_limit_signals(signal_t *signals);
void handle_limit_signals(int sfd, signal_t *signals);
int handle_autocomplete(char **buffer, int *len, int *cursor,
    main_t *main_stock);

#endif
