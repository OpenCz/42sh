/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** Quote-aware backtick substitution: backticks inside single or
** double quotes are treated as literal characters, not as command
** substitution delimiters.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../../include/c_zsh.h"

static char *append_str(char *result, const char *src, int len)
{
    int rlen = result ? strlen(result) : 0;
    char *new_result = malloc(rlen + len + 1);

    if (!new_result)
        return NULL;
    if (result)
        memcpy(new_result, result, rlen);
    memcpy(new_result + rlen, src, len);
    new_result[rlen + len] = '\0';
    return new_result;
}

static void update_quote_state(char c, int *in_single, int *in_double)
{
    if (c == '\'' && !(*in_double))
        *in_single = !(*in_single);
    if (c == '"' && !(*in_single))
        *in_double = !(*in_double);
}

static char *do_subst_and_update(char *cmd, int i, int *bts, main_t *sm)
{
    char *inner = strndup(cmd + bts[0], i - bts[0]);
    char *s = inner ? command_substitution(sm, inner) : NULL;

    free_alloc(inner);
    if (!s)
        s = strdup("");
    bts[1] = i + 1;
    bts[0] = 0;
    return s;
}

static char *handle_opening_backtick(char *cmd, char *result,
    int i, int *bts)
{
    char *s = append_str(result, cmd + bts[1], i - bts[1]);

    free_alloc(result);
    if (!s)
        return NULL;
    bts[1] = i;
    bts[0] = i + 1;
    return s;
}

static char *do_append_subst(char *result, char *subst)
{
    char *new = NULL;

    if (!subst)
        return NULL;
    new = append_str(result, subst, strlen(subst));
    free_alloc(subst);
    free_alloc(result);
    return new;
}

static char *append_tail(char *cmd, char *result, int bts1)
{
    char *s = append_str(result, cmd + bts1, strlen(cmd + bts1));

    free_alloc(result);
    return s;
}

static char *process_backtick_loop(char *cmd, char *result,
    main_t *stock_main)
{
    int in_single = 0;
    int in_double = 0;
    int bts[2] = {0, 0};

    for (int i = 0; cmd[i]; i++) {
        if (!bts[0])
            update_quote_state(cmd[i], &in_single, &in_double);
        if (cmd[i] != '`' || in_single || in_double)
            continue;
        if (!bts[0])
            result = handle_opening_backtick(cmd, result, i, bts);
        else
            result = do_append_subst(result,
                do_subst_and_update(cmd, i, bts, stock_main));
        if (!result)
            return NULL;
    }
    return append_tail(cmd, result, bts[1]);
}

char *manage_backticks(char *cmd, main_t *stock_main)
{
    char *result = strdup("");

    if (!result)
        return NULL;
    return process_backtick_loop(cmd, result, stock_main);
}
