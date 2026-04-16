/*
** EPITECH PROJECT, 2026
** minishell
** File description:
** environment api
*/

#ifndef ENVIRONMENT_H
    #define ENVIRONMENT_H

    #include "core/types.h"

char *get_path(env_t *stock_env);
char *get_home(env_t *stock_env);
char *get_user(env_t *stock_env);
env_t *find_env_node(env_t *env, char *key, env_t **prev);
char *loop_bin(main_t *main_stock, char *command);
char *check_bin(char *command, char *path);

#endif
