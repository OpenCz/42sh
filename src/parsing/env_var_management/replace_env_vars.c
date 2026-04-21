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

    if (name[0] == '{') {
        i = 1;
        for (; name[i] && name[i] != '}'; i++);
        return i;
    }
    for (; name[i] && (isalnum(name[i]) || name[i] == '_'); i++);
    return i;
}

static char *is_hard(char *key)
{
    char *hard_keys[] = {"0", "36", "117 354 889 550", "69", "8", "21", NULL};
    char *hard_values[] = {"c_zsh", "Sacha Le Moign-Avalos", "Celenzo Peuch",
        "Lucas Soigneux", "Jessym Gaddacha", "Erwan Lo Presti", NULL};

    for (int i = 0; hard_keys[i]; i++) {
        if (my_strcmp(hard_keys[i], key) == 0)
            return hard_values[i];
    }
    return NULL;
}

static char *find_value(char *key, main_t *stock_main)
{
    bool is_braced = key[1] == '{';
    size_t key_len = 0;
    int offset = is_braced ? 2 : 1;
    char *value = NULL;

    if (!stock_main || key[0] != '$')
        return NULL;
    value = is_hard(key + offset);
    if (value)
        return value;
    key_len = get_var_name_len(key + 1) - (is_braced ? 1 : 0);
    if (key_len == 0)
        return NULL;
    for (env_t *e = stock_main->stock_env; e; e = e->next) {
        if (strlen(e->key) == key_len &&
            strncmp(e->key, key + offset, key_len) == 0)
            return e->value;
    }
    return NULL;
}

static int replace_single_arg(char **args, int i, main_t *stock_main)
{
    char *env_var = NULL;
    char *suffix = NULL;
    char *new_val = NULL;

    if (args[i][0] != '$')
        return 0;
    env_var = find_value(args[i], stock_main);
    if (!env_var) {
        my_putstr(args[i] + 1);
        free_alloc(args[i]);
        args[i] = my_strdup(": Undefined variable.");
        return 0;
    }
    suffix = args[i] + 1 + get_var_name_len(args[i] + 1)
        + (args[i][1] == '{' ? 1 : 0);
    new_val = my_strconcat(env_var, suffix);
    free_alloc(args[i]);
    args[i] = new_val;
    return 0;
}

char **replace_env_vars(char **args, main_t *stock_main)
{
    if (!args)
        return args;
    for (int i = 0; args[i] != NULL; i++)
        replace_single_arg(args, i, stock_main);
    return args;
}
