/*
** EPITECH PROJECT, 2026
** check_bin
** File description:
** bin
*/
#include "minishell.h"
#include <stdlib.h>
#include <string.h>

static int is_executable_file(char *full_path)
{
    struct stat st;

    if (!full_path)
        return SUCCESS;
    if (stat(full_path, &st) == -1)
        return SUCCESS;
    if (S_ISDIR(st.st_mode))
        return SUCCESS;
    return access(full_path, X_OK) == 0;
}

char *loop_bin(main_t *main_stock, char *command)
{
    int i = 0;
    char *path_bin = NULL;

    if (main_stock == NULL || main_stock->path == NULL)
        return NULL;
    for (; main_stock->path[i] != NULL; i++) {
        path_bin = check_bin(command, main_stock->path[i]);
        if (path_bin != NULL)
            return path_bin;
    }
    return NULL;
}

static char *build_path(char *path, char *name)
{
    char *tmp = my_strconcat(path, "/");
    char *full_path;

    if (tmp == NULL)
        return NULL;
    full_path = my_strconcat(tmp, name);
    free(tmp);
    return full_path;
}

int check_is_dir(char *command)
{
    struct stat st;

    if (command == NULL)
        return SUCCESS;
    if (stat(command, &st) == 0 && S_ISDIR(st.st_mode)) {
        my_putstrerror(command);
        my_putstrerror(": Permission denied.");
        return 1;
    }
    return SUCCESS;
}

char *check_bin(char *command, char *path)
{
    char *full_path = NULL;

    if (command == NULL || path == NULL)
        return NULL;
    if (check_is_dir(command) == 1)
        return NULL;
    full_path = build_path(path, command);
    if (!full_path)
        return NULL;
    if (!is_executable_file(full_path)) {
        free(full_path);
        return NULL;
    }
    return full_path;
}
