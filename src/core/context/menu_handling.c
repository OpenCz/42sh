/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/core/context
** File description:
** menu_handling.c
*/

#include "c_zsh.h"

int down_arrow(char **names, int *idx)
{
    if (*idx < len_array(names) - 1)
        (*idx)++;
    return 0;
}

int up_arrow(char **names, int *idx)
{
    if (*idx > 0)
        (*idx)--;
    return 0;
}

int tab_handling(char **names, int *idx)
{
    (*idx)++;
    if (*idx >= len_array(names))
        (*idx) = 0;
    return 0;
}

void handle_menu_arrow(char **names, int *idx,
    char *arrow, int shown)
{
    printf("\x1b[%dA", shown);
    if (arrow[2] == 'T')
        tab_handling(names, idx);
    if (arrow[2] == 'B')
        down_arrow(names, idx);
    if (arrow[2] == 'A')
        up_arrow(names, idx);
    render_list(names, *idx, shown);
}

int check_escape(char *arrow)
{
    if (read(STDIN_FILENO, &arrow[1], 1) != 1 ||
        read(STDIN_FILENO, &arrow[2], 1) != 1)
        return 1;
    if (arrow[1] == '[' && (arrow[2] == 'A' || arrow[2] == 'B'))
        return 0;
    return 1;
}
