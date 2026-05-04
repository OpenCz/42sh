/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Logical operator chain evaluator: get_operator_array extracts
** && and || tokens; execute_operator_loop short-circuits: next
** command only runs when && (status 0) or || (status != 0).
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

static int get_count_operator(char *command)
{
    int count = 0;

    for (int i = 0; command[i] != '\0'; i++) {
        if ((command[i] == '&' && command[i + 1] == '&') ||
            (command[i] == '|' && command[i + 1] == '|')) {
            count++;
            i++;
        }
    }
    return count;
}

static char **get_operator_array(char *command)
{
    int count = get_count_operator(command);
    char **op_array = malloc(sizeof(char *) * (count + 1));
    int k = 0;

    if (!op_array)
        return NULL;
    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == '&' && command[i + 1] == '&') {
            op_array[k] = strdup("&&");
            k++;
            i++;
        }
        if (command[i] == '|' && command[i + 1] == '|') {
            op_array[k] = strdup("||");
            k++;
            i++;
        }
    }
    op_array[k] = NULL;
    return op_array;
}

int execute_operator_loop(main_t *stock_main, char **commands,
    char **operator_array, int status_exec)
{
    int k = 0;
    int is_and = 0;
    int is_or = 0;

    for (int i = 1; commands[i] != NULL && operator_array[k] != NULL; i++) {
        is_and = my_strcmp(operator_array[k], "&&") == 0;
        is_or = my_strcmp(operator_array[k], "||") == 0;
        if (is_and && status_exec == 0) {
            status_exec = execute_single_command(
                stock_main, commands[i], true);
        }
        if (is_or && status_exec != 0) {
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
    int return_value;

    if (!commands || !commands[0] || !operator_array) {
        free_array(commands);
        free_array(operator_array);
        return 1;
    }
    status_exec = execute_single_command(stock_main, commands[0], true);
    return_value = execute_operator_loop(stock_main, commands,
        operator_array, status_exec);
    free_array(commands);
    free_array(operator_array);
    return return_value;
}
