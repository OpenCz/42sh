/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** USER query: get_user walks the env_t linked list looking for
** the node whose key equals USER and returns its value pointer.
** Used by the prompt renderer to display the current username.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

char *get_user(env_t *stock_env)
{
    for (env_t *tmp = stock_env; tmp; tmp = tmp->next) {
        if (my_strcmp(tmp->key, "USER") == 0 && tmp->value != NULL)
            return tmp->value;
    }
    return NULL;
}
