/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/core/context
** File description:
** control
*/

#include "c_zsh.h"

int handle_ctrl_d(int *len, char *user, main_t *stock_main)
{
    if (*len == 0)
        return -1;
    my_putstr("\n");
    display_prompt(stock_main->czshrc->prompt, user);
    return 2;
}

int handle_ctrl_l(main_t *stock_main, char *user)
{
    execute_command(stock_main, "clear");
    display_prompt(stock_main->czshrc->prompt, user);
    return 2;
}
