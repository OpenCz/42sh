/*
** EPITECH PROJECT, 2026
** get
** File description:
** home
*/

#include "42sh.h"

char *get_home(env_t *stock_env)
{
    for (env_t *tmp = stock_env; tmp; tmp = tmp->next) {
        if (my_strcmp(tmp->key, "HOME") == 0 && tmp->value != NULL)
            return tmp->value;
    }
    return NULL;
}
