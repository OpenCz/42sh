/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** detect_os
*/

#include "../../include/instaler.h"

static void strip_quotes(char *id)
{
    size_t len = strlen(id);

    while (len > 0 && (id[len - 1] == '\n' || id[len - 1] == '"')) {
        id[len - 1] = '\0';
        len--;
    }
    if (id[0] == '"')
        memmove(id, id + 1, strlen(id));
}

static void free_array_of_word_array(char ***arr)
{
    int i;

    if (!arr)
        return;
    for (i = 0; arr[i]; i++) {
        free_array(arr[i]);
    }
    free(arr);
}

static char *find_id(char ***lines)
{
    char *id;
    int i;

    for (i = 0; lines[i]; i++) {
        if (!lines[i][0] || strcmp(lines[i][0], "ID") != 0)
            continue;
        if (!lines[i][1])
            continue;
        id = strdup(lines[i][1]);
        strip_quotes(id);
        return id;
    }
    return NULL;
}

char *detect_os(void)
{
    char *content;
    char ***lines;
    char *id;

    content = openator("/etc/os-release");
    if (!content)
        return strdup("macos");
    lines = my_str_to_array_of_word_array(content, "\n", " \t=");
    free_alloc(content);
    if (!lines)
        return strdup("unknown");
    id = find_id(lines);
    free_array_of_word_array(lines);
    return id ? id : strdup("unknown");
}
