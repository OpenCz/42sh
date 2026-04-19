/*
** EPITECH PROJECT, 2026
** get
** File description:
** path
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
