/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** init
*/

#include "../../include/instaler.h"

void init(WINDOW *window)
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(window, TRUE);
}
