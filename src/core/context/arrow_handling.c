/*
** EPITECH PROJECT, 2026
** execute
** File description:
** command
*/
#include <termios.h>
#include "../../../include/minishell.h"

static int is_arrow(char arrow[2], char ch)
{
    if (ch != ARROW_START)
        return -1;
    read(STDIN_FILENO, &arrow[0], 1);
    if (arrow[0] != '[')
        return -1;
    return 0;
}

static void left_arrow(char arrow)
{
    if (arrow != 'D')
        return;
    write(1, "\x1b[D", 3);
}

static void right_arrow(char arrow)
{
    if (arrow != 'C')
        return;
    write(1, "\x1b[C", 3);
}

int arrow_handling(char ch)
{
    char arrow[2];

    if (is_arrow(arrow, ch) == -1)
        return 0;
    read(STDIN_FILENO, &arrow[1], 1);
    left_arrow(arrow[1]);
    right_arrow(arrow[1]);
    return 1;
}
