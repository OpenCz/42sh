/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include "../../include/minishell.h"

static void write_print(void)
{
    if (isatty(0))
        display_prompt();
}

static void write_tty(char *buffer)
{
    if (isatty(0))
        my_putstr(buffer);
}

static void serialize(char *buffer)
{
    if (buffer[my_strlen(buffer) - 1] == '\n')
        buffer[my_strlen(buffer) - 1] = '\0';
}

int main(int argc, char **argv, char **env)
{
    main_t *stock = init_main(env);
    char *buffer = NULL;
    int last_exit = 0;
    int cmd = 0;

    while (my_strcmp(buffer, "exit") != 0) {
        write_print();
        cmd = get_command(&buffer, stock->history);
        if (cmd == CONTINUE)
            continue;
        serialize(buffer);
        if (my_strcmp(buffer, "exit") == 0 || cmd == -1)
            break;
        last_exit = execute_command(stock, buffer);
    }
    free_alloc(buffer);
    write_tty("exit\n");
    free_main(stock);
    return last_exit;
}
