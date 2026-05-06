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

char **get_aliases(char *word, alias_stock_t *aliases)
{
    char **alias = NULL;
    alias_stock_t *tmp = aliases;

    for (; tmp; tmp = tmp->next)
        if (strncmp(word, tmp->new_name, strlen(word)) == 0)
            append_array(&alias, tmp->new_name);
    return alias;
}

char **get_auto_exec(char *word, main_t *main_stock, int *cursor)
{
    char **path = my_str_to_word_array(get_path(main_stock->stock_env), ":");
    char **total = NULL;

    if (!path || !word)
        return NULL;
    append_array_to_array(&total, get_aliases(word, main_stock->alias_stock));
    for (int i = 0; path[i] != NULL; i++)
        append_array_to_array(&total, find_name_executables(word, path[i]));
    free_array(path);
    merge_sort(total, 0, (len_array(total) - 1));
    clean_multiple(&total);
    return total;
}

int handle_autocomplete(char **buffer, int *len, int *cursor,
    main_t *main_stock)
{
    char **names = NULL;
    char *word = get_word_on_cursor(buffer, cursor);

    if (*len <= 0 || !word)
        return 0;
    names = get_auto_exec(word, main_stock, cursor);
    if (!names) {
        free_alloc(word);
        return 0;
    }
    if (len_array(names) > 1)
        menu(names, main_stock, &(buffer_t){len, buffer, cursor});
    free_array(names);
    free_alloc(word);
    return 0;
}
