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
    int rlen = result ? (int)strlen(result) : 0;
    char *new_result = malloc(rlen + len + 1);

    if (!new_result)
        return result;
    if (result)
        memcpy(new_result, result, rlen);
    memcpy(new_result + rlen, src, len);
    new_result[rlen + len] = '\0';
    free(result);
    return new_result;
}

static void update_quote_state(char c, int *in_single, int *in_double)
{
    if (c == '\'' && !*in_double)
        *in_single = !*in_single;
    if (c == '"' && !*in_single)
        *in_double = !*in_double;
}

static char *do_subst(char *inner_cmd, int len, main_t *stock_main)
{
    char *inner = strndup(inner_cmd, len);
    char *subst = inner ? command_substitution(stock_main, inner) : NULL;

    free(inner);
    if (!subst)
        subst = my_strdup("");
    return subst;
}

static char *do_subst_and_update(char *cmd, int i, int *bts, main_t *sm)
{
    char *s = do_subst(cmd + bts[0], i - bts[0], sm);

    bts[1] = i + 1;
    bts[0] = 0;
    return s;
}

static char *process_backtick_loop(char *cmd, char *result,
    main_t *stock_main)
{
    int in_single = 0;
    int in_double = 0;
    int bts[2] = {0, 0};
    char *s = NULL;

    for (int i = 0; cmd[i]; i++) {
        if (!bts[0])
            update_quote_state(cmd[i], &in_single, &in_double);
        if (cmd[i] != '`' || in_single || in_double)
            continue;
        if (!bts[0]) {
            result = append_str(result, cmd + bts[1], i - bts[1]);
            bts[0] = i + 1;
        } else {
            s = do_subst_and_update(cmd, i, bts, stock_main);
            result = append_str(result, s, strlen(s));
            free(s);
        }
    }
    return append_str(result, cmd + bts[1], strlen(cmd + bts[1]));
}

char *manage_backticks(char *cmd, main_t *stock_main)
{
    char *result = my_strdup("");

    if (!result)
        return NULL;
    return process_backtick_loop(cmd, result, stock_main);
}
