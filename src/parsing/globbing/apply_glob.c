/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/parsing/globbing
** File description:
** apply_glob.c
*/

#include "c_zsh.h"

static int has_glob_chars(const char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] == '*' || str[i] == '?' || str[i] == '[')
            return 1;
    return 0;
}

static int append_glob_matches(char ***new_args, int *count, glob_t *g)
{
    char **temp = NULL;
    int size = g->gl_pathc;

    temp = realloc(*new_args, sizeof(char *) * (*count + size + 1));
    if (!temp)
        return -1;
    *new_args = temp;
    for (int i = 0; i < size; i++) {
        (*new_args)[*count] = strdup(g->gl_pathv[i]);
        if (!(*new_args)[*count])
            return -1;
        (*count)++;
    }
    (*new_args)[*count] = NULL;
    return 0;
}

static int append_single_arg(char ***new_args, int *count, const char *arg)
{
    char **temp = realloc(*new_args, sizeof(char *) * (*count + 2));

    if (!temp)
        return -1;
    *new_args = temp;
    (*new_args)[*count] = strdup(arg);
    if (!(*new_args)[*count])
        return -1;
    (*count)++;
    (*new_args)[*count] = NULL;
    return 0;
}

static int process_glob_pattern(char ***new_args, int *count,
    char **args, int idx)
{
    glob_t g = {0};
    int ret = glob(args[idx], GLOB_TILDE, NULL, &g);

    if (ret == 0) {
        if (append_glob_matches(new_args, count, &g) == -1) {
            globfree(&g);
            return -1;
        }
        globfree(&g);
        return 0;
    }
    if (ret == GLOB_NOMATCH) {
        fprintf(stderr, "%s: No match.\n", args[0]);
        globfree(&g);
        return -2;
    }
    globfree(&g);
    return -1;
}

static int process_arg(char ***new_args, int *count, char **args, int idx)
{
    if (has_glob_chars(args[idx]))
        return process_glob_pattern(new_args, count, args, idx);
    return (append_single_arg(new_args, count, args[idx]) == -1) ? -1 : 0;
}

char **apply_globbing_to_args(char **args)
{
    char **new_args = NULL;
    int count = 0;
    int ret = 0;

    if (!args || !args[0])
        return args;
    for (int i = 0; args[i]; i++) {
        ret = process_arg(&new_args, &count, args, i);
        if (ret == -2) {
            free_array(new_args);
            free_array(args);
            return NULL;
        }
        if (ret == -1) {
            free_array(new_args);
            return args;
        }
    }
    free_array(args);
    return new_args;
}
