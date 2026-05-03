/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Variable substitution in argv
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../../include/c_zsh.h"

static size_t get_var_name_len(const char *name)
{
    size_t i = 0;

    if (!name || !name[0])
        return 0;
    if (name[0] == '{') {
        for (i = 1; name[i] && name[i] != '}'; i++);
        return i;
    }
    if (name[0] == '(') {
        for (i = 1; name[i] && name[i] != ')'; i++);
        return i;
    }
    if (isalnum((unsigned char)name[0]) || name[0] == '_') {
        for (; name[i] &&
            (isalnum((unsigned char)name[i]) || name[i] == '_'); i++);
    }
    return i ? i : 1;
}

static char *is_env(const char *key, size_t klen, main_t *m, int off)
{
    for (env_t *e = m->stock_local_var; e; e = e->next)
        if (strlen(e->key) == klen &&
            strncmp(e->key, key + off, klen) == 0)
            return e->value;
    for (env_t *e = m->stock_env; e; e = e->next)
        if (strlen(e->key) == klen &&
            strncmp(e->key, key + off, klen) == 0)
            return e->value;
    return NULL;
}

static char *manage_substitution(main_t *m, const char *key, int klen)
{
    char *command = strndup(key, klen);
    char *result = NULL;

    if (!command)
        return NULL;
    result = command_substitution(m, command);
    free(command);
    return result;
}

static char *find_value(char *key, main_t *m)
{
    bool braced = key[1] == '{';
    int off = braced ? 2 : 1;
    size_t klen = 0;
    char *v = NULL;

    if (!m || key[0] != '$')
        return NULL;
    klen = get_var_name_len(key + 1) - (braced ? 1 : 0);
    if (klen == 0)
        return NULL;
    if (key[1] == '(')
        return manage_substitution(m, key + 2, klen - 1);
    v = is_hard(key + off, klen, m);
    return v ? v : is_env(key, klen, m, off);
}

static char *build_new_val(char *arg, int dp, char *val, char *suffix)
{
    size_t plen = dp;
    size_t vlen = val ? strlen(val) : 0;
    size_t slen = strlen(suffix);
    char *new = malloc(plen + vlen + slen + 1);

    if (!new)
        return NULL;
    memcpy(new, arg, plen);
    if (vlen)
        memcpy(new + plen, val, vlen);
    memcpy(new + plen + vlen, suffix, slen + 1);
    return new;
}

static void drop_current_dollar(char *arg, int dp)
{
    size_t tail_len = strlen(arg + dp + 1);

    memmove(arg + dp, arg + dp + 1, tail_len + 1);
}

static void handle_undefined(char **args, int i, char *p, int dp)
{
    char *err = strdup(": Undefined variable.");

    my_putstr(p + 1);
    if (!err) {
        drop_current_dollar(args[i], dp);
        return;
    }
    free(args[i]);
    args[i] = err;
}

static void apply_substitution(char **args, int i, int dp, char *val)
{
    char *after = args[i] + dp + 1;
    size_t nlen = get_var_name_len(after);
    int closing = (after[0] == '{' || after[0] == '(') ? 1 : 0;
    char *new = build_new_val(args[i], dp, val, after + nlen + closing);

    if (!new) {
        drop_current_dollar(args[i], dp);
        return;
    }
    free(args[i]);
    args[i] = new;
}

static void replace_single_arg(char **args, int i, main_t *m)
{
    char *p = strchr(args[i], '$');
    int dp = p - args[i];
    bool free_val = p[1] == '$' || p[1] == '(' ||
        (p[1] == '{' && p[2] == '(');
    char *val = find_value(p, m);

    if (!val) {
        handle_undefined(args, i, p, dp);
        return;
    }
    apply_substitution(args, i, dp, val);
    if (free_val)
        free(val);
}

char **replace_env_vars(char **args, main_t *m)
{
    if (!args)
        return args;
    for (int i = 0; args[i]; i++)
        while (args[i] && strchr(args[i], '$'))
            replace_single_arg(args, i, m);
    return args;
}
