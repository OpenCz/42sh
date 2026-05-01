/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** manage_backticks
*/

#include "../../../include/c_zsh.h"

static void substitute_backticks(main_t *main, char **parsed, int len)
{
    char *content = NULL;
    char *result = NULL;
    int i = 1;

    for (; i < len; i = i + 2) {
        content = parsed[i];
        result = command_substitution(main, content);
        free_alloc(content);
        parsed[i] = result ? result : my_strdup("");
    }
}

char *manage_backticks(char *cmd, main_t *stock_main)
{
    char **parsed = NULL;
    int len = 0;
    char *result = NULL;

    parsed = my_str_to_word_array(cmd, "`");
    if (!parsed)
        return NULL;
    len = my_wordarray_len(parsed);
    if (len <= 1) {
        free_array(parsed);
        return my_strdup(cmd);
    }
    substitute_backticks(stock_main, parsed, len);
    result = my_word_array_to_str(parsed);
    free_array(parsed);
    return result;
}
