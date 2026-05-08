/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/core/context
** File description:
** craft_autocomplete.c
*/

#include "c_zsh.h"

static char *join_path(char *directory, char *name)
{
    size_t dir_len = strlen(directory);
    size_t name_len = strlen(name);
    int need_separator = (dir_len > 0 && directory[dir_len - 1] != '/');
    char *path = malloc(sizeof(char) * (dir_len +
            (size_t)need_separator + name_len + 1));

    if (!path)
        return NULL;
    memcpy(path, directory, dir_len);
    if (need_separator)
        path[dir_len] = '/';
    memcpy(path + dir_len + (size_t)need_separator, name, name_len);
    path[dir_len + (size_t)need_separator + name_len] = '\0';
    return path;
}

static bool split_completion_without_slash(char **directory_name,
    char **prefix, char *word)
{
    *prefix = strdup(word ? word : "");
    if (!*prefix)
        return false;
    *directory_name = strdup("");
    if (!*directory_name) {
        free_alloc(*prefix);
        *prefix = NULL;
        return false;
    }
    return true;
}

static bool split_completion_with_slash(char *slash, char **prefix)
{
    *prefix = strdup(slash + 1);
    if (!*prefix)
        return false;
    slash[1] = '\0';
    return true;
}

bool split_completion_path(char *word, char **directory_name,
    char **prefix)
{
    char *slash = NULL;

    *directory_name = strdup(word ? word : "");
    if (!*directory_name)
        return false;
    slash = strrchr(*directory_name, '/');
    if (!slash) {
        free_alloc(*directory_name);
        *directory_name = NULL;
        return split_completion_without_slash(directory_name, prefix, word);
    }
    return split_completion_with_slash(slash, prefix);
}

static void append_matching_file(char ***names, char *directory_name,
    struct dirent *file, char *prefix)
{
    char *candidate = NULL;

    if (strncmp(prefix, file->d_name, strlen(prefix)) != 0)
        return;
    candidate = join_path(directory_name, file->d_name);
    if (!candidate)
        return;
    append_array(names, candidate);
    free_alloc(candidate);
}

bool should_complete_command(char *precedent, char *word)
{
    if (!precedent || !word)
        return true;
    return (strcmp(precedent, "&&") == 0 || strcmp(precedent, "|") == 0 ||
        strcmp(precedent, "||") == 0);
}

char **collect_file_names(char *directory_to_open, char *directory_name,
    char *prefix)
{
    DIR *directory = opendir(directory_to_open);
    struct dirent *file = NULL;
    char **names = NULL;

    if (!directory)
        return NULL;
    for (file = readdir(directory); file != NULL; file = readdir(directory)) {
        append_matching_file(&names, directory_name, file, prefix);
    }
    if (closedir(directory) == -1) {
        free_array(names);
        return NULL;
    }
    merge_sort(names, 0, (len_array(names) - 1));
    return names;
}

bool is_special_token(char *word)
{
    if (!word)
        return false;
    return (strcmp(word, "&&") == 0 || strcmp(word, "|") == 0 ||
        strcmp(word, "||") == 0);
}
