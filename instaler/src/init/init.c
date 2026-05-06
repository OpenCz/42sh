/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** init
*/

#include "../../include/instaler.h"

void init(instaler_t *instaler)
{
    noecho();
    cbreak();
    curs_set(0);
    nodelay(instaler->window, TRUE);
    keypad(instaler->window, TRUE);
    wtimeout(instaler->window, 100);
    getmaxyx(instaler->window, instaler->size.y, instaler->size.x);
}
