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

    instaler->window = initscr();
    init(instaler);
    loop(instaler);
    closup(instaler);
    return 0;
}
