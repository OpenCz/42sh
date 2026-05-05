/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/core/context
** File description:
** autocomplete.c
*/

#include "c_zsh.h"

static void append_bin(char *buffer, struct dirent *file, char *path,
    char ***names)
{
    char *bin = NULL;

    if (strncmp(buffer, file->d_name, strlen(buffer)) == 0) {
        bin = check_bin(file->d_name, path);
        if (bin) {
            append_array(names, file->d_name);
            free_alloc(bin);
        }
    }
}

char **find_name_executables(char *buffer, char *path)
{
    DIR *directory = opendir(path);
    struct dirent *file = NULL;
    char **names = NULL;

    if (!directory)
        return NULL;
    for (file = readdir(directory); file != NULL; file = readdir(directory))
        append_bin(buffer, file, path, &names);
    if (closedir(directory) == -1)
        return NULL;
    return names;
}

static void delete_element(int i, int j, char ***names)
{
    if (strcmp((*names)[i], (*names)[j]) == 0) {
        free_alloc((*names)[j]);
        for (int k = j; (*names)[k] != NULL; k++)
            (*names)[k] = (*names)[k + 1];
        j--;
    }
}

static void clean_multiple(char ***names)
{
    int i = 0;
    int j = 0;

    if (!names || !*names)
        return;
    for (i = 0; (*names)[i] != NULL; i++)
        for (j = i + 1; (*names)[j] != NULL; j++)
            delete_element(i, j, names);
}

char **get_auto_exec(char *buffer, env_t *env)
{
    char **path = my_str_to_word_array(get_path(env), ":");
    char **total = NULL;

    if (!path)
        return NULL;
    for (int i = 0; path[i] != NULL; i++)
        append_array_to_array(&total, find_name_executables(buffer, path[i]));
    free_array(path);
    clean_multiple(&total);
    return total;
}

int handle_autocomplete(char **buffer, int *len, int *cursor,
    main_t *main_stock)
{
    char **names = NULL;

    if (*len <= 0)
        return 0;
    names = get_auto_exec(*buffer, main_stock->stock_env);
    if (!names)
        return 0;
    printf("\n");
    for (int i = 0; names[i] != NULL; i++)
        printf("%s\n", names[i]);
    free_array(names);
    display_prompt(main_stock->czshrc->prompt, get_user(main_stock->stock_env));
    return 0;
}
