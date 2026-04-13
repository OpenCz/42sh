/*
** EPITECH PROJECT, 2026
** minishell
** File description:
** shell
*/

#include "../../../include/minishell.h"

static void add_to_history(history_cmd_t *history)
{
    FILE *file = fopen("history.txt", "a+");

    if (!file)
        return;
    fprintf(file, "%6d\t00:00\t%s", history->id, history->cmd);
    fclose(file);
}

static void push_front(history_t *his, history_cmd_t **history, char *cmd)
{
    history_cmd_t *new = malloc(sizeof(history_cmd_t));

    if (!new)
        return;
    new->cmd = strdup(cmd);
    new->date = NULL;
    new->id = his->id;
    his->id += 1;
    new->prev = *history;
    new->next = NULL;
    *history = new;
}

int manage_history(history_t *history, char *cmd)
{
    if (cmd[0] == '\n' || !cmd)
        return 1;
    push_front(history, &history->history_cmd, cmd);
    add_to_history(history->history_cmd);
    return 0;
}
