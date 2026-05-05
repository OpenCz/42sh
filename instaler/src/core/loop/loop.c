/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** loop
*/

#include "../../../include/instaler.h"

void loop(int c)
{
    char *title_str = openator("assets/title.txt");
    char **title_arr = title_str ?
        my_str_to_word_array(title_str, "\n") : NULL;

    while (c != 'q') {
        clear();
        print_ascii(1, 15, title_arr);
        mvprintw(10, 10, "Press 'q' to quit.");
        refresh();
        c = getch();
    }
}
