/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** PATH query: get_path walks the env_t linked list looking for
** the node whose key equals PATH and returns its raw value,
** or NULL if PATH is not set in the current environment.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

char *get_path(env_t *stock_env)
{
    for (env_t *tmp = stock_env; tmp; tmp = tmp->next) {
        if (my_strcmp(tmp->key, "PATH") == 0 && tmp->value != NULL)
            return tmp->value;
    }
    return NULL;
}
