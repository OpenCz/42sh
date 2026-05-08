/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/plugins/example/matrix
** File description:
** window.c
*/

#include "c_zsh.h"

void set_blank_term(void)
{
    struct termios tr;

    tcgetattr(STDIN_FILENO, &tr);
    tr.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tr);
}

void get_terminal_size(int *rows, int *cols)
{
    struct winsize size;

    if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) == -1 || size.ws_row == 0 ||
        size.ws_col == 0) {
        *rows = 24;
        *cols = 80;
        return;
    }
    *rows = size.ws_row;
    *cols = size.ws_col;
}

void restore_terminal(struct termios *old)
{
    printf("\033[0m\033[?25h\033[2J\033[H");
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSANOW, old);
}
