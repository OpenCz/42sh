/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** init
*/

#include "../../include/instaler.h"

void init(WINDOW *window)
{
    noecho();
    cbreak();
    curs_set(0);
    nodelay(window, TRUE);
    keypad(window, TRUE);
    wtimeout(window, 100);
}
