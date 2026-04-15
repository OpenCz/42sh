/*
** EPITECH PROJECT, 2026
** execute
** File description:
** command
*/

#include "c_zsh.h"

static int execute_compound_command(main_t *stock_main, char *command)
{
    if (my_strstr(command, "&&") != NULL ||
        my_strstr(command, "||") != NULL)
        return execute_operator(stock_main, command);
    if (my_strstr(command, "|") != NULL)
        return execute_pipeline(stock_main, command);
    return execute_single_command(stock_main, command, true);
}

int execute_command(main_t *stock_main, char *command)
{
    char **commands = my_str_to_word_array_quote(command, ";");
    int last_status = 0;

    if (!commands)
        return 1;
    for (int i = 0; commands[i] != NULL; i++)
        last_status = execute_compound_command(stock_main, commands[i]);
    free_array(commands);
    return last_status;
}
