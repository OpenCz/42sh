/*
** EPITECH PROJECT, 2026
** execute
** File description:
** execute
*/

#include "42sh.h"

int execute_double_and(main_t *stock_main, char *command)
{
    char **commands = my_str_to_word_array(command, "&&");
    int commands_len = my_wordarray_len(commands);
    int single_status = 0;

    for (int i = 0; i < commands_len; i++) {
        if (single_status == 0)
            single_status = execute_single_command(
                stock_main, commands[i], true);
        else
            return -1;
    }
    return 0;
}

int execute_double_pipe(main_t *stock_main, char *command)
{
    char **commands = my_str_to_word_array(command, "||");
    int commands_len = my_wordarray_len(commands);
    int single_status = 0;

    single_status = execute_single_command(
        stock_main, commands[0], true);
    for (int i = 1; i < commands_len; i++) {
        if (single_status != 0)
            single_status = execute_single_command(
                stock_main, commands[i], true);
        else
            return -1;
    }
    return 0;
}
