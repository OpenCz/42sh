/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** loop
*/

#include "../../../include/instaler.h"

void loop(int c, instaler_t *instaler)
{
    char *title_str = openator("assets/title.txt");
    char **title_arr = title_str ?
        my_str_to_word_array(title_str, "\n") : NULL;

    while (c != 'q') {
        clear();
        print_ascii(1, 15, title_arr);
        mvprintw(instaler->size.y - 1, 0, "Press 'q' to quit.");
        refresh();
        c = getch();
    }
}
