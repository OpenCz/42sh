/*
** EPITECH PROJECT, 2026
** instaler
** File description:
** print_ascii
*/

#include "installer/install.h"

void print_ascii(int y, int x, char **ascii)
{
    for (int i = 0; ascii[i] != NULL; i++) {
        mvprintw(y + i, x, "%s", ascii[i]);
    }
}
