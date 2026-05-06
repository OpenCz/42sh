/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** main
*/

#include "../../include/instaler.h"

int main(void)
{
    instaler_t *instaler = malloc(sizeof(instaler_t));
    int c = 0;

    instaler->window = initscr();
    init(instaler);
    loop(c, instaler);
    endwin();
}
