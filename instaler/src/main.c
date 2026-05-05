/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** main
*/

#include "../include/instaler.h"

int main(void)
{
    WINDOW *window = initscr();
    int c = 0;

    init(window);
    while (c != 'q')
        c = getch();
    endwin();
}
