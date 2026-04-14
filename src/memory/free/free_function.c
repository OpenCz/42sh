/*
** EPITECH PROJECT, 2026
** free
** File description:
** function
*/

#include "c_zsh.h"

void free_linked_list(env_t *env)
{
    env_t *next;

    while (env) {
        next = env->next;
        free(env->key);
        free(env->value);
        free(env);
        env = next;
    }
}

void free_array(char **array)
{
    int i = 0;

    if (!array)
        return;
    for (; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

void free_main(main_t *stock)
{
    if (!stock)
        return;
    free_array(stock->path);
    free_array(stock->argv);
    if (stock->redirection)
        free(stock->redirection);
    if (stock->old_path)
        free(stock->old_path);
    free_linked_list(stock->stock_env);
    free(stock);
}

void free_shell_state(main_t *stock)
{
    free_main(stock);
}
