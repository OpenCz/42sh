/*
** EPITECH PROJECT, 2026
** 42_sh
** File description:
** replace_env_vars
*/

#include "c_zsh.h"

static size_t get_var_name_len(const char *name)
{
    size_t i = 0;

    for (; name[i] && (isalnum(name[i]) || name[i] == '_'); i++);
    return i;
}

static char *find_value(char *key, main_t *stock_main)
{
    size_t key_len = 0;

    if (!key || !stock_main || key[0] != '$')
        return NULL;
    key_len = get_var_name_len(key + 1);
    if (key_len == 0)
        return NULL;
    for (env_t *head_env = stock_main->stock_env;
        head_env; head_env = head_env->next)
        if (strlen(head_env->key) == key_len &&
            strncmp(head_env->key, key + 1, key_len) == 0)
            return head_env->value;
    return NULL;
}

static void replace_single_arg(char **args, int i, main_t *stock_main)
{
    char *env_var = NULL;
    char *suffix = NULL;
    char *new_val = NULL;
    size_t var_len = 0;

    if (args[i][0] != '$')
        return;
    env_var = find_value(args[i], stock_main);
    if (!env_var)
        return;
    var_len = get_var_name_len(args[i] + 1);
    suffix = args[i] + 1 + var_len;
    new_val = malloc(strlen(env_var) + strlen(suffix) + 1);
    if (!new_val)
        return;
    strcpy(new_val, env_var);
    strcat(new_val, suffix);
    free_alloc(args[i]);
    args[i] = new_val;
}

char **replace_env_vars(char **args, main_t *stock_main)
{
    if (!args)
        return args;
    for (int i = 0; args[i] != NULL; i++)
        replace_single_arg(args, i, stock_main);
    return args;
}
