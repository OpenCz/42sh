/*
** EPITECH PROJECT, 2026
** free
** File description:
** function
*/

#include "minishell.h"

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

static void free_history(history_t *his, history_cmd_t *history)
{
    history_cmd_t *next = NULL;

    for (history_cmd_t *curr = history; curr; curr = next) {
        next = curr->next;
        free(curr->cmd);
        free(curr);
    }
    free(his);
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
    free_history(stock->history, stock->history->history_cmd);
    free(stock);
}

void free_shell_state(main_t *stock)
{
    free_main(stock);
}
