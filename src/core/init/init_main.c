/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Shell state constructor: init_history loads ~/.c_zsh_history;
** init_rc calls update_rc() for czshrc; init_main allocates
** main_t and fills PATH, HOME, history, RC config.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../../include/c_zsh.h"

static history_t *init_history(main_t *main)
{
    main->history = calloc(1, sizeof(history_t));
    if (!main->history)
        free(main);
    main->history->curr = malloc(BUFFER_SIZE + 1);
    if (!main->history->curr)
        return NULL;
    return main->history;
}

static czshrc_t *init_rc(void)
{
    czshrc_t *rc = update_rc(".czshrc");

    if (!rc)
        return NULL;
    return rc;
}

static job_controler_t *init_job_controler(void)
{
    job_controler_t *controler = malloc(sizeof(job_controler_t));

    if (controler == NULL)
        return NULL;
    controler->job = NULL;
    controler->next = NULL;
    return controler;
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
    main_node->alias_stock = NULL;
    init_history(main_node);
    main_node->czshrc = init_rc();
    main_node->controler = init_job_controler();
    main_node->stock_local_var = NULL;
    return main_node;
}
