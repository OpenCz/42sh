/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Tab completion stub: get_display_width returns char display
** width; get_buffer_display_width sums widths for cursor math;
** write_tab_spaces is a placeholder for future completion.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

int get_display_width(char ch)
{
    return ch == '\t' ? TAB_WIDTH : 1;
}

int get_buffer_display_width(char *buffer, int len)
{
    int width = 0;

    for (int i = 0; i < len && buffer[i]; i++)
        width += get_display_width(buffer[i]);
    return width;
}

void write_tab_spaces(void)
{
    for (int tab = 0; tab < TAB_WIDTH; tab++)
        write(1, " ", 1);
}
