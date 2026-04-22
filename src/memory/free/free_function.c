/*
** EPITECH PROJECT, 2026
** free
** File description:
** function
*/

#include "c_zsh.h"

void free_alloc(void *object)
{
    if (object)
        free(object);
}

void free_linked_list(env_t *env)
{
    env_t *next;

    while (env) {
        next = env->next;
        free_alloc(env->key);
        free_alloc(env->value);
        free_alloc(env);
        env = next;
    }
}

void free_array(char **array)
{
    int i = 0;

    if (!array)
        return;
    for (; array[i] != NULL; i++)
        free_alloc(array[i]);
    free_alloc(array);
}

static void free_history(history_t *his, history_cmd_t *history)
{
    history_cmd_t *next = NULL;

    for (history_cmd_t *curr = history; curr; curr = next) {
        next = curr->next;
        free_alloc(curr->cmd);
        free_alloc(curr);
    }
    free_alloc(his->curr);
    free_alloc(his);
}

void free_main(main_t *stock)
{
    if (!stock)
        return;
    free_array(stock->path);
    free_array(stock->argv);
    free_alloc(stock->redirection);
    free_alloc(stock->old_path);
    free_linked_list(stock->stock_env);
    free_history(stock->history, stock->history->history_cmd);
    free_alloc(stock);
}
