/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** manage_backticks
*/

#include "../../../include/c_zsh.h"

char *manage_backticks(char *cmd, main_t *stock_main)
{
    char **parsed_backticks = my_str_to_word_array(cmd, "`");
    char *result = NULL;
    int len = 0;

    if (!parsed_backticks)
        return NULL;
    len = my_wordarray_len(parsed_backticks);
    if (len == 1) {
        free_array(parsed_backticks);
        return my_strdup(cmd);
    }
    for (int i = 1; i < len; i = i + 2) {
        parsed_backticks[i] = command_substitution(stock_main,
            parsed_backticks[i]);
        if (!parsed_backticks[i])
            parsed_backticks[i] = my_strdup("");
    }
    result = my_word_array_to_str(parsed_backticks);
    free_array(parsed_backticks);
    return result;
}
