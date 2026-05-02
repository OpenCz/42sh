/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Inhibitor processing: convert_quotes strips outer quotes and resolves
** escapes — double quotes allow C escape sequences, single quotes make
** all content literal ($ is replaced with \x01 to survive variable
** expansion). decode_literals restores \x01 back to $ afterwards.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

static char get_escape(char c)
{
    char escapes[] = {'n', 't', 'r', 'a', 'b', 'f', 'v', '\\', '"', '\0'};
    char values[] = {'\n', '\t', '\r', '\a', '\b', '\f', '\v', '\\', '"', '\0'};

    for (int i = 0; escapes[i]; i++)
        if (escapes[i] == c)
            return values[i];
    return c;
}

static void handle_quote(int *state, char c)
{
    if (c == '"' && !state[1])
        state[0] = !state[0];
    if (c == '\'' && !state[0])
        state[1] = !state[1];
}

static int should_toggle_quote(int *state, char c)
{
    if (c == '"' && !state[1])
        return 1;
    if (c == '\'' && !state[0])
        return 1;
    return 0;
}

static void handle_body(char *cmd, char *result, int *i, int *state)
{
    if (state[1]) {
        result[state[2]] = (cmd[*i] == '$') ? '\x01' : cmd[*i];
        state[2]++;
        return;
    }
    if (state[0] && cmd[*i] == '\\' && cmd[*i + 1]) {
        result[state[2]] = get_escape(cmd[*i + 1]);
        (*i)++;
    } else
        result[state[2]] = cmd[*i];
    state[2]++;
}

static char *get_result(char *cmd, char *result, int *j)
{
    int state[3] = {0, 0, 0};

    for (int i = 0; cmd[i]; i++) {
        if (should_toggle_quote(state, cmd[i])) {
            handle_quote(state, cmd[i]);
            continue;
        }
        handle_body(cmd, result, &i, state);
    }
    *j = state[2];
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

char *decode_literals(char *str)
{
    char *result = NULL;
    int j = 0;

    if (!str)
        return NULL;
    result = malloc(strlen(str) + 1);
    if (!result)
        return NULL;
    for (int i = 0; str[i]; i++) {
        result[j] = (str[i] == '\x01') ? '$' : str[i];
        j++;
    }
    result[j] = '\0';
    return result;
}

int is_escaped(char *str, int index)
{
    int backslashes = 0;

    for (int i = index - 1; i >= 0 && str[i] == '\\'; i--)
        backslashes++;
    return backslashes % 2;
}
