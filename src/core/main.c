/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include "minishell.h"

static void write_print(void)
{
    if (isatty(0))
        my_putstr("$> ");
}

int main(int argc, char **argv, char **env)
{
    main_t *stock = init_main(env);
    size_t buffer_size = 64;
    char *buffer = NULL;
    int last_exit = 0;

    while (my_strcmp(buffer, "exit") != 0) {
        write_print();
        if (getline(&buffer, &buffer_size, stdin) == -1)
            break;
        if (buffer[my_strlen(buffer) - 1] == '\n')
            buffer[my_strlen(buffer) - 1] = '\0';
        last_exit = execute_command(stock, buffer);
    }
    free(buffer);
    free_main(stock);
    return last_exit;
}
