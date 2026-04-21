/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/core/context
** File description:
** termios
*/

#include "c_zsh.h"

void init_termios(struct termios *tr, struct termios *old)
{
    tcgetattr(STDIN_FILENO, old);
    tcgetattr(STDIN_FILENO, tr);
    tr->c_lflag &= ~(ICANON | ECHO | ISIG);
    tr->c_cc[VMIN] = 1;
    tr->c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, tr);
}
