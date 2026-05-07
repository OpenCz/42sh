/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Substring search: iterates the haystack and at each position
** compares the next len(needle) chars using my_strncmp.
** Returns pointer to the first match, or NULL if not found.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

static void update_quote_state(char c, int *in_single, int *in_double,
    int *in_backtick)
{
    if (c == '\'' && !(*in_double) && !(*in_backtick))
        *in_single = !(*in_single);
    if (c == '"' && !(*in_single) && !(*in_backtick))
        *in_double = !(*in_double);
    if (c == '`' && !(*in_single) && !(*in_double))
        *in_backtick = !(*in_backtick);
}

const char *my_strstr(const char *str, const char *to_f)
{
    int k = 0;
    int in_single = 0;
    int in_double = 0;
    int in_backtick = 0;

    if (*to_f == '\0')
        return str;
    for (int i = 0; str[i] != '\0'; i++) {
        update_quote_state(str[i], &in_single, &in_double, &in_backtick);
        if (in_single || in_double || in_backtick)
            continue;
        for (k = 0; str[i + k] != '\0' && to_f[k] != '\0'
            && str[i + k] == to_f[k]; k++);
        if (to_f[k] == '\0')
            return &str[i];
    }
    return NULL;
}
