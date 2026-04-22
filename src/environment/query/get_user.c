/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** The get_user.c
*/
/**
 * @file get_user.c
 * @brief The get_user.c
 * @author Erwan Lo Presti
 */

#include "c_zsh.h"

char *get_user(env_t *stock_env)
{
    for (env_t *tmp = stock_env; tmp; tmp = tmp->next) {
        if (my_strcmp(tmp->key, "USERNAME") == 0 && tmp->value != NULL)
            return tmp->value;
    }
    return NULL;
}
