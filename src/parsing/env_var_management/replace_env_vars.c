/*
** EPITECH PROJECT, 2026
** 42_sh
** File description:
** replace_env_vars
*/

#include "../../../include/c_zsh.h"

static char *find_value(char *key, main_t *stock_main)
{
    char *key_name = NULL;
    size_t key_len = 0;

    if (!key || !stock_main || key[0] != '$')
        return NULL;
    key_name = key + 1;
    key_len = strlen(key_name);
    for (env_t *head_env = stock_main->stock_env;
        head_env; head_env = head_env->next)
        if (strlen(head_env->key) == key_len &&
            strncmp(head_env->key, key_name, key_len) == 0)
            return head_env->value;
    return NULL;
}

char **replace_env_vars(char **args, main_t *stock_main)
{
    char *env_var = NULL;

    if (!args)
        return args;
    for (int i = 0; args[i] != NULL; i++) {
        if (args[i][0] != '$')
            continue;
        env_var = find_value(args[i], stock_main);
        if (!env_var)
            continue;
        free(args[i]);
        args[i] = my_strdup(env_var);
    }
    return args;
}
