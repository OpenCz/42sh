/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Prompt and TTY display helpers: write_print calls
** display_prompt() to render the full styled prompt;
** write_tty rewrites the buffer for in-line editing display.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

void write_print(main_t *stock)
{
    char *user = get_user(stock->stock_env);

    pre_cmd(stock);
    if (isatty(0))
        display_prompt(stock->czshrc->prompt, user);
}

void write_tty(char *buffer)
{
    if (isatty(0))
        my_putstr(buffer);
}
