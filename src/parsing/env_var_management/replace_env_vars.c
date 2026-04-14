/*
** EPITECH PROJECT, 2026
** 42_sh
** File description:
** replace_env_vars
*/

#include "c_zsh.h"

static char *find_value(char *key, main_t *stock_main)
{
    for (env_t *head_env = stock_main->stock_env; head_env;
        head_env = head_env->next) {
        if (strncmp(head_env->key, key + 1, strlen(head_env->key)) == 0)
            return head_env->value;
    }
    return NULL;
}

static int is_there_env_vars(char **args)
{
    for (int i= 0; args[i]; i++) {
        if (args[i][0] == '$')
            return i;
    }
    return -1;
}

char **replace_env_vars(char **args, main_t *stock_main)
{
    char *env_var = NULL;
    int pos = is_there_env_vars(args);

    if (pos == -1)
        return args;
    env_var = find_value(args[pos], stock_main);
    if (!env_var)
        return args;
    free(args[pos]);
    args[pos] = my_strdup(env_var);
    return args;
}
