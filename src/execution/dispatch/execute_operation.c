/*
** EPITECH PROJECT, 2026
** execute
** File description:
** execute
*/

#include "c_zsh.h"

static int get_count_operator(char **commands)
{
    int i = 0;
    int count = 0;

    for (; commands[i] != NULL; i++) {
        if (my_strcmp(commands[i], "&&") == 0 ||
            my_strcmp(commands[i], "||") == 0) {
            count++;
        }
    }
    return count;
}

static char **get_operator_array(char *command)
{
    char **commands = my_str_to_word_array(command, " ");
    int count = get_count_operator(commands);
    char **op_array = malloc(sizeof(char *) * (count + 1));
    int i = 0;
    int k = 0;

    for (; commands[i] != NULL; i++) {
        if (my_strcmp(commands[i], "&&") == 0 ||
            my_strcmp(commands[i], "||") == 0) {
            op_array[k] = my_strdup(commands[i]);
            k++;
        }
    }
    return op_array;
}

int execute_operator_loop(main_t *stock_main, char **commands,
    char **operator_array, int status_exec)
{
    int i = 1;
    int k = 0;

    for (; commands[i] != NULL; i++) {
        if (my_strcmp(operator_array[k], "&&") == 0 && status_exec == 0) {
            status_exec = execute_single_command(
                stock_main, commands[i], true);
        }
        if (my_strcmp(operator_array[k], "||") == 0 && status_exec != 0) {
            status_exec = execute_single_command(
                stock_main, commands[i], true);
        }
        k++;
    }
    return status_exec;
}

int execute_operator(main_t *stock_main, char *command)
{
    char **commands = my_str_to_word_array(command, "&&||");
    char **operator_array = get_operator_array(command);
    int status_exec = 0;
    int i = 0;
    int return_value;

    status_exec = execute_single_command(
        stock_main, commands[i], true);
    return_value = execute_operator_loop(stock_main, commands,
        operator_array, status_exec);
    free_array(commands);
    free_array(operator_array);
    return return_value;
}
