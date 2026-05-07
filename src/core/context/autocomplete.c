/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/core/context
** File description:
** autocomplete.c
*/

#include "c_zsh.h"

const builtin_command_common_t command_builtin[] = {
    {"env", builtin_env},
    {"setenv", builtin_setenv},
    {"unsetenv", builtin_unsetenv},
    {"cd", builtin_cd},
    {"jobs", builtin_jobs},
    {"fg", builtin_foreground},
    {"bg", builtin_background},
    {"repeat", builtin_repeat},
    {"foreach", builtin_foreach},
    {"which", builtin_which},
    {"where", builtin_where},
    {"printenv", builtin_printenv},
    {"if", builtin_if},
    {"history", builtin_history},
    {"alias", builtin_alias},
    {"source", source},
    {"set", builtin_set},
    {"unset", builtin_unset},
    {"limit", builtin_limit},
    {"unlimit", builtin_unlimit},
    {NULL, NULL}
};

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

char **get_builtins(char *word, builtin_command_t *builtins)
{
    char **builtins_total = NULL;
    builtin_command_t *tmp = builtins;

    for (; tmp; tmp = tmp->next)
        if (strncmp(word, tmp->name, strlen(word)) == 0)
            append_array(&builtins_total, tmp->name);
    for (size_t i = 0; command_builtin[i].name != NULL; i++)
        if (strncmp(word, (char *)command_builtin[i].name, strlen(word)) == 0)
            append_array(&builtins_total, (char *)command_builtin[i].name);
    return builtins_total;
}

char **get_auto_exec(char *word, main_t *main_stock, int *cursor)
{
    char **total = NULL;
    char **path = NULL;

    if (!word)
        return NULL;
    path = my_str_to_word_array(get_path(main_stock->stock_env), ":");
    if (!path)
        return NULL;
    append_array_to_array(&total, get_aliases(word, main_stock->alias_stock));
    append_array_to_array(&total, get_builtins(word, main_stock->builtin));
    for (int i = 0; path[i] != NULL; i++)
        append_array_to_array(&total, find_name_executables(word, path[i]));
    free_array(path);
    merge_sort(total, 0, (len_array(total) - 1));
    clean_multiple(&total);
    return total;
}

static char *get_precedent_word(char *buffer, int cursor, char *word)
{
    int i = cursor - 1;

    if (word)
        i -= strlen(word);
    for (; i >= 0 && buffer[i] == ' '; i--);
    return get_word_on_cursor(&buffer, &i);
}

static char **get_files(char *word)
{
    char *directory_name = NULL;
    char *prefix = NULL;
    char **names = NULL;

    if (!split_completion_path(word, &directory_name, &prefix))
        return NULL;
    names = collect_file_names(directory_name[0] ? directory_name : ".",
        directory_name, prefix);
    free_alloc(directory_name);
    free_alloc(prefix);
    return names;
}

int handle_autocomplete(char **buffer, int *len, int *cursor,
    main_t *main_stock)
{
    char **names = NULL;
    char *word = get_word_on_cursor(buffer, cursor);
    char *precedent = NULL;

    if (*len <= 0)
        return 0;
    precedent = get_precedent_word(*buffer, *cursor, word);
    if (should_complete_command(precedent, word))
        names = get_auto_exec(word, main_stock, cursor);
    else if (!is_special_token(word))
        names = get_files(word);
    if (names && len_array(names) >= 1)
        menu(names, main_stock, &(buffer_t){len, buffer, cursor});
    free_array(names);
    free_alloc(word);
    free_alloc(precedent);
    return 0;
}
