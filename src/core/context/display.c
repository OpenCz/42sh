/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/core/context
** File description:
** display
*/

#include "c_zsh.h"

void write_print(main_t *stock)
{
    char *user = get_user(stock->stock_env);

    if (isatty(0))
        display_prompt(stock->czshrc->prompt, user);
}

void write_tty(char *buffer)
{
    if (isatty(0))
        my_putstr(buffer);
}
