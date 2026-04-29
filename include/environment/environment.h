/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Public API for environment access and binary resolution:
** get_path, get_home, get_user, find_env_node,
** check_bin (one dir), loop_bin (iterate PATH).
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
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
