/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Variable substitution in argv: get_var_name_len reads the
** identifier after '$'; find_value looks it up in stock_env;
** replace_env_vars iterates all argv tokens and replaces each.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../../include/c_zsh.h"

static size_t get_var_name_len(const char *name)
{
    size_t i = 0;

    if (!name || !name[0])
        return 0;
    if (name[0] == '{') {
        i = 1;
        for (; name[i] && name[i] != '}'; i++);
        return i;
    }
    if (name[0] == '(') {
        i = 1;
        for (; name[i] && name[i] != ')'; i++);
        return i;
    }
    if (isalnum((unsigned char)name[0]) || name[0] == '_') {
        for (; name[i] &&
            (isalnum((unsigned char)name[i]) || name[i] == '_'); i++);
        return i;
    }
    return 1;
}

static char *is_env(const char *key, size_t key_len, main_t *stock_main,
    int offset)
{
    for (env_t *e = stock_main->stock_local_var; e; e = e->next)
        if (strlen(e->key) == key_len &&
            strncmp(e->key, key + offset, key_len) == 0)
            return e->value;
    for (env_t *e = stock_main->stock_env; e; e = e->next)
        if (strlen(e->key) == key_len &&
            strncmp(e->key, key + offset, key_len) == 0)
            return e->value;
    return NULL;
}

static char *manage_substitution(main_t *stock_main, const char *key,
    int key_len)
{
    char *command = strndup(key, key_len);
    char *result = NULL;

    if (!command)
        return NULL;
    result = command_substitution(stock_main, command);
    free(command);
    return result;
}

static char *find_value(char *key, main_t *stock_main)
{
    bool is_braced = key[1] == '{';
    size_t key_len = 0;
    int offset = is_braced ? 2 : 1;
    char *value = NULL;

    if (!stock_main || key[0] != '$')
        return NULL;
    key_len = get_var_name_len(key + 1) - (is_braced ? 1 : 0);
    if (key_len == 0)
        return NULL;
    if (key[1] == '(')
        return manage_substitution(stock_main, key + 2, key_len - 1);
    value = is_hard(key + offset, key_len, stock_main);
    if (value)
        return value;
    return is_env(key, key_len, stock_main, offset);
}

static void undefined_var(char *env_var, char **args, int i, int doll_pos)
{
    if (env_var)
        return;
    my_putstr(args[i] + doll_pos + 1);
    free(args[i]);
    args[i] = strdup(": Undefined variable.");
}

static int find_doll(char *arg)
{
    int i = 0;

    for (; arg[i] && arg[i] != '$'; i++);
    return i;
}

static char *compute_suffix(char *arg, int doll_pos)
{
    char *after_doll = arg + doll_pos + 1;
    size_t name_len = get_var_name_len(after_doll);
    int closing = (after_doll[0] == '{' || after_doll[0] == '(') ? 1 : 0;

    return after_doll + name_len + closing;
}

static char *build_new_val(char *arg, int doll_pos, char *env_var,
    char *suffix)
{
    size_t plen = doll_pos;
    size_t vlen = env_var ? strlen(env_var) : 0;
    size_t slen = strlen(suffix);
    char *new_val = malloc(plen + vlen + slen + 1);

    if (!new_val)
        return NULL;
    memcpy(new_val, arg, plen);
    if (vlen)
        memcpy(new_val + plen, env_var, vlen);
    memcpy(new_val + plen + vlen, suffix, slen + 1);
    return new_val;
}

static int replace_single_arg(char **args, int i, main_t *stock_main)
{
    char *env_var = NULL;
    char *suffix = NULL;
    int is_subst = 0;
    int doll_pos = find_doll(args[i]);

    if (args[i][doll_pos + 1] == '(' || (args[i][doll_pos + 1] == '{'
            && args[i][doll_pos + 2] == '('))
        is_subst = 1;
    env_var = find_value(args[i] + doll_pos, stock_main);
    undefined_var(env_var, args, i, doll_pos);
    if (!env_var)
        return 0;
    suffix = compute_suffix(args[i], doll_pos);
    args[i] = build_new_val(args[i], doll_pos, env_var, suffix);
    if (is_subst)
        free(env_var);
    return 0;
}

char **replace_env_vars(char **args, main_t *stock_main)
{
    if (!args)
        return args;
    for (int i = 0; args[i] != NULL; i++)
        while (args[i] && strstr(args[i], "$") != NULL)
            replace_single_arg(args, i, stock_main);
    return args;
}
