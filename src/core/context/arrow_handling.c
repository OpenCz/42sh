/*
** EPITECH PROJECT, 2026
** execute
** File description:
** command
*/
#include <termios.h>
#include "c_zsh.h"

static void left_arrow(char arrow, int *cursor)
{
    if (arrow != 'D')
        return;
    *cursor -= *cursor > 0 ? 1 : 0;
    write(1, "\b", 1);
}

static int up_arrow(history_t *history, char **buffer, int *len, char arrow)
{
    if (arrow != 'A' || !history->history_cmd)
        return 0;
    if (!history->curr_cmd) {
        history->curr = strncpy(history->curr, *buffer, BUFFER_SIZE);
        history->curr_cmd = history->history_cmd;
    } else if (history->curr_cmd->next != NULL)
        history->curr_cmd = history->curr_cmd->next;
    *buffer = strncpy(*buffer, history->curr_cmd->cmd, BUFFER_SIZE);
    *len = strlen(*buffer);
    return 1;
}

static int down_arrow(history_t *history, char **buffer, int *len, char arrow)
{
    if (arrow != 'B' || !history->history_cmd ||
        !history->curr_cmd)
        return 0;
    if (!history->curr_cmd->prev) {
        *buffer = strncpy(*buffer, history->curr, BUFFER_SIZE);
        history->curr_cmd = NULL;
    } else {
        history->curr_cmd = history->curr_cmd->prev;
        *buffer = strncpy(*buffer, history->curr_cmd->cmd, BUFFER_SIZE);
    }
    *len = strlen(*buffer);
    return 1;
}

static void right_arrow(char arrow, int *cursor, int len)
{
    if (arrow != 'C')
        return;
    *cursor += *cursor < len ? 1 : 0;
    write(1, "\x1b[C", 3);
}

int arrow_handling(history_t *history, char **buffer, int *cursor, int *len)
{
    char arrow[2];

    read(STDIN_FILENO, &arrow[0], 1);
    if (arrow[0] != '[')
        return 0;
    read(STDIN_FILENO, &arrow[1], 1);
    left_arrow(arrow[1], cursor);
    right_arrow(arrow[1], cursor, *len);
    if (up_arrow(history, buffer, len, arrow[1]) == 1 ||
        down_arrow(history, buffer, len, arrow[1]) == 1)
        *cursor = strlen(*buffer);
    return 0;
}
