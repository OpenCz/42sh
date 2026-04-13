/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include "minishell.h"

static history_t *init_history(main_t *main)
{
    FILE *file = NULL;

    main->history = calloc(1, sizeof(history_t));
    if (!main->history)
        free(main);
    file = fopen("history.txt", "w+");
    if (file)
        fclose(file);
    return main->history;
}

main_t *init_main(char **env)
{
    main_t *main_node = malloc(sizeof(main_t));

    if (!main_node)
        return NULL;
    main_node->stock_env = init_env(env);
    main_node->command = NULL;
    main_node->env = env;
    main_node->argv = NULL;
    main_node->arg_command = NULL;
    main_node->redirection = NULL;
    main_node->old_path = NULL;
    main_node->path = my_str_to_word_array(get_path(main_node->stock_env), ":");
    main_node->home = get_home(main_node->stock_env);
    init_history(main_node);
    return main_node;
}
