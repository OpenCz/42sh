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

static int get_history_id(void)
{
    FILE *file = fopen(".c_zsh_history", "r");
    int id = 0;
    char *line = NULL;
    size_t len = 0;

    if (!file)
        return id;
    for (; getline(&line, &len, file) != -1; id++);
    fclose(file);
    free_alloc(line);
    return id;
}

static history_t *init_history(main_t *main)
{
    main->history = calloc(1, sizeof(history_t));
    if (!main->history)
        free(main);
    main->history->curr = malloc(LINE_SIZE + 1);
    if (!main->history->curr)
        return NULL;
    main->history->id = get_history_id();
    return main->history;
}

static czshrc_t *init_rc(void)
{
    czshrc_t *rc = update_rc(".czshrc");

    if (!rc)
        return NULL;
    return rc;
}

static void init_alias_stock(main_t *main_node)
{
    if (!main_node->czshrc)
        return;
    main_node->alias_stock = main_node->czshrc->aliases;
    main_node->czshrc->aliases = NULL;
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

static signal_t *init_signal(void)
{
    signal_t *signal = malloc(sizeof(signal_t));

    if (!signal)
        return NULL;
    signal->g_sigxcpu = 0;
    signal->sfd = 0;
    return signal;
}

static void initrc(main_t *main_node)
{
    main_node->czshrc = init_rc();
    init_alias_stock(main_node);
}

static void set_basic_shell(main_t *main_node, char **env)
{
    main_node->stock_env = init_env(env);
    main_node->command = NULL;
    main_node->env = env;
    main_node->argv = NULL;
    main_node->arg_command = NULL;
    main_node->redirection = NULL;
    main_node->old_path = NULL;
    main_node->path = my_str_to_word_array(get_path(main_node->stock_env), ":");
    main_node->home = get_home(main_node->stock_env);
}

main_t *init_main(char **env)
{
    main_t *main_node = malloc(sizeof(main_t));

    if (!main_node)
        return NULL;
    set_basic_shell(main_node, env);
    main_node->alias_stock = NULL;
    init_history(main_node);
    initrc(main_node);
    builtin_loader(main_node);
    main_node->controler = init_job_controler();
    main_node->signal = init_signal();
    main_node->stock_local_var = NULL;
    return main_node;
}
