/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include "42sh.h"

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
    return main_node;
}
