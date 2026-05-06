/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** RC file loader: update_rc opens ~/.c_zshrc with openator(),
** trims each line, dispatches key=value pairs to manage_prompt()
** and returns a heap-allocated czshrc_t* (or defaults).
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

static void trim_inplace(char *str)
{
    int start = 0;
    int end;
    int len;

    if (!str || str[0] == '\0')
        return;
    for (; str[start] == ' ' || str[start] == '\t'; start++);
    for (end = (int)strlen(str) - 1;
        end >= start && (str[end] == ' ' || str[end] == '\t'); end--);
    len = end - start + 1;
    if (len <= 0) {
        str[0] = '\0';
        return;
    }
    memmove(str, str + start, (size_t)len);
    str[len] = '\0';
}

static void free_parsed_rc(char ***rc_parsed)
{
    if (!rc_parsed)
        return;
    for (int i = 0; rc_parsed[i]; i++)
        free_array(rc_parsed[i]);
    free(rc_parsed);
}

void manage_alias(czshrc_t *rc, char ***rc_parsed, int i)
{
    alias_stock_t *new_alias = NULL;

    for (int j = i + 1; rc_parsed[j] && rc_parsed[j][0][0] != '['; j++) {
        if (!rc_parsed[j][0] || !rc_parsed[j][1])
            continue;
        new_alias = malloc(sizeof(alias_stock_t));
        if (!new_alias)
            return;
        new_alias->new_name = strdup(rc_parsed[j][0]);
        new_alias->command = strdup(rc_parsed[j][1]);
        new_alias->is_fixed = false;
        new_alias->next = rc->aliases;
        rc->aliases = new_alias;
    }
}

static void parse_and_fill_struct(czshrc_t *rc, char *rc_content)
{
    char ***rc_parsed = my_str_to_array_of_word_array(rc_content, "\n", "=");

    if (!rc_parsed)
        return;
    for (int i = 0; rc_parsed[i]; i++) {
        trim_inplace(rc_parsed[i][0]);
        if (rc_parsed[i][1])
            trim_inplace(rc_parsed[i][1]);
    }
    for (int i = 0; rc_parsed[i]; i++) {
        if (rc_parsed[i][0][0] == '#')
            continue;
        if (my_strcmp(rc_parsed[i][0], "[prompt]") == 0)
            manage_prompt(rc, rc_parsed, i);
        if (my_strcmp(rc_parsed[i][0], "[alias]") == 0)
            manage_alias(rc, rc_parsed, i);
    }
    free_parsed_rc(rc_parsed);
    free_alloc(rc_content);
}

czshrc_t *update_rc(char *path)
{
    czshrc_t *rc = malloc(sizeof(czshrc_t));
    char *rc_content = NULL;

    if (!rc)
        return NULL;
    set_default_rc(rc);
    if (path) {
        if (access(path, F_OK) == -1)
            return rc;
        rc_content = openator(path);
    } else {
        if (access(".czshrc", F_OK) == -1)
            return rc;
        rc_content = openator(".czshrc");
    }
    if (!rc_content)
        return rc;
    parse_and_fill_struct(rc, rc_content);
    return rc;
}
