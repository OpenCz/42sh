/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Alias expansion: extract first word, find alias, build expanded command,
** handle self-referential and recursive aliases.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

static char *copy_word(char *src, int start, int len)
{
    char *word = malloc(sizeof(char) * (len + 1));

    if (!word)
        return NULL;
    for (int j = 0; j < len; j++)
        word[j] = src[start + j];
    word[len] = '\0';
    return word;
}

char *alias_extract_first_word(char *cmd)
{
    int i = 0;
    int start;

    while (cmd[i] == ' ' || cmd[i] == '\t')
        i++;
    if (cmd[i] == '"' || cmd[i] == '\'')
        return NULL;
    start = i;
    while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t')
        i++;
    if (i == start)
        return NULL;
    return copy_word(cmd, start, i - start);
}

static alias_stock_t *find_alias_by_name(alias_stock_t *list, char *name)
{
    while (list) {
        if (my_strcmp(name, list->new_name) == 0)
            return list;
        list = list->next;
    }
    return NULL;
}

static char *get_args_after_first(char *cmd)
{
    while (*cmd == ' ' || *cmd == '\t')
        cmd++;
    while (*cmd && *cmd != ' ' && *cmd != '\t')
        cmd++;
    while (*cmd == ' ' || *cmd == '\t')
        cmd++;
    return cmd;
}

static char *concat_val_args(char *alias_val, char *args)
{
    int vlen = strlen(alias_val);
    int rlen = strlen(args);
    char *result = malloc(vlen + 1 + rlen + 1);

    if (!result)
        return NULL;
    for (int i = 0; i < vlen; i++)
        result[i] = alias_val[i];
    result[vlen] = ' ';
    for (int i = 0; i <= rlen; i++)
        result[vlen + 1 + i] = args[i];
    return result;
}

static char *build_expanded_cmd(char *alias_val, char *full_cmd)
{
    char *rest = get_args_after_first(full_cmd);

    if (*rest == '\0')
        return my_strdup(alias_val);
    return concat_val_args(alias_val, rest);
}

static bool is_self_recursive(char *cmd, char *alias_name)
{
    char *first = alias_extract_first_word(cmd);
    bool result;

    if (!first)
        return false;
    result = (my_strcmp(first, alias_name) == 0);
    free(first);
    return result;
}

static bool expand_one_alias(main_t *s, char **command, char **expanded)
{
    char *first_word = alias_extract_first_word(*command);
    alias_stock_t *found = NULL;
    char *new_cmd = NULL;

    if (!first_word)
        return false;
    found = find_alias_by_name(s->alias_stock, first_word);
    free(first_word);
    if (!found)
        return false;
    new_cmd = build_expanded_cmd(found->command, *command);
    if (!new_cmd)
        return false;
    if (*expanded)
        free(*expanded);
    *expanded = new_cmd;
    *command = new_cmd;
    return !is_self_recursive(new_cmd, found->new_name);
}

void expand_aliases(main_t *stock_main, char **command)
{
    char *expanded = NULL;
    int depth = 0;

    if (!stock_main->alias_stock)
        return;
    while (depth < 20 && expand_one_alias(stock_main, command, &expanded))
        depth++;
}
