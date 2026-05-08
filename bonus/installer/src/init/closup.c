/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** closup
*/

#include "installer/install.h"

void closup(instaler_t *instaler)
{
    endwin();
    free(instaler);
}
