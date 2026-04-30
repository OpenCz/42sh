/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Command history: push_front prepends a new history_cmd_t node
** with id and HH:MM timestamp, appends to ~/.c_zsh_history.
** manage_history is the public entry point after each command.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"
#include <time.h>

static void add_to_history(history_t *his, history_cmd_t *history)
{
    FILE *file = fopen(".c_zsh_history", "a+");
    time_t curr_time = time(NULL);
    struct tm *t = localtime(&curr_time);

    if (!file)
        return;
    fprintf(file, "%6d\t%.2d:%.2d\t%s\n", his->id, t->tm_hour,
        t->tm_min, history->cmd);
    fclose(file);
}

static history_cmd_t *push_front(history_t *his,
    history_cmd_t **history, char *cmd)
{
    history_cmd_t *new = malloc(sizeof(history_cmd_t));
    size_t len = strlen(cmd);

    if (!new)
        return NULL;
    new->cmd = cmd;
    if (len > 0 && new->cmd[len - 1] == '\n')
        new->cmd[len - 1] = '\0';
    new->id = his->id;
    his->id += 1;
    new->next = *history;
    new->prev = NULL;
    if (*history != NULL)
        (*history)->prev = new;
    *history = new;
    return new;
}

int manage_history(history_t *history, char **cmd)
{
    history_cmd_t *history_cmd = NULL;

    if (!(*cmd) || (*cmd)[0] == '\0' ||
        ((*cmd)[0] == '\n' && (*cmd)[1] == '\0')) {
        if (*cmd) {
            free(*cmd);
            *cmd = NULL;
        }
        return 1;
    }
    history_cmd = push_front(history, &history->history_cmd, *cmd);
    if (!history_cmd)
        return 1;
    add_to_history(history, history_cmd);
    return 0;
}
