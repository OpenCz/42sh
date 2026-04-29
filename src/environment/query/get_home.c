/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** HOME query: get_home walks the env_t linked list looking for
** the node whose key equals HOME and returns its value pointer,
** or NULL if HOME is not set in the current environment.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

char *get_home(env_t *stock_env)
{
    for (env_t *tmp = stock_env; tmp; tmp = tmp->next) {
        if (my_strcmp(tmp->key, "HOME") == 0 && tmp->value != NULL)
            return tmp->value;
    }
    return NULL;
}
