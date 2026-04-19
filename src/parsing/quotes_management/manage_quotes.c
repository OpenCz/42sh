/*
** EPITECH PROJECT, 2026
** 42_sh
** File description:
** manage_quotes
*/

#include "c_zsh.h"
#include <stdlib.h>
#include <string.h>

static char get_escape(char c)
{
    char escapes[] = {'n', 't', 'r', 'a', 'b', 'f', 'v', '\\', '"', '\0'};
    char values[] = {'\n', '\t', '\r', '\a', '\b', '\f', '\v', '\\', '"', '\0'};
    int i = 0;

    while (escapes[i]) {
        if (escapes[i] == c)
            return values[i];
        i++;
    }
    return c;
}

static char *get_result(char *cmd, char *result, int *j)
{
    int in_quotes = 0;

    for (int i = 0; cmd[i]; i++) {
        if (cmd[i] == '"') {
            in_quotes = !in_quotes;
            continue;
        }
        if (in_quotes && cmd[i] == '\\' && cmd[i + 1]) {
            result[*j] = get_escape(cmd[i + 1]);
            (*j)++;
            i++;
        } else {
            result[*j] = cmd[i];
            (*j)++;
        }
    }
    return result;
}

char *convert_quotes(char *cmd)
{
    char *result = NULL;
    int j = 0;

    result = malloc(sizeof(char) * (strlen(cmd) + 1));
    if (!result)
        return NULL;
    result = get_result(cmd, result, &j);
    result[j] = '\0';
    return result;
}
