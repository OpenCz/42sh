/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** closup
*/

#include "../../include/instaler.h"

void closup(instaler_t *instaler)
{
    endwin();
    free(instaler);
}
